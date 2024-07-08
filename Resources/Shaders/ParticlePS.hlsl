#include "Particle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//トムの画像表示
	float4 output = tex.Sample(samLinear, input.Tex);

    float3 Alpha = float3(brightness.x, brightness.x, brightness.x);

	float3 emissiveColor = float3(brightness.y,brightness.z,brightness.w);
    
    // 光の影響を掛ける
    output.rgb += emissiveColor;

    //頂点と視点との距離を計算する
   float d = distance( input.Pos.xyz, EyePos.xyz );
    float4 m_FogColor = float4(1,1, 1, 1); //フォグカラー

   float f = ( EyePos.w - d ) / ( EyePos.w - input.FogNear );
   f = clamp( f, 0.0f, 1.0f );
   //オブジェクトのランバート拡散照明の計算結果とフォグカラーを線形合成する
    float4 Out = output * input.Color/* * f + FogColor * (1.0f - f)*/;

    return Out;
}