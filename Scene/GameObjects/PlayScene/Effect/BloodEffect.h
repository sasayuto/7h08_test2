#pragma once

#include "ImaseLib/GaugeManager.h"

/// <summary>
/// ���̃G�t�F�N�g�̃N���X���`����
/// </summary>
class BloodEffect
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="m_player">�v���C���[�̃|�C���^</param>
	BloodEffect();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BloodEffect();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();


	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="HP">�v���C���[��HP</param>
	void Update(int HP);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

	/// <summary>
	/// �Q�[�W�����
	/// </summary>
	/// <param name="path">�Q�[�W�̉摜</param>
	/// <param name="position">�`��ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="anchor">�`��J�n�ʒu</param>
	void Add(
		const wchar_t* path,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& positionAnchor
	);

private:
	//�Q�[�W�ƃx�[�X�̃|�C���^
	std::unique_ptr<tito::GaugeManager> m_bloodEffect;
};