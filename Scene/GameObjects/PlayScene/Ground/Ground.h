#pragma once
#include"Floor/Floor.h"
/// <summary>
/// �n�ʂ̃N���X���`����
/// </summary>
class Ground:public Floor
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Ground();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Ground();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize()override;
};
