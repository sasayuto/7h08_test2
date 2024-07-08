#include "UI.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//トムの画像表示
	float4 output = tex.Sample(samLinear, input.tex);

	float green = 1 - input.color.x;

	//真っ白な板ポリゴン
	float4 white = float4(green, input.color.x, 0,input.color.w);
	
	return output*white;
}