#include "UI.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    float2 uv = input.tex;

    // ゆがみの速度を設定
    float distortionSpeed = 0.15f; // ゆがみの速度

    // ゆがみの速度を設定
    float distortionStrengthConstant = 0.008f; // ゆがみの強度

    // ゆがみのエフェクトを計算
    float time = windowSize.z;

    float distortionOffsetX = sin(time * distortionSpeed + uv.y) * distortionStrengthConstant;

    // ゆがんだテクスチャ座標を計算
    uv.x += distortionOffsetX;

    // ゆがんだテクスチャから色をサンプリング
    float4 output = tex.Sample(samLinear, uv);
    	//真っ白な板ポリゴン
	float4 white = float4(1, 1, 1, input.color.y);

    return output * white;
}