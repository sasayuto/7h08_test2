#pragma once
#include"../../Objects.h"

/// <summary>
/// �Ƃ̃N���X���`����
/// </summary>
class House_02 : public Objects
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	House_02();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~House_02()override;

	/// <summary>
/// ����������
/// </summary>
	void Initialize()override;

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update()override;


};
