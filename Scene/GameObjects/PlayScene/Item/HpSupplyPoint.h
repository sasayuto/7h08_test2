#pragma once
#include"Item.h"

/// <summary>
/// HP�⋋�̃N���X���`����
/// </summary>
class HpSupplyPoint : public Item
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	HpSupplyPoint();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~HpSupplyPoint()override;

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
private:
	static const int REPLENISHMENT_HP;
};
