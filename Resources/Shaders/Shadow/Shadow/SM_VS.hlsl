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

    // 頂点の位置を投影空間へ
    output.PositionPS = mul(vin.Position, WorldViewProj);
    // 頂点の位置をワールド空間へ
    output.PositionWS = mul(vin.Position, World);
    // 法線ベクトルをワールド空間へ（拡大縮小の影響を打ち消すため逆転置行列をかける）
    output.NormalWS = mul(vin.Normal, WorldInverseTranspose);
    // テクスチャのUV座標
    output.TexCoord = vin.TexCoord;
    // 頂点の位置をライトの投影空間へ
    for (int i = 0; i < MAX_CASCADE; i++)
    {
        output.LightPosPS[i] = mul(output.PositionWS, LightViewProj[i]);
        output.MoveLightPosPS[i] = mul(output.PositionWS, MoveLightViewProj[i]);
    } 
    return output;
}
