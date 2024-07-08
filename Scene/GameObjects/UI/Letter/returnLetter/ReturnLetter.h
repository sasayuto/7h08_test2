#pragma once

#include "ImaseLib/MoveUserInterface.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
/// <summary>
/// �^�C�g�����̃N���X���`����
/// </summary>
class ReturnLetter
{
public:

	bool GetMouseFlag() const { return m_mouseFlag; }

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="m_player">�v���C���[�̃|�C���^</param>
	ReturnLetter();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~ReturnLetter();

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

	Collider::Box2D* GetCollider() { return m_collider.get(); };
private:
	//�Q�[�W�ƃx�[�X�̃|�C���^
	std::unique_ptr<tito::MoveUserInterface> m_returnLetter;

	//�����蔻��
	std::unique_ptr<Collider::Box2D> m_collider;

	//�}�E�X�Ƃ������Ă��邩
	bool m_mouseFlag;
};
