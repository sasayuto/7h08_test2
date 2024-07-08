#include "SM_Common.hlsli"

struct Input
{
    float4 Position     : SV_Position;
    float3 Normal       : NORMAL;
    float2 TexCoord     : TEXCOORD0;
    float4 Color        : COLOR;
};

struct Output
{
    float2 TexCoord     : TEXCOORD0;
    float4 PositionWS   : TEXCOORD1;
    float3 NormalWS     : TEXCOORD2;
    float4 LightPosPS[MAX_CASCADE] : TEXCOORD3;
    float4 MoveLightPosPS[MAX_CASCADE] : TEXCOORD7;
    float4 PositionPS   : SV_Position;
};

Output main(Input vin)
{
    Output output;

    // ���_�̈ʒu�𓊉e��Ԃ�
    output.PositionPS = mul(vin.Position, WorldViewProj);
    // ���_�̈ʒu�����[���h��Ԃ�
    output.PositionWS = mul(vin.Position, World);
    // �@���x�N�g�������[���h��Ԃցi�g��k���̉e����ł��������ߋt�]�u�s���������j
    output.NormalWS = mul(vin.Normal, WorldInverseTranspose);
    // �e�N�X�`����UV���W
    output.TexCoord = vin.TexCoord;
    // ���_�̈ʒu�����C�g�̓��e��Ԃ�
    for (int i = 0; i < MAX_CASCADE; i++)
    {
        output.LightPosPS[i] = mul(output.PositionWS, LightViewProj[i]);
        output.MoveLightPosPS[i] = mul(output.PositionWS, MoveLightViewProj[i]);
    } 
    return output;
}