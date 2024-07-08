#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"Scene/GameObjects/PlayScene/Colliider/CollisionOLL.h"

class Player;

/// <summary>
/// �I�u�W�F�N�g�̊��N���X���`����
/// </summary>
class Objects
{
	
public:
	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	void SetRotateJson(const DirectX::SimpleMath::Vector3& rotate) {
		m_rotate = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(rotate.x),
			DirectX::XMConvertToRadians(rotate.y),
			DirectX::XMConvertToRadians(rotate.z)
		);
	}

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Matrix GetWorld() const { return m_world; }
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { m_world = world; }

	//���f���̂̃Z�b�^�[�A�Q�b�^�[
	DirectX::Model* GetObjectsModel() { return m_objectsModel; }
	void SetObjectsModel(DirectX::Model * objectsModel) { m_objectsModel = objectsModel; }

	//�����蔻��̃Q�b�^�[
	Collider::MultipleHitDetermination* GetCollider() { return m_collider.get(); }

	//��܂��ȓ����蔻��̃Q�b�^�[
	Collider::Sphere* GetRoughCollider() { return m_roughCollider.get(); }

private:
	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;
	//��]�N�I�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotate;

	//��]�N�I�[�^�j�I��
	DirectX::SimpleMath::Matrix m_world;

	//���f���̃|�C���^
	DirectX::Model* m_objectsModel;

	//�����蔻��̃|�C���^
	std::unique_ptr<Collider::MultipleHitDetermination> m_collider;

	//��܂��ȓ����蔻��̃|�C���^
	std::unique_ptr<Collider::Sphere> m_roughCollider;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Objects();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Objects();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update();

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render();

	/// <summary>
	/// �V���h�E�}�b�v�p�̉摜�����
	/// </summary>
	virtual void RenderShadowTex();

	/// <summary>
	/// �G�������_���ɐ���
	/// </summary>
	/// <param name="min">�ŏ�</param>
	/// <param name="max">�ő�</param>
	void SetpositionRandam(const float& min, const float& max);

};
