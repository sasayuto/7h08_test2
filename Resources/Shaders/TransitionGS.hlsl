#include "Transition.hlsli"

static const unsigned int vnum = 4;

//wが0だと行列計算がおかしくなるので1に変更
static const float4 offset_array[vnum] =
{
	float4(-1,  1, 0.0f, 1),	// 左上
	float4( 1,  1, 0.0f, 1),	// 右上
	float4(-1, -1, 0.0f, 1),	// 左下
	float4( 1, -1, 0.0f, 1),	// 右下

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

		element=input[0];

		//頂点座標等から配置を決める
		element.pos.xy = offset_array[i].xy;

		output.Append(element);
	}
	output.RestartStrip();
}