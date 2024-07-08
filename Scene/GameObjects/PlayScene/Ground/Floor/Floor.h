#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"

class Player;
class Enemy;
/// <summary>
/// �n�ʂ̃N���X���`����
/// </summary>
class Floor
{
public:
	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//���f���̂̃Z�b�^�[�A�Q�b�^�[
	DirectX::Model* GetModel() { return m_objectsModel; }
	void SetModel(DirectX::Model * objectsModel) { m_objectsModel = objectsModel; }
	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//�����蔻��̃Q�b�^�[
	Collider::OBB* GetCollider() { return m_collider.get(); }

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Floor();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Floor();

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
	/// �v���C���[�Ɠ����蔻��
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	virtual void CheckHitPlayer(Player* player);

	/// <summary>
	/// �v���C���[�Ɠ����蔻��
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	virtual void CheckHitEnemy(Enemy* enemy);

private:
	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;

	//�ʒu
	DirectX::SimpleMath::Quaternion m_rotate;

	//���f���̃|�C���^
	DirectX::Model* m_objectsModel;

	//�����蔻��̃|�C���^
	std::unique_ptr<Collider::OBB> m_collider;

};
