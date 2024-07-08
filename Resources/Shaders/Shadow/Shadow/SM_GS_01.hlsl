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
void main(
  triangle Output In[3],
  inout TriangleStream<Input> stream)
{
    for (int i = 0; i < 3; ++i)
    {
        Input v;
        v.LightPosPS = In[i].LightPosPS;
        v.NormalWS = In[i].NormalWS;
        v.PositionWS = In[i].PositionWS;
        v.TexCoord = In[i].TexCoord;
        stream.Append(v);
    }
    stream.RestartStrip();
}