#include "Particle.hlsli"

Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//�g���̉摜�\��
	float4 output = tex.Sample(samLinear, input.Tex);

    float3 Alpha = float3(brightness.x, brightness.x, brightness.x);

	float3 emissiveColor = float3(brightness.y,brightness.z,brightness.w);
    
    // ���̉e�����|����
    output.rgb += emissiveColor;

    //���_�Ǝ��_�Ƃ̋������v�Z����
   float d = distance( input.Pos.xyz, EyePos.xyz );
    float4 m_FogColor = float4(1,1, 1, 1); //�t�H�O�J���[

   float f = ( EyePos.w - d ) / ( EyePos.w - input.FogNear );
   f = clamp( f, 0.0f, 1.0f );
   //�I�u�W�F�N�g�̃����o�[�g�g�U�Ɩ��̌v�Z���ʂƃt�H�O�J���[����`��������
    float4 Out = output * input.Color/* * f + FogColor * (1.0f - f)*/;

    return Out;
}