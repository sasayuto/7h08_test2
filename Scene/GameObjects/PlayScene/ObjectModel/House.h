#pragma once
#include"Objects.h"

/// <summary>
/// �Ƃ̃N���X���`����
/// </summary>
class House : public Objects
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	House();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~House()override;

	/// <summary>
/// ����������
/// </summary>
	void Initialize()override;


};
