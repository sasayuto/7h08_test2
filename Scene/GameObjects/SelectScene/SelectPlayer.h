#pragma once
#include"Scene/GameObjects/PlayScene/ObjectModel/ObjectsManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/StreetLight/StreetLightManager.h"
#include"Scene/GameObjects/PlayScene/ObjectModel/Bench/BenchManager.h"
#include"Scene/GameObjects/PlayScene/Item/RespawnManager.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/Floor.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/FloorManagers/FloorManager_01.h"
#include"Scene/GameObjects/PlayScene/Character/Player/IPlayerComponent.h"
#include "ImaseLib/MoveUserInterface.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"

#include"Scene/GameObjects/PlayScene/Character/Player/StatePlayerFactory.h"
#include"Scene/GameObjects/PlayScene/Character/Player/IState.h"

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

class BloodEffect;
class PlayerEffect;

//�X�e�[�g�N���X
class Players;
class KillMotion;

/// <summary>
/// �v���C���[�̃N���X���`����
/// </summary>
class SelectPlayer
{
public:
	static const float BULLET_COOL_TIME;					//���N�[���^�C��	(s)
	static const float PLAYER_MAX_SPEED;					//�O�i�̍ő�X�s�[�h(m/s)
	static const float PLAYER_ACCELERATION;					//�O�i�̉����x		(m/s)
	static const float PLAYER_BEND_ACCELERATION;			//�p�Ȃ̉����x		(��/s)
	static const float PLAYER_AIR_RESISTANCE;				//��C��R
	static const float PLAYER_BEND_AIR_RESISTANCE;			//�p�Ȃ̋�C��R
	static const float PLAYER_STRAT_FALLING_SPEED;			//�����J�n���x		(m/s)
	static const float PLAYER_FALL_SPEED__ACCELERATION;		//�����̉����x		(m/s)
	static const float PLAYER_FALL_SPEED_MAX;				//�����̍ő呬�x	(m/s)
	static const int PLAYER_MAX_HP;							//�v���C���[��HP	
	static const int PLAYER_MAX_FUEL=1000000;						//�v���C���[�̔R��	
	static const int PLAYER_OFFENSIVE_POWER=100;				//�v���C���[�̍U����
	static const float BULLET_WIDTH;

	//�J�����̕���
	DirectX::SimpleMath::Quaternion GetCameraRotate()const { return m_cameraRotate; };
	void SetCameraRotate(const DirectX::SimpleMath::Quaternion& cameraRotate) { m_cameraRotate = cameraRotate; }


	//�v���C���[�̉��G�t�F�N�g�̃|�C���^�̃Q�b�^�[
	PlayerEffect* GetPlayerEffect() { return m_playerEffect.get(); };

	//�X���A�j���[�V�����̃Z�b�^�[�A�Q�b�^�[
	float GetTiltAnimation() const { return m_TiltAnimation; };
	void SetTiltAnimation(const float& tiltAnimation) { m_TiltAnimation = tiltAnimation;; };

	//�A�j���[�V�����̉�]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetAnimetionRotate()const { return m_AnimetionRotate; };
	void SetAnimetionRotate(const DirectX::SimpleMath::Quaternion& animetionRotate) { m_AnimetionRotate = animetionRotate; };

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
	SelectPlayer();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SelectPlayer();

	/// <summary>
	///  ����������
	/// </summary>
	/// <param name="bulletManager">���̊Ǘ��҂̃A�h���X</param>
	/// <param name="enemyManager">�G�̊Ǘ��҂̃A�h���X</param>
	/// <param name="coinManager">�R�C���̊Ǘ��҂̃A�h���X</param>
	/// <param name="objectsManager">�I�u�W�F�N�g�̊Ǘ��҂̃A�h���X</param>
	/// <param name="respawnManager">���X�|�[���n�_�̊Ǘ��҂̃A�h���X</param>
	/// <param name="supplyPointManager">�A�C�e���̊Ǘ��҂̃A�h���X</param>
	/// <param name="treeManager">�؂̊Ǘ��҂̃A�h���X</param>
	/// <param name="airshipManager">��s�D�̊Ǘ��҂̃A�h���X</param>
	/// <param name="windmillManager">���Ԃ̊Ǘ��҂̃A�h���X</param>
	/// <param name="floor">���̊Ǘ��҂̃A�h���X</param>
	/// <param name="streetLightManager">�X���̊Ǘ��҂̃A�h���X</param>
	/// <param name="BenchManager">�x���`�̊Ǘ��҂̃A�h���X</param>
	/// <param name="sandstormManager">�����̊Ǘ��҂̃A�h���X</param>
	/// <param name="turretManager">�^���b�g�̊Ǘ��҂̃A�h���X</param>
	/// <param name="floorManager_01">���̊Ǘ��҂̃A�h���X</param>
	void Initialize(BulletManager* bulletManager);

	/// <summary>
	/// ���������s����
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	void Update(const float& elapsedTime,const bool& decisionFlag,  const bool& returnDecisionFlag);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize();

	/// <summary>
	/// �p�[�c�𐶐�����
	/// </summary>
	/// <param name="Parts">�p�[�c�̃|�C���^</param>
	void AddParts(std::unique_ptr<IPlayerComponent> Parts) { m_parts.emplace_back(move(Parts)); }
	std::vector<std::unique_ptr<IPlayerComponent>>& GetPlayerParts() { return m_parts; }

	/// <summary>
	/// �e�ɂȂ�I�u�W�F�N�g�̕`��
	/// </summary>
	void ShadowMapRender();

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
	//�p�[�c�̔z��̃|�C���^
	std::vector<std::unique_ptr<IPlayerComponent>> m_parts;

	//�J������]
	DirectX::SimpleMath::Quaternion m_cameraRotate;

	//���̃G�t�F�N�g�̃|�C���^
	std::unique_ptr<PlayerEffect> m_playerEffect;

	//��s�@��Z���A�j���[�V����
	float m_TiltAnimation;

	//�A�j���[�V�����̉�]�N�I�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_AnimetionRotate;

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

	//�Q�[�W�ƃx�[�X�̃|�C���^
	std::unique_ptr<tito::MoveUserInterface> m_HorizontalTriangle[2];
	std::unique_ptr<Collider::Box2D> m_HorizontalTrianglecol[2];

};