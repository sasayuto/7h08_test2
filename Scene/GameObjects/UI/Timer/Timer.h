#pragma once

#include "ImaseLib/NumberManager.h"


/// <summary>
/// �Q�[�W�̃N���X���`����
/// </summary>
class TimerTex
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="m_player">�v���C���[�̃|�C���^</param>
	TimerTex();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~TimerTex();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const float& timer,
		const tito::ANCHOR& anchor
	);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(const float& timer);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Finalize();

	/// <summary>
private:
	//�Q�[�W�ƃx�[�X�̃|�C���^
	std::vector<std::unique_ptr<tito::NumberManager>> m_timerTex;
};
