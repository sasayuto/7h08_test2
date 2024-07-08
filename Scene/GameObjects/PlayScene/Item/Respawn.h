#pragma once
#include"Item.h"

/// <summary>
/// ���X�|�[���n�_�̃N���X���`����
/// </summary>
class Respawn : public Item
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Respawn();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Respawn()override;

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	void Update(const float& elapsedTime)override;

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render()override;

	/// <summary>
	/// �񕜂�������
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X/param>
	void Recovery(Player* player) override;
};
