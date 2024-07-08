

Texture2D<float4> Texture : register(t0);
sampler Sampler : register(s0);


cbuffer Parameters : register(b0)
{
    float4 DiffuseColor             : packoffset(c0);
    float3 EmissiveColor            : packoffset(c1);
    float3 SpecularColor            : packoffset(c2);
    float  SpecularPower : packoffset(c2.w);

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

cbuffer Parameters : register(b1)
{
    float Att0 : packoffset(c0.x);
    float Att1 : packoffset(c0.y);
    float Att2 : packoffset(c0.z);
    float3 SpotLight :  packoffset(c1);
    float3 LightPosition : packoffset(c2);
};

struct PSInputPixelLightingTx
{
    float2 TexCoord     : TEXCOORD0;
    float4 PositionWS   : TEXCOORD1;
    float3 NormalWS     : TEXCOORD2;
    float4 Diffuse      : COLOR0;
};

// Pixel shader: pixel lighting.
float4 main(PSInputPixelLightingTx pin) : SV_TARGET
{

//if (abs(6 - pin.PositionWS.z) > 200 || abs(42 - pin.PositionWS.x) > 300)
//{
//    discard;
//}

// ŒõŒ¹‚Ì•ûŒü
//  discard;

return float4(0,0,0,0.8f);
}
