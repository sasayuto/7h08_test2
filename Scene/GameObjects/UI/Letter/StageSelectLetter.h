#pragma once

#include "ImaseLib/UserInterface.h"

/// <summary>
/// �X�e�[�W�I��UI�̃N���X���`����
/// </summary>
class StageSelectLetter
{
public:
	void SetPath(const wchar_t* path) { m_path = path; }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	StageSelectLetter();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~StageSelectLetter();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const DirectX::SimpleMath::Vector2& position,
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

	const wchar_t* m_path;
	//�Q�[�W�ƃx�[�X�̃|�C���^
	std::unique_ptr<tito::UserInterface> m_titleName, m_titleNameBase;
};
