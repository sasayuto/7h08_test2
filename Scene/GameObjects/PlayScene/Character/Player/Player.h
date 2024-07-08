#pragma once
#include"Scene/GameObjects/PlayScene/ObjectModel/ObjectsManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/StreetLight/StreetLightManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Bench/BenchManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/MoveObjects/MoveObjectsManager.h"
#include"Scene/GameObjects/PlayScene/Item/RespawnManager.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/Floor.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/FloorManagers/FloorManager_01.h"
#include"IPlayerComponent.h"

#include"Scene/GameObjects/PlayScene/Character/Player/StatePlayerFactory.h"
#include"Scene/GameObjects/PlayScene/Character/Player/IState.h"
#include"PlayerMotion.h"
#include"PlayerKillMotion.h"

//�����蔻��
class SupplyPointManager;
class EnemyManager;
class CoinManager;
class BulletManager;
class AirshipManager;
class WindmillManager;
class SandstormManager;
class TurretManager;
class BigBrickWallManager;
class HouseMoveObjectsManager;
class BloodEffect;
class PlayerEffect;

//�X�e�[�g�N���X
class Players;
class KillMotion;

/// <summary>
/// �v���C���[�̃N���X���`����
/// </summary>
class Player
{
public:
	static float BULLET_COOL_TIME;					//���N�[���^�C��	(s)
	static float PLAYER_MAX_SPEED;					//�O�i�̍ő�X�s�[�h(m/s)
	static float PLAYER_ACCELERATION;					//�O�i�̉����x		(m/s)
	static float PLAYER_BEND_ACCELERATION;			//�p�Ȃ̉����x		(��/s)
	static float PLAYER_AIR_RESISTANCE;				//��C��R
	static float PLAYER_BEND_AIR_RESISTANCE;			//�p�Ȃ̋�C��R
	static float PLAYER_STRAT_FALLING_SPEED;			//�����J�n���x		(m/s)
	static float PLAYER_FALL_SPEED__ACCELERATION;		//�����̉����x		(m/s)
	static float PLAYER_FALL_SPEED_MAX;				//�����̍ő呬�x	(m/s)
	static int PLAYER_MAX_HP;							//�v���C���[��HP	
	static int PLAYER_MAX_FUEL;						//�v���C���[�̔R��	
	static int PLAYER_OFFENSIVE_POWER;				//�v���C���[�̍U����
	static float BULLET_WIDTH;

	//�J�����̕���
	DirectX::SimpleMath::Quaternion GetCameraRotate()const { return m_cameraRotate; };
	void SetCameraRotate(const DirectX::SimpleMath::Quaternion& cameraRotate) { m_cameraRotate = cameraRotate; }

	//�ʏ�̏��
	IState* GetMotion() { return m_motion.get(); }

	//���S�̏��
	IState* GetKillMotion() { return m_killMotion.get(); }

	//��~�̏��
	IState* GetStopMotion() { return m_stopMotion.get(); }

	//��~�̏��
	IState* GetAvoidanceMotion() { return m_avoidanceMotion.get(); }

	//�����̏��
	IState* GetTurbMode() { return m_turbMode.get(); }

	//���݂̏�ԃZ�b�g
	void SetIState(IState* Istate) {
		m_pCurrentState = Istate;
		m_pCurrentState->Initialize();
	}

	//�v���C���[�̉��G�t�F�N�g�̃|�C���^�̃Q�b�^�[
	PlayerEffect* GetPlayerEffect() { return m_playerEffect.get(); };

	//�v���C���[�̌��̃G�t�F�N�g�̃Q�b�^�[
	BloodEffect* GetBloodEffect() { return m_bloodEffect.get(); };

	//�X���A�j���[�V�����̃Z�b�^�[�A�Q�b�^�[
	float GetTiltAnimation() const { return m_TiltAnimation; };
	void SetTiltAnimation(const float& tiltAnimation) { m_TiltAnimation = tiltAnimation;; };

	//�A�j���[�V�����̉�]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetAnimetionRotate()const { return m_AnimetionRotate; };
	void SetAnimetionRotate(const DirectX::SimpleMath::Quaternion& animetionRotate) { m_AnimetionRotate = animetionRotate; };

	//�����t���O�̃Q�b�^�[�Z�b�^�[
	bool GetSurvival() { return m_survival; }
	void SetSurvival(const bool& survival) { m_survival = survival; }

	//���˃x�N�g���̃Q�b�^�[�A�Z�b�^�[
	void SetReflectionVector(const DirectX::SimpleMath::Vector3& reflectionVector) { m_reflectionVector = reflectionVector; }
	DirectX::SimpleMath::Vector3 GetReflectionVector() { return m_reflectionVector; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
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

	//���̎�ނ̃Q�b�^�[�A�Z�b�^�[
	Bullet::BulletType GetBulletType() const { return m_bulletType; }
	void SetBulletType(const Bullet::BulletType& bulletType) { m_bulletType = bulletType; }

	//�����蔻��̃Q�b�^�[
	Collider::Sphere* GetCollider() { return m_collider.get(); }


public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Player();

	/// <summary>
	///  ����������
	/// </summary>
	/// <param name="bulletManager">���̊Ǘ��҂̃A�h���X</param>
	/// <param name="enemyManager">�G�̊Ǘ��҂̃A�h���X</param>
	/// <param name="coinManager">�R�C���̊Ǘ��҂̃A�h���X</param>
	/// <param name="objectsManager">�I�u�W�F�N�g�̊Ǘ��҂̃A�h���X</param>
	/// <param name="respawnManager">���X�|�[���n�_�̊Ǘ��҂̃A�h���X</param>
	/// <param name="supplyPointManager">�A�C�e���̊Ǘ��҂̃A�h���X</param>
	/// <param name="airshipManager">��s�D�̊Ǘ��҂̃A�h���X</param>
	/// <param name="windmillManager">���Ԃ̊Ǘ��҂̃A�h���X</param>
	/// <param name="floor">���̊Ǘ��҂̃A�h���X</param>
	/// <param name="streetLightManager">�X���̊Ǘ��҂̃A�h���X</param>
	/// <param name="BenchManager">�x���`�̊Ǘ��҂̃A�h���X</param>
	/// <param name="sandstormManager">�����̊Ǘ��҂̃A�h���X</param>
	/// <param name="turretManager">�^���b�g�̊Ǘ��҂̃A�h���X</param>
	/// <param name="floorManager_01">���̊Ǘ��҂̃A�h���X</param>
	void Initialize(
		BulletManager* bulletManager,
		EnemyManager* enemyManager = nullptr,
		CoinManager* coinManager = nullptr,
		ObjectsManager* objectsManager = nullptr,
		RespawnManager* respawnManager = nullptr,
		SupplyPointManager* supplyPointManager = nullptr,
		AirshipManager* airshipManager = nullptr,
		WindmillManager* windmillManager = nullptr,
		Floor* floor = nullptr,
		StreetLightManager* streetLightManager = nullptr,
		MoveObjectsManager* BenchManager = nullptr,
		MoveObjectsManager* fenceManager = nullptr,
		SandstormManager* sandstormManager = nullptr,
		TurretManager* turretManager = nullptr,
		FloorManager_01* floorManager_01 = nullptr,
		BigBrickWallManager* bigBrickWallManager = nullptr,
		HouseMoveObjectsManager* houseMoveObjectsManager = nullptr,
		HouseMoveObjectsManager * HouseMoveObjectsManager2 = nullptr,
		HouseMoveObjectsManager * HouseMoveObjectsManager3 = nullptr
	);

	void PlayerLoudDate();
	/// <summary>
	/// ���������s����
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
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
	/// ���������Z�b�g
	/// </summary>
	void Reset();

	/// <summary>
	/// �_���[�W����
	/// </summary>
	/// <param name="damage">���肪�^����_���[�W</param>
	void Damage(const int& damage);

	/// <summary>
	/// 2������
	/// </summary>
	/// <param name="BulletCoolTime">���̃N�[���^�C��</param>
	void DoubleShot(const float& BulletCoolTime);

	/// <summary>
	/// 1������
	/// </summary>
	/// <param name="BulletCoolTime">���̃N�[���^�C��</param>
	void Shot(const float& maxBulletCoolTime);

	/// <summary>
	/// �p�[�c�𐶐�����
	/// </summary>
	/// <param name="Parts">�p�[�c�̃|�C���^</param>
	void AddParts(std::unique_ptr<IPlayerComponent> Parts) { m_parts.emplace_back(move(Parts)); }
	std::vector<std::unique_ptr<IPlayerComponent>>& GetParts() { return m_parts; }

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
	/// �p�[�c�̑��x����������
	/// </summary>
	void PartsRender();

private:
	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="motion">�ʏ�̏�Ԃ̃|�C���^</param>
	void AddPlayerMotion(std::unique_ptr<IState> motion) { m_motion = std::move(motion); }

	/// <summary>
	/// ���S�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="killmotion">���S�̏�Ԃ̃|�C���^</param>
	void AddKillPlayerMotion(std::unique_ptr<IState> killmotion) { m_killMotion = std::move(killmotion); }

	/// <summary>
	/// ���S�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="killmotion">���S�̏�Ԃ̃|�C���^</param>
	void AddPlayerStopMotion(std::unique_ptr<IState> killmotion) { m_stopMotion = std::move(killmotion); }

	/// <summary>
	/// ���S�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="killmotion">���S�̏�Ԃ̃|�C���^</param>
	void AddPlayerAvoidanceMotion(std::unique_ptr<IState> avoidanceMotion) { m_avoidanceMotion = std::move(avoidanceMotion); }

	/// <summary>
	/// ���S�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="killmotion">���S�̏�Ԃ̃|�C���^</param>
	void AddPlayerTurbMode(std::unique_ptr<IState> turbMode) { m_turbMode = std::move(turbMode); }

private:
	//�ʏ�̏�Ԃ̃|�C���^
	std::unique_ptr<IState> m_motion;

	//���S�̏�Ԃ̃|�C���^
	std::unique_ptr<IState> m_killMotion;

	//���S�̏�Ԃ̃|�C���^
	std::unique_ptr<IState> m_stopMotion;

	//���S�̏�Ԃ̃|�C���^
	std::unique_ptr<IState> m_avoidanceMotion;

	//���S�̏�Ԃ̃|�C���^
	std::unique_ptr<IState> m_turbMode;

	// ���݂̏�Ԃ̃|�C���^
	IState* m_pCurrentState;

	//�I�u�W�F�N�g�̃|�C���^
	ObjectsManager* m_pObjectsManager;
	
	HouseMoveObjectsManager* m_pHouseMoveObjectsManager;
	HouseMoveObjectsManager* m_pHouseMoveObjectsManager1;
	HouseMoveObjectsManager* m_pHouseMoveObjectsManager2;

	//���X�|�[���n�_�̊Ǘ��҂̃|�C���^
	RespawnManager* m_pRespawnManager;

	//��s�D�̊Ǘ��҂̃|�C���^
	AirshipManager* m_pAirshipManager;

	//���Ԃ̊Ǘ��҂̃|�C���^
	WindmillManager* m_pWindmillManager;

	//���̃|�C���^
	Floor* m_pFloor;

	//���̊Ǘ��҂̃|�C���^
	FloorManager_01* m_pFloorManager_01;

	//�X���̊Ǘ��҂̃|�C���^
	StreetLightManager* m_pStreetLightManager;

	//�����̊Ǘ��҂̃|�C���^
	SandstormManager* m_pSandstormManager;

	//�x���`�̊Ǘ��҂̃|�C���^
	MoveObjectsManager* m_pBenchManager;

	//�x���`�̊Ǘ��҂̃|�C���^
	MoveObjectsManager* m_pFenceManager;

	//�^���b�g�̊Ǘ��҂̃|�C���^
	TurretManager* m_pTurretManager;

	//�^���b�g�̊Ǘ��҂̃|�C���^
	BigBrickWallManager* m_pBigBrickWallManager;

	//�p�[�c�̔z��̃|�C���^
	std::vector<std::unique_ptr<IPlayerComponent>> m_parts;

	//�J������]
	DirectX::SimpleMath::Quaternion m_cameraRotate;

	//���̃G�t�F�N�g�̃|�C���^
	std::unique_ptr<PlayerEffect> m_playerEffect;

	//���̃G�t�F�N�g�̃|�C���^
	std::unique_ptr<BloodEffect> m_bloodEffect;

	//��s�@��Z���A�j���[�V����
	float m_TiltAnimation;

	//�A�j���[�V�����̉�]�N�I�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_AnimetionRotate;

	//�����t���O
	bool m_survival;

	//���˃x�N�g��
	DirectX::SimpleMath::Vector3 m_reflectionVector;

	//���̊Ǘ��҂̃|�C���^
	BulletManager* m_pBulletManager;

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

	//�����蔻��̃|�C���^
	std::unique_ptr<Collider::Sphere> m_collider;
};