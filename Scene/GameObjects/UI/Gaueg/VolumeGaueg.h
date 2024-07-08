#pragma once

#include "ImaseLib/GaugeManager.h"
#include "ImaseLib/MoveUserInterface.h"
#include "Scene/GameObjects/PlayScene/Colliider/Collision.h"

/// <summary>
/// �Q�[�W�̃N���X���`����
/// </summary>
class VolumeGaueg
{

public:

	static const int TEXTURE_ANCHOR_RATIO_NUM;

	//�Q�[�W�̊������擾
	float GetRatio() const { return m_ratio; }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="m_player">�v���C���[�̃|�C���^</param>
	VolumeGaueg();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~VolumeGaueg();

	/// <summary>
	///  ������
	/// </summary>
	/// <param name="position">�ʒu</param>
	/// <param name="scale">�傫���i��{�P�j</param>
	/// <param name="anchor">�摜�̂ǂ̒[����`�悷�邩</param>
	/// <param name="positionAnchor">�X�N���[�����W�̂ǂ̒[����`�悷�邩</param>
	void Initialize(
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& positionAnchor,
		const float& ratio
	);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();
	void SetRatio(const float& ratio);

private:
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
		const DirectX::SimpleMath::Vector2& position,
		const DirectX::SimpleMath::Vector2& scale,
		const tito::ANCHOR& anchor,
		const tito::POSITION_ANCHOR& positionAnchor
	);
	//�Q�[�W�ƃx�[�X�̃|�C���^
	std::unique_ptr<tito::GaugeManager>  m_baes, m_frame;

	std::unique_ptr<tito::MoveUserInterface>  m_bottom;

	//Button�̏����ʒu
	DirectX::SimpleMath::Vector2 m_initialBottonPosition;

	//Button�̈ʒu
	DirectX::SimpleMath::Vector2 m_BottonPosition;

	//Button�������ꂽ��
	bool m_BottonFlag;

	//�{�^�����������Ƃ���x���W
	float m_pressedMousePos_x;
	float m_bottonPosStorage_x;

	float m_ratio;
	std::unique_ptr<Collider::Box2D> m_collider;
};
