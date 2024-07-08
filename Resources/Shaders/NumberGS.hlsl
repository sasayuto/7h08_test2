#include "Number.hlsli"

static const unsigned int vnum = 4;

//wが0だと行列計算がおかしくなるので1に変更
static const float4 offset_array[vnum] =
{
	float4( 0.0f,  1.0f, 0.0f, 1.0f),	// 左上
	float4( 0.1f,  1.0f, 0.0f, 1.0f),	// 右上
	float4( 0.0f,  0.0f, 0.0f, 1.0f),	// 左下
	float4( 0.1f,  0.0f, 0.0f, 1.0f),	// 右下

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
		float4 rect = input[0].color;
		float2 pos = (rect.xy / window.xy) * 2.0f;
				//数字は64*64しか使わないので
		float2 size = (float2(640,64) / window.xy);
		float2 scale = input[0].pos.xy;
		//アンカータイプごとに補正する座標を決定する
		uint anc = input[0].pos.z;
		float2 anchor;
		anchor.x = (size.x) * (anc % 3u) * scale.x;
		anchor.y = (size.y) * (anc / 3u) * scale.y;

		//頂点座標等から配置を決める
		element.pos.xy = pos + scale * size * offset_array[i].xy * 2.0f - float2(1.0f,1.0f);
		element.pos.xy -= anchor;
		element.pos.y *= -1;

		//XY平面なので zは0、wは1
		element.pos.z = 0.0f;
		element.pos.w = 1.0f;

		//サイズ変更等のUI化-----------------------------------
		//-----------------------------------------------------

		//色情報（貰った情報は使えないのでとりあえず白）
		element.color = float4(0,input[0].tex.y, 1.0f, 1.0f);

		//テクスチャのUV座標
		element.tex =  float2(offset_array[i].x+input[0].tex.x*0.1f,offset_array[i].y);

		output.Append(element);
	}
	output.RestartStrip();
}