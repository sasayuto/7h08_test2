#include "Gauge.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//ƒgƒ€‚Ì‰æ‘œ•\Ž¦
	float4 output = tex.Sample(samLinear, input.tex);


	output.a *= lerp(1.0f, 0.0f, step(input.color.x, input.tex.x));
	output.a *= input.color.y;
	return output;
}