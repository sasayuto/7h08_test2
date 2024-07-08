

Texture2D<float4> Texture : register(t0);
sampler Sampler : register(s0);


cbuffer Parameters : register(b0)
{
    float4 DiffuseColor             : packoffset(c0);
    float3 EmissiveColor            : packoffset(c1);
    float3 SpecularColor            : packoffset(c2);
    float  SpecularPower : packoffset(c2.w);

    float3 LightDirection[3]        : packoffset(c3);
    float3 LightDiffuseColor[3]     : packoffset(c6);
    float3 LightSpecularColor[3]    : packoffset(c9);

    float3 EyePosition              : packoffset(c12);

    float3 FogColor                 : packoffset(c13);
    float4 FogVector                : packoffset(c14);

    float4x4 World                  : packoffset(c15);
    float3x3 WorldInverseTranspose  : packoffset(c19);
    float4x4 WorldViewProj          : packoffset(c22);
};

cbuffer Parameters : register(b1)
{
    float SpotLightPower : packoffset(c0.x);
    float LightPower : packoffset(c0.y);
    float Att2 : packoffset(c0.z);
    float3 SpotLight :  packoffset(c1);
    float3 LightPosition : packoffset(c2);
    float3 LightAmbient : packoffset(c3);
    float3 EyePos : packoffset(c4);
    float Near : packoffset(c5.x);
    float Far : packoffset(c5.y);
};

struct PSInputPixelLightingTx
{
    float2 TexCoord     : TEXCOORD0;
    float4 PositionWS   : TEXCOORD1;
    float3 NormalWS     : TEXCOORD2;
    float4 Diffuse      : COLOR0;
};

// Pixel shader: pixel lighting.
float4 main(PSInputPixelLightingTx pin) : SV_TARGET
{
// 光源の方向
    float3 lightDirection = pin.PositionWS.xyz - SpotLight;
  
    // 光源までの距離
    float lightDistance = length(lightDirection);

    // 光源からの距離の影響
    float atten = saturate(SpotLightPower / (lightDistance * lightDistance));

   // テクスチャ色 × Vcが指定されている場合は頂点カラー + アルファ
    float4 color = Texture.Sample(Sampler, pin.TexCoord) * pin.Diffuse;

    // 法線を正規化
   float3 worldNormal = normalize(pin.NormalWS);

   // 光の強さを内積から算出する
   float3 dotL = dot(LightPosition, worldNormal);

   // 表面の場合は１、裏面の場合は0
   float3 zeroL = step(0, dotL);

   // 裏面の場合は黒になる
   float3 diffuse = zeroL * dotL;// 光の強さを内積から算出する
 
   float3 dotSpot = dot(SpotLight, worldNormal);

   // 表面の場合は１、裏面の場合は0
   float3 zeroSpot = step(0.0f, dotSpot);

   // 裏面の場合は黒になる
   float3 SpotDiffuse = dotSpot * zeroSpot;
   SpotDiffuse *= atten;

   // マテリアルのディフューズ色を掛ける
   diffuse = diffuse * DiffuseColor.rgb + EmissiveColor;

   // マテリアルのディフューズ色を掛ける
   SpotDiffuse = SpotDiffuse * DiffuseColor.rgb + EmissiveColor;

   // 光の影響を掛ける
   color.rgb *= SpotDiffuse + (diffuse * (1.0f-LightAmbient)) * LightPower + LightAmbient;

    //頂点と視点との距離を計算する
   float d = distance( pin.PositionWS.xyz, EyePos.xyz );
    float4 m_FogColor = float4(135.0f / 255.0f, 206.0f / 255.0f, 1, 1); //フォグカラー

   float f = ( Far - d ) / ( Far - Near );
   f = clamp( f, 0.0f, 1.0f );
   //オブジェクトのランバート拡散照明の計算結果とフォグカラーを線形合成する
    float4 Out = color * f + m_FogColor * (1.0f - f);

   // 視線ベクトル
    float3 eyeVector = normalize(EyePosition - pin.PositionWS.xyz);
 
    // ハーフベクトル
    float3 halfVector = normalize(eyeVector - lightDirection);
 
    // スペキュラの影響割合を内積を使い求める
    float dotH = dot(halfVector, worldNormal);
 
    // スペキュラパワーを指数として使いハイライトのかかり具合を調整
    float3 specular = pow(max(dotH, 0) * zeroL, SpecularPower) * dotL;
 
    // ライトのスペキュラ色とマテリアルのスペキュラ色を反映
    specular = specular * LightSpecularColor[0] * SpecularColor;
 
    // スペキュラを加える
    color.rgb += specular * color.a;
 //  discard;
    
    float uvx = pin.PositionWS.y;
        //かりかりかり変更城
    float max = 300.0f;

    if (uvx <= max)
    {
        uvx /= max;
        float wari = uvx;
        uvx = 1 - uvx;
        uvx *= 3;
    
        float4 col = float4(uvx, uvx, uvx, 1);

        return lerp(col, color * float4(2.1f, 1.4f, 0.7f, 1), wari);
    }
    return color * float4(2.1f, 1.4f, 0.7f, 1);
}
