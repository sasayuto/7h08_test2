#include "UI.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
    float2 uv = input.tex;

    // �䂪�݂̑��x��ݒ�
    float distortionSpeed = 0.15f; // �䂪�݂̑��x

    // �䂪�݂̑��x��ݒ�
    float distortionStrengthConstant = 0.008f; // �䂪�݂̋��x

    // �䂪�݂̃G�t�F�N�g���v�Z
    float time = windowSize.z;

    float distortionOffsetX = sin(time * distortionSpeed + uv.y) * distortionStrengthConstant;

    // �䂪�񂾃e�N�X�`�����W���v�Z
    uv.x += distortionOffsetX;

    // �䂪�񂾃e�N�X�`������F���T���v�����O
    float4 output = tex.Sample(samLinear, uv);
    	//�^�����Ȕ|���S��
	float4 white = float4(1, 1, 1, input.color.y);

    return output * white;
}