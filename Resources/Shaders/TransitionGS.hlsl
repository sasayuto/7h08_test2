#include "Transition.hlsli"

static const unsigned int vnum = 4;

//w��0���ƍs��v�Z�����������Ȃ�̂�1�ɕύX
static const float4 offset_array[vnum] =
{
	float4(-1,  1, 0.0f, 1),	// ����
	float4( 1,  1, 0.0f, 1),	// �E��
	float4(-1, -1, 0.0f, 1),	// ����
	float4( 1, -1, 0.0f, 1),	// �E��

};

[maxvertexcount(vnum)]
void main(
	point PS_INPUT input[1],
	inout TriangleStream< PS_INPUT > output
)
{

	for (uint i = 0; i < vnum; i++)
	{
		//�W�I���g���o��
		PS_INPUT element;

		element=input[0];

		//���_���W������z�u�����߂�
		element.pos.xy = offset_array[i].xy;

		output.Append(element);
	}
	output.RestartStrip();
}