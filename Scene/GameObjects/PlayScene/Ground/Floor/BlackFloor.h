#pragma once
#include"Floor.h"
/// <summary>
/// �n�ʂ̃N���X���`����
/// </summary>
class BlackFloor :public Floor
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BlackFloor();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BlackFloor();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize()override;

};
