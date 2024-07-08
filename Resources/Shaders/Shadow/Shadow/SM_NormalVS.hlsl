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
    float4 LightPosPS[4] : TEXCOORD3;
    float4 MoveLightPosPS[4] : TEXCOORD7;
    float3 LightTangentDirectPS : TEXCOORD11;
    float4 PositionPS   : SV_Position;
};

float4x4 InvTangentMatrix(
   float3 tangent,
   float3 binormal,
   float3 normal)
{
    float4x4 mat =
    {
        float4(tangent, 0.0f),
        float4(binormal, 0.0f),
        float4(normal, 0.0f),
        { 0, 0, 0, 1 }
    };
    return transpose(mat); // �]�u
}
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
    for (int i = 0; i < 4; i++)
    {
        output.LightPosPS[i] = mul(output.PositionWS, LightViewProj[i]);
        output.MoveLightPosPS[i] = mul(output.PositionWS, MoveLightViewProj[i]);
    }
    
    float3 normal = normalize(vin.Normal);
    float3 tangent;
    float3 c1 = cross(normal, float3(0, 1, 0));
    float3 c2 = cross(normal, float3(0, 0, 1));

// Use dot product to compare lengths
    if (dot(c2, c2) < dot(c1, c1))
        tangent = normalize(c1);
    else
        tangent = normalize(c2);

    float3 binormal = normalize(cross(normal, tangent));

// Make sure LightDir is in world space before transforming
    float3 worldLightDir = normalize(mul(float4(LightDir, 0.0f), World).xyz);

// Transform the light direction to tangent space
    output.LightTangentDirectPS = mul(float4(worldLightDir, 0.0f), InvTangentMatrix(tangent, binormal, normal)).xyz;
    return output;
}
