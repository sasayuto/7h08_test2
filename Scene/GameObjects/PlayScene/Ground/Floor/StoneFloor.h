#pragma once
#include"Floor.h"
/// <summary>
/// �n�ʂ̃N���X���`����
/// </summary>
class StoneFloor :public Floor
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	StoneFloor();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~StoneFloor();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize()override;

};
