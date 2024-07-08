#pragma once
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"

/// <summary>
/// ���̊��N���X���`����
/// </summary>
class Bullet
{
public:
	//���̎g�p��
	enum class BulletParent
	{
		None,
		PlayerBullet,
		EnemyBullet,
		OverID
	};

	//���̎��
	enum class BulletType
	{
		None,
		Type1,
		Type2,
		Type3,
		Type4,
		Turret,
		OverID
	};

	//�g�p���̃Q�b�^�[�A�Z�b�^�[
	bool GetisActive() const { return m_isActive; }
	void SetisActive(const bool& flag) { m_isActive = flag; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetMove() const { return m_move; }
	void SetMove(const DirectX::SimpleMath::Vector3& Move) { m_move = Move; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const  { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//���̃^�C�v�̃Q�b�^�[
	Bullet::BulletParent GetParentType() const {return m_bulletparent; }

	int GetOffensivePower()const { return m_offensivePower; }
	//�傫���̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetScale() const { return m_scale; }
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }

	float GetSpeed()const { return m_speed; }
	//�����蔻��̃Q�b�^�[
	Collider::Sphere* GetCollider() { return m_collider.get(); }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Bullet(const float& speed,const int& offensivePower, const float& scale);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Bullet();

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="bulletType">���̎g�p��</param>
	/// <param name="shooterType">���̎��</param>
	/// <param name="position">�g�p���̈ʒu</param>
	/// <param name="rotate">�g�p���̊p�x</param>
	virtual void Initialize(
		const BulletParent& shooterType, 
		const DirectX::SimpleMath::Vector3& position, 
		const DirectX::SimpleMath::Quaternion& rotate
	);

	/// <summary>
	/// ���������s����
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
	/// ��n��
	/// </summary>
	virtual void Finalize();

private:
	//���ˑΏ�
	BulletParent m_bulletparent;

	//���̃|�W�V����
	DirectX::SimpleMath::Vector3 m_position;

	//���̑傫��
	DirectX::SimpleMath::Vector3 m_scale;

	//���̑���
	float m_speed;

	//���̍U����
	int m_offensivePower;

	//���̕���
	DirectX::SimpleMath::Quaternion m_rotate;

	//�g�p����Ă��邩�̃O���t
	bool m_isActive;

	// ���̃��f���̃|�C���^
	DirectX::Model* m_bulletModel;

	//�����蔻��̃|�C���^
	std::unique_ptr<Collider::Sphere> m_collider;

	DirectX::SimpleMath::Vector3 m_move;
}; 