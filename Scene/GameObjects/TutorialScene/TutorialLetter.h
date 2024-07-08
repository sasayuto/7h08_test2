#pragma once

#include "ImaseLib/MoveUserInterface.h"

/// <summary>
/// �X�e�[�W�I��UI�̃N���X���`����
/// </summary>
class TutorialLetter
{
public:

	static const float TRANSPARENT_END_TIME;

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	TutorialLetter();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TutorialLetter();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const wchar_t* path,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& positionAnchor);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(const float& elapsedTime);

	/// <summary>
	/// �X�V����
	/// </summary>
	void ReduceTransparency(const float& elapsedTime);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

private:
	//�Q�[�W�ƃx�[�X�̃|�C���^
	std::unique_ptr<tito::MoveUserInterface> m_titleName;
	//�`��X�^�[�g����
	float m_timer;

	//�����x
	float m_transparency;
};
