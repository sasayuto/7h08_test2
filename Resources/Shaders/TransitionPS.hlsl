#include "Transition.hlsli"

float4 main(PS_INPUT input) : SV_TARGET
{
	//真っ白な板ポリゴン
	float4 outputw = float4(0, 0, 0, input.color.w);

	
	return outputw;
}