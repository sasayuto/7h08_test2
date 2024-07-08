#pragma once

#include "ImaseLib/UserInterface.h"

/// <summary>
/// �X�e�[�W�I��UI�̃N���X���`����
/// </summary>
class FreeUi
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	FreeUi();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~FreeUi();

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
	void Update();

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

private:
	//�Q�[�W�ƃx�[�X�̃|�C���^
	std::unique_ptr<tito::UserInterface> m_titleName;
};
