#pragma once

#include "ImaseLib/NumberManager.h"


/// <summary>
/// �Q�[�W�̃N���X���`����
/// </summary>
class ScoreTex
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="m_player">�v���C���[�̃|�C���^</param>
	ScoreTex();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ScoreTex();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const int& timer,
		const tito::ANCHOR& anchor
	);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(const int& timer);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

	/// <summary>
private:
	//�Q�[�W�ƃx�[�X�̃|�C���^
	std::vector<std::unique_ptr<tito::NumberManager>> m_ScoreTex;

	DirectX::SimpleMath::Vector2 m_position;
	DirectX::SimpleMath::Vector2 m_scale;
	float m_timer;
	tito::ANCHOR m_anchor;
};
