#pragma once

#include "ImaseLib/MoveUserInterface.h"

/// <summary>
/// �X�e�[�W�I��UI�̃N���X���`����
/// </summary>
class UnderBar
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	UnderBar();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~UnderBar();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& positionAnchor
	);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(int selectNum);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

//private:
	/// <summary>
	/// UI�����
	/// </summary>
	/// <param name="path">�Q�[�W�̉摜</param>
	/// <param name="basePath">�w�i�̉摜</param>
	/// <param name="position">�`��ʒu</param>
	/// <param name="scale">�傫��</param>
	/// <param name="anchor">�摜�̕`��J�n�ʒu</param>
	/// <param name="anchor">��ʂ̕`��J�n�ʒu</param>
	void Add(
		const wchar_t* path,
		const wchar_t* pathBase,
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& positionAnchor
	);

private:
	//�Q�[�W�ƃx�[�X�̃|�C���^
	std::unique_ptr<tito::MoveUserInterface> m_underBar;

	DirectX::SimpleMath::Vector2 m_position;
};
