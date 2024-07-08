#pragma once
#include"Item.h"

/// <summary>
/// �R���⋋�̃N���X���`����
/// </summary>
class FuelSupplyPoint : public Item
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	FuelSupplyPoint();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~FuelSupplyPoint()override;

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime"></param>
	void Update(const float& elapsedTime)override;

	/// <summary>
	/// �񕜂�������
	/// </summary>
	/// <param name="player">�v���C���[�̃|�C���^</param>
	void Recovery(Player* player) override;
};
