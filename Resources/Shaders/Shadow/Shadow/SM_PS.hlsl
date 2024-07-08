#include "SM_Common.hlsli"

Texture2D<float4> Texture : register(t0);
// シャドウマップテクスチャ
Texture2D ShadowMapTexture[MAX_CASCADE] : register(t3);
// シャドウマップテクスチャ
Texture2D MoveShadowMapTexture[MAX_CASCADE] : register(t7);
sampler Sampler : register(s0);

// シャドウマップ用テクスチャサンプラー
SamplerComparisonState ShadowMapSampler : register(s1);

struct Input
{
    float2 TexCoord     : TEXCOORD0;
    float4 PositionWS   : TEXCOORD1;
    float3 NormalWS     : TEXCOORD2;
    float4 LightPosPS[MAX_CASCADE] : TEXCOORD3;
    float4 MoveLightPosPS[MAX_CASCADE] : TEXCOORD7;
};

// マッハバンド対策
#define SHADOW_EPSILON 0.0004f

float4 main(Input pin) : SV_TARGET0
{
    // ライトの向きを求める
    float lightlength = length(pin.PositionWS.xyz);
    float4 diffuse;
    float3 specular = 0;
    float percentLit = 1;
    float cascadeNum = -1;

            //どのライトが何回あたってるか調べる
    for (int i = 0; i < MAX_CASCADE; i++)
        {
        //ライトまでの方向
            float targetLength = length(pin.PositionWS.xyz - StaticTargetPosition);
             // ------------------------------------------------------------------------------- //
            //シャドウマップの影の計算
            // ------------------------------------------------------------------------------- //
            // 正規化デバイス座標にする
                    //範囲内か
            if (targetLength < Lightdistance[i].w)
            {

            float4 lightPosPS = pin.LightPosPS[i];
            lightPosPS.xyz /= lightPosPS.w;

            // 参照するシャドウマップのUV値を求める
            float2 uv = lightPosPS.xy * float2(0.5f, -0.5f) + 0.5f;
            
            percentLit *= (ShadowMapTexture[i].SampleCmpLevelZero(ShadowMapSampler, uv, lightPosPS.z - SHADOW_EPSILON).x);
              break;
            }
        }
                //どのライトが何回あたってるか調べる
      for (int x = 0; x < MAX_CASCADE; x++)
        {
         //ライトまでの方向
            float targetLength = length(pin.PositionWS.xyz - DynamicTargetPosition);
             // ------------------------------------------------------------------------------- //
            //シャドウマップの影の計算
            // ------------------------------------------------------------------------------- //
            // 正規化デバイス座標にする
                    //範囲内か
            if (targetLength < Lightdistance[x].w)
            {
                pin.MoveLightPosPS[x].xyz /= pin.MoveLightPosPS[x].w;

            // 参照するシャドウマップのUV値を求める
                float2 moveUV = pin.MoveLightPosPS[x].xy * float2(0.5f, -0.5f) + 0.5f;

                percentLit *= (MoveShadowMapTexture[x].SampleCmpLevelZero(ShadowMapSampler, moveUV, pin.MoveLightPosPS[x].z - SHADOW_EPSILON).x);
                cascadeNum = x;
                break;
            }
        }
    // ------------------------------------------------------------------------------- //
    // ディフューズ
    // ------------------------------------------------------------------------------- //
        //    //cascadeの位置の色
        //float cascadeShadow[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        //float3 shadowColor = 1;
        //if (cascadeNum != -1)
        //{
    
        //    for (int i = 0; i < 4; i++)
        //        if (cascadeNum == i)
        //            cascadeShadow[i] += 1;
        //    shadowColor = float3(cascadeShadow[0] + cascadeShadow[3] * 2, cascadeShadow[1], cascadeShadow[2]);
        //}


    // 法線を正規化
        float3 worldNormal = normalize(pin.NormalWS);

    // 光の強さを内積から算出する
    float3 dotL = saturate(dot(-LightDir, worldNormal));

    // ライトによる明るさを求める
    float3 lightAmount = dotL * percentLit * (1.0f - LightAmbient) + LightAmbient;

    // ディフューズ色を求める 
        diffuse = float4(DiffuseColor.rgb * lightAmount, DiffuseColor.a);

    // ------------------------------------------------------------------------------- //
    // スペキュラ
    // ------------------------------------------------------------------------------- //
    
         // 視線ベクトル
        float3 eyeVector = normalize(EyePosition - pin.PositionWS.xyz);

        // ハーフベクトル
        float3 halfVector = normalize(eyeVector - LightDir);

        // スペキュラの影響割合を内積を使い求める
        float dotH = saturate(dot(halfVector, worldNormal));

        // スペキュラパワーを指数として使いハイライトのかかり具合を調整
        specular = pow(dotH, SpecularPower) * dotL * SpecularColor * percentLit;
    // ------------------------------------------------------------------------------- //
    
        // テクスチャ色を掛ける 
    float4 color = Texture.Sample(Sampler, pin.TexCoord) * diffuse;

    float4 m_FogColor = float4(1,1, 1, 1); //フォグカラー

//頂点と視点との距離を計算する
    float d = distance(pin.PositionWS.xyz, EyePosition);

    float f = (Far - d) / (Far - Near);
    f = clamp(f, 0.0f, 1.0f);
    
   //オブジェクトのランバート拡散照明の計算結果とフォグカラーを線形合成する
    float4 Out = color * f * float4(3,2,1,1) + m_FogColor * (1.0f - f);

      // スペキュラを加える
    Out.rgb += specular * diffuse.a;

    return Out;
}


