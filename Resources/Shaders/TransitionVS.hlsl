#include "Transition.hlsli"

PS_INPUT main(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;


	output.color = input.color;
	return output;
}