#include "SM_Common.hlsli"

static const unsigned int vnum = 3;
struct Input
{
    float2 TexCoord : TEXCOORD0;
    float4 PositionWS : TEXCOORD1;
    float3 NormalWS : TEXCOORD2;
    float4 LightPosPS : TEXCOORD3;
};

struct Output
{
    float2 TexCoord : TEXCOORD0;
    float4 PositionWS : TEXCOORD1;
    float3 NormalWS : TEXCOORD2;
    float4 LightPosPS : TEXCOORD3;
    float4 PositionPS : SV_Position;
};

[maxvertexcount(3)]
void GSmain(
  triangle Input In[1],
  inout TriangleStream<Input> stream)
{
    for (int i = 0; i < 3; ++i)
    {
        Input v;
        v.LightPosPS = In[0].LightPosPS;
        v.NormalWS = In[0].NormalWS;
        v.PositionWS = In[0].PositionWS;
        v.TexCoord = In[0].TexCoord;
        stream.Append(v);
    }
    stream.RestartStrip();
}