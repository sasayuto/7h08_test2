static const int MAX_CASCADE = 4;

cbuffer Parameters : register(b0)
{
    float4 DiffuseColor             : packoffset(c0);
    float3 EmissiveColor            : packoffset(c1);
    float3 SpecularColor            : packoffset(c2);
    float SpecularPower             : packoffset(c2.w);

    float3 LightDirection[3]        : packoffset(c3);
    float3 LightDiffuseColor[3]     : packoffset(c6);
    float3 LightSpecularColor[3]    : packoffset(c9);

    float3 EyePosition              : packoffset(c12);

    float3 FogColor                 : packoffset(c13);
    float4 FogVector                : packoffset(c14);

    float4x4 World                  : packoffset(c15);
    float3x3 WorldInverseTranspose  : packoffset(c19);
    float4x4 WorldViewProj          : packoffset(c22);
};

// �ǉ�����萔�o�b�t�@
cbuffer Parameters : register(b1)
{
    float4x4 LightViewProj[MAX_CASCADE] : packoffset(c0);
    float4x4 MoveLightViewProj[MAX_CASCADE] : packoffset(c16);
    float4 Lightdistance[MAX_CASCADE] : packoffset(c32);
    float3 StaticTargetPosition : packoffset(c36);
    float3 DynamicTargetPosition : packoffset(c37);
    float3 LightDir : packoffset(c38);
    float3 LightAmbient : packoffset(c39);
    float Near : packoffset(c40.x);
    float Far : packoffset(c40.y);
};

