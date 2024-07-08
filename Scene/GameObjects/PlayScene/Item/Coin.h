#pragma once
#include"Item.h"
#include"Scene/GameObjects/PlayScene/Effect/LightEffect.h"

/// <summary>
/// �R�C���̃N���X���`����
/// </summary>
class Coin : public Item
{
private:
	//���̃G�t�F�N�g�̃|�C���^
	std::unique_ptr<LightEffect> m_lightEffect;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Coin();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Coin()override;

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
	/// �`�悷��
	/// </summary>
	void Render()override;

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize()override;

};
