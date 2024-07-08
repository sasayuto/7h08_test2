#pragma once

#include "ImaseLib/GaugeManager.h"

class Player;

/// <summary>
/// �Q�[�W�̃N���X���`����
/// </summary>
class Gaueg
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="m_player">�v���C���[�̃|�C���^</param>
	Gaueg(Player* m_player);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Gaueg();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();


	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

	/// <summary>
	/// �Q�[�W�����
	/// </summary>
	/// <param name="path">�Q�[�W�̉摜</param>
	/// <param name="basePath">�w�i�̉摜</param>
	/// <param name="position">�`��ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="anchor">�`��J�n�ʒu</param>
	void Add(
		const wchar_t* path,
		const wchar_t* basePath,
		const wchar_t* framePath,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& posotionAnchor
	);

private:
	//�Q�[�W�ƃx�[�X�̃|�C���^
	std::vector<std::unique_ptr<tito::GaugeManager>> m_gaueg, m_baes, m_frame;

	//�v���C���[�̃|�C���^
	Player* m_player;
};
