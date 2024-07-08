#pragma once

#include "ImaseLib/MoveUserInterface.h"

class Player;

/// <summary>
/// �^�C�g�����̃N���X���`����
/// </summary>
class SpaseLetter
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="m_player">�v���C���[�̃|�C���^</param>
	SpaseLetter();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SpaseLetter();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(const float& nowTime);

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
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& positionAnchor
	);

private:
	//�Q�[�W�ƃx�[�X�̃|�C���^
	std::unique_ptr<tito::MoveUserInterface> m_SpaseLetter;

	//�`��X�^�[�g����
	float m_timer;

	//�����x
	float m_transparency;

	//�����x
	bool m_transparencyFlag;
};
