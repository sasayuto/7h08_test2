#include "UI.hlsli"

static const unsigned int vnum = 4;

//wが0だと行列計算がおかしくなるので1に変更
static const float4 offset_array[vnum] =
{
	float4( 0.0f,  1.0f, 0.0f, 1.0f),	// 左上
	float4( 1.0f,  1.0f, 0.0f, 1.0f),	// 右上
	float4( 0.0f,  0.0f, 0.0f, 1.0f),	// 左下
	float4( 1.0f,  0.0f, 0.0f, 1.0f),	// 右下

};

[maxvertexcount(vnum)]
void main(
	point PS_INPUT input[1],
	inout TriangleStream< PS_INPUT > output
)
{

	for (uint i = 0; i < vnum; i++)
	{
		//ジオメトリ出力
		PS_INPUT element;
		
		//頂点に入れていた諸々を受け取る
		float2 window = float2(windowSize.xy);
		float2 pos = (input[0].pos.xy / window.xy) * 2.0f;
		float2 size = (input[0].tex / window.xy);

		//アンカータイプごとに補正する座標を決定する
		uint anc = input[0].pos.z;
		float2 anchor;
		anchor.x = (size.x) * (anc % 3u);
		anchor.y = (size.y) * (anc / 3u);

		uint posanc = input[0].color.w;
		float2 posanchor;
		posanchor.x = (posanc % 3u);
		posanchor.y = (posanc / 3u);

		//頂点座標等から配置を決める
		element.pos.xy = pos + size * offset_array[i].xy * 2.0f - float2(1.0f,1.0f);
		element.pos.xy -= anchor;
		element.pos.xy += posanchor;
		element.pos.y *= -1;

		//XY平面なので zは0、wは1
		element.pos.z = 0.0f;
		element.pos.w = 1.0f;

		//サイズ変更等のUI化-----------------------------------
		//-----------------------------------------------------

		element.color = float4(input[0].color.x,input[0].color.x,input[0].color.x,input[0].color.y);
		//テクスチャのUV座標
		element.tex =  offset_array[i].xy;

		output.Append(element);
	}
	output.RestartStrip();
}