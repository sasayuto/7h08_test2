#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"Scene/GameObjects/Models/Resources.h"
class Player;

/// <summary>
/// �A�C�e���̊��N���X���`����
/// </summary>
class Item
{
public:
	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//�傫���̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetScale() const { return m_scale; }
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }

	//�g�p�t���O�̃Z�b�^�[�A�Q�b�^�[
	bool GetSurvival() const { return m_survival; }
	void SetSurvival(const bool& survival) { m_survival = survival; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Matrix GetWorld() const { return m_world; }
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { m_world = world; }

	//���f���̃Z�b�^�[�A�Q�b�^�[
	DirectX::Model* GetSupplyPointModel() { return m_pSupplyPointModel; }
	void SetSupplyPointModel(DirectX::Model* supplyPointModel) { m_pSupplyPointModel = supplyPointModel; }

	//�����蔻��̃Q�b�^�[
	Collider::Sphere* GetCollider() { return m_collider.get(); }

private:
	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;

	//�ʒu
	DirectX::SimpleMath::Quaternion m_rotate;

	//�傫��
	DirectX::SimpleMath::Vector3 m_scale;

	//�g�p�t���O
	bool m_survival;

	//���f���̃|�C���^
	DirectX::Model* m_pSupplyPointModel;

	//�����蔻��̃|�C���^
	std::unique_ptr<Collider::Sphere> m_collider;
	DirectX::SimpleMath::Matrix m_world;

public:
	//�~�Ƀ����_���ɐ���
	void SetpositionRandam(const float& min, const float& max);

	/// <summary>
	/// �񕜂�������
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	virtual void Recovery(Player* player);

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Item();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Item();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	virtual void Update(const float& elapsedTime);

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render();

	/// <summary>
	/// �V���h�E�}�b�v�p�̉摜�����
	/// </summary>
	virtual void RenderShadowTex();

	/// <summary>
	/// ��n��
	/// </summary>
	virtual void Finalize();
};
