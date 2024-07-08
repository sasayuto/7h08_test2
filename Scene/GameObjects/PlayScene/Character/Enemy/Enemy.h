#pragma once
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"
#include"Scene/GameObjects/PlayScene/Character/Player/IState.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/EnemyKillMotion.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/EnemyMotion.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/ObjectsManager.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/Floor.h"

class EnemyManager;
class EnemyKillMotion;
class EnemyMotion;
class Player;
class AirshipManager;
class WindmillManager;
class SandstormManager;
class FloorManager_01;
class BigBrickWallManager;

/// <summary>
/// �G�̃N���X���`����
/// </summary>
class Enemy 
{
public:
	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const { 
		return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//�����̃Q�b�^�[�A�Z�b�^�[
	DirectX::SimpleMath::Vector3 GetAngle() const { return m_angle; }
	void SetAngle(const DirectX::SimpleMath::Vector3& angle) { m_angle = angle; }

	//HP�̃Q�b�^�[�A�Z�b�^�[
	int GetHP() const { return m_HP; }
	void SetHP(const int& HP) { m_HP = HP; }

	//�R���̃Q�b�^�[�A�Z�b�^�[
	int GetFuel() const { return m_fuel; }
	void SetFuel(const int& fuel) { m_fuel = fuel; }

	//�U���͂̃Q�b�^�[�A�Z�b�^�[
	int GetOffensivePower() const { return m_offensivePower; }
	void SetOffensivePower(const int& offensivePower) { m_offensivePower = offensivePower; }

	//���x(����)�̃Q�b�^�[�A�Z�b�^�[
	DirectX::SimpleMath::Vector3 GetVelcity() const { return m_velcity; }
	void SetVelcity(const DirectX::SimpleMath::Vector3& velcity) { m_velcity = velcity; }

	//���x�̃Q�b�^�[�A�Z�b�^�[
	float GetSpeed() const { return m_speed; }
	void SetSpeed(const float& speed) { m_speed = speed; }

	//���N�[���^�C���̃Q�b�^�[�A�Z�b�^�[
	float GetBulletCoolTime() const { return m_bulletCoolTime; }
	void SetBulletCoolTime(const float& bulletCoolTime) { m_bulletCoolTime = bulletCoolTime; }

	//�d�͂̃Q�b�^�[�A�Z�b�^�[
	float GetGravity() const { return m_gravity; }
	void SetGravity(const float& gravity) { m_gravity = gravity; }

	//���̎g�p�҂̃Q�b�^�[�A�Z�b�^�[
	Bullet::BulletParent GetBulletParent() const { return m_bulletParent; }
	void SetBulletParent(const Bullet::BulletParent& bulletParent) { m_bulletParent = bulletParent; }

	//���̎�ނ̃Q�b�^�[�A�Z�b�^�[
	Bullet::BulletType GetBulletType() const { return m_bulletType; }
	void SetBulletType(const Bullet::BulletType& bulletType) { m_bulletType = bulletType; }

	//�����蔻��̃Q�b�^�[
	Collider::Sphere* GetCollider() { return m_collider.get(); }

	std::vector<std::unique_ptr<IPlayerComponent>>& GetParts() { return m_parts; };

	//�����̃Q�b�^�[�A�Z�b�^�[
	bool GetSurvival() const { return m_survival; }
	void SetSurvival(const bool& survival) { m_survival = survival; }

	//���˃x�N�g���̃Q�b�^�[�A�Z�b�^�[
	void SetReflectionVector(const DirectX::SimpleMath::Vector3& reflectionVector) { m_reflectionVector = reflectionVector; }
	DirectX::SimpleMath::Vector3 GetReflectionVector() { return m_reflectionVector; }


	//�����̏�Ԃ��Q�b�g
	IState* GetEnemyMotion() { 
		return m_enemyMotion.get(); }

	//���S�̏�Ԃ��Q�b�g
	IState* GetEnemyKillMotion() { return m_enemyKillMotion.get(); }

	//���݂̏�ԃZ�b�g
	void SetIState(IState* Istate) 
	{
		m_pCurrentState = Istate;
		m_pCurrentState->Initialize();
	}

	IState* GetIState() { return m_pCurrentState; }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="Hp">NP�̏����l</param>
	/// <param name="Fuel">�R���̏����l</param>
	/// <param name="offensivePower">�U���͂̏����l</param>
	Enemy(const int& Hp, const int& Fuel, const int& offensivePower);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Enemy();

	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="bulletManager">���̃A�h���X</param>
	/// <param name="enemyManager">�G�̃}�l�[�W���[�̃A�h���X</param>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="bulletManager">���̊Ǘ��҃A�h���X</param>
	/// <param name="enemyManager">�G�̊Ǘ��҂̃A�h���X</param>
	/// <param name="objectsManager">�I�u�W�F�N�g�̊Ǘ��҂̃A�h���X</param>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	/// <param name="airshipManager">��s�D�̊Ǘ��҂̃A�h���X</param>
	/// <param name="windmillManager">���Ԃ̊Ǘ��҂̃A�h���X</param>
	/// <param name="floor">���̃A�h���X</param>
	/// <param name="sandstormManager">�����̊Ǘ��҂̃A�h���X</param>
	/// <param name="floorManager_01">���̊Ǘ��҂̃A�h���X</param>
	virtual void Initialize(
		BulletManager* bulletManager,
		EnemyManager* enemyManager,
		ObjectsManager* objectsManager,
		Player* player,
		AirshipManager* airshipManager,
		WindmillManager* windmillManager,
		Floor* floor,
		SandstormManager* sandstormManager,
		FloorManager_01* floorManager_01,
		BigBrickWallManager* bigBrickWallManager
	);

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">�t���[������</param>
	void Update(const float& elapsedTime);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

		/// <summary>
	/// �V���h�E�}�b�v�p�̉摜�����
	/// </summary>
	void RenderShadowTex();

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize();
	
	/// <summary>
	/// �G�������_���ɐ���
	/// </summary>
	/// <param name="min">�ŏ�</param>
	/// <param name="max">�ő�</param>
	void SetpositionRandam(const float& min, const float& max);

	/// <summary>
	/// �_���[�W����
	/// </summary>
	/// <param name="damage">���肪�^����_���[�W</param>
	void Damage(const int& damage);

	/// <summary>
	/// ���������Z�b�g
	/// </summary>
	virtual void Reset();

	/// <summary>
	/// 1������
	/// </summary>
	/// <param name="BulletCoolTime">���̃N�[���^�C��</param>
	void Shot(const float& maxBulletCoolTime);

	/// <summary>
	/// �p�[�c�̏�����
	/// </summary>
	void PartsInitialize();

	/// <summary>
	/// �p�[�c�̍X�V������
	/// </summary>
	void PartsUpdate();

	/// <summary>
	/// �p�[�c�̔�������
	/// </summary>
	void PartsExplosion();

	/// <summary>
	/// �p�[�c�̑��x����������
	/// </summary>
	void PartsMotion();

	/// <summary>
	/// �p�[�c�̓����蔻��
	/// </summary>
	void PartsCollision();

	/// <summary>
	/// �p�[�c�̕`��
	/// </summary>
	void PartsRender();

	/// <summary>
/// �p�[�c�𐶐�����
/// </summary>
/// <param name="Parts">�p�[�c�̃|�C���^</param>
	void AddParts(std::unique_ptr<IPlayerComponent> Parts) { m_parts.emplace_back(move(Parts)); }

public:
	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="motion">�ʏ�̏�Ԃ��|�C���^</param>
	void AddEnemyMotion(std::unique_ptr<IState> motion) { m_enemyMotion = std::move(motion); }

	/// <summary>
	/// ���S�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="killmotion">���S�̏�Ԃ��|�C���^</param>
	void AddEnemyKillMotion(std::unique_ptr<IState> killmotion) { m_enemyKillMotion = std::move(killmotion); }

private:
	//����
	bool m_survival;

	//�����̏�ԃ|�C���^
	std::unique_ptr<IState> m_enemyMotion;

	//���S�̏�Ԃ̃|�C���^
	std::unique_ptr<IState> m_enemyKillMotion;

	// ���݂̏�Ԃ̃A�h���X
	IState* m_pCurrentState;

	//���̃|�C���^
	BulletManager* m_pBulletManager;

	//���̃|�C���^
	ObjectsManager* m_pObjectsManager;

	//��s�D�̊Ǘ��҂̃|�C���^
	AirshipManager* m_pAirshipManager;

	//���Ԃ̊Ǘ��҂̃|�C���^
	WindmillManager* m_pWindmillManager;

	//���̃|�C���^
	Floor* m_pFloor;

	//�����̊Ǘ��҂̃|�C���^
	SandstormManager* m_pSandstormManager;

	//���̎g�p��
	Bullet::BulletParent m_bulletParent;

	//���̊Ǘ��҂̃|�C���^
	FloorManager_01* m_pFloorManager_01;

	//�^���b�g�̊Ǘ��҂̃|�C���^
	BigBrickWallManager* m_pBigBrickWallManager;

	//���̎��
	Bullet::BulletType m_bulletType;

	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;

	//���x(����)
	DirectX::SimpleMath::Vector3 m_velcity;

	//���x
	float m_speed;

	//��]�N�I�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotate;

	//����
	DirectX::SimpleMath::Vector3 m_angle;

	//���̃N�[���^�C��
	float m_bulletCoolTime;

	//HP
	int m_HP;

	//�R��
	int m_fuel;

	//�U����
	int m_offensivePower;

	//�d��
	float m_gravity;

	//���˃x�N�g��
	DirectX::SimpleMath::Vector3 m_reflectionVector;

	//�p�[�c�̔z��̃|�C���^
	std::vector<std::unique_ptr<IPlayerComponent>> m_parts;

	//�����蔻��̃|�C���^
	std::unique_ptr<Collider::Sphere> m_collider;


};
