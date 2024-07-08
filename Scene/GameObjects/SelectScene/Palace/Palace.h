#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"Scene/GameObjects/Models/Resources.h"

/// <summary>
/// �A�C�e���̊��N���X���`����
/// </summary>
class Palace
{
public:
	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

private:
	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;

	//�ʒu
	DirectX::SimpleMath::Quaternion m_rotate;

	//���f���̃|�C���^
	DirectX::Model* m_pModel;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Palace();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Palace();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	void Update(const float& elapsedTime);


	/// <summary>
	/// �V���h�E�}�b�v�p�̉摜�����
	/// </summary>
	virtual void RenderShadowTex();

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize();
};
