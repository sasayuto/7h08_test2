#pragma once
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"
#include"Scene/GameObjects/PlayScene/Ground/Floor/Floor.h"
#include"CrabRobotState/ICrabRobotState.h"
#include"CrabRobotParts/ICrabRobotComponent.h"
class TurretManager;
class AirshipManager;
class SandstormManager;
class CrabRobotManager;
/// <summary>
/// �I���{�b�g�̊��N���X���`����
/// </summary>
class CrabRobot
{
public:
	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//HP�̃Q�b�^�[�A�Z�b�^�[
	int GetHP() const { return m_HP; }
	void SetHP(const int& HP) { m_HP = HP; }

	//�U���͂̃Q�b�^�[�A�Z�b�^�[
	int GetOffensivePower() const { return m_offensivePower; }
	void SetOffensivePower(const int& offensivePower) { m_offensivePower = offensivePower; }

	//�����蔻��̃Q�b�^�[
	Collider::Sphere* GetCollider() { return m_collider.get(); }

	//�q�̃p�[�c�̔z��̃Q�b�^�[
	std::vector<std::unique_ptr<ICrabRobotComponent>>& GetParts() { return m_parts; };

	//�����̃Q�b�^�[�A�Z�b�^�[
	bool GetSurvival() const { return m_survival; }
	void SetSurvival(const bool& survival) { m_survival = survival; }

	//���˃x�N�g���̃Q�b�^�[�A�Z�b�^�[
	void SetReflectionVector(const DirectX::SimpleMath::Vector3& reflectionVector) { m_reflectionVector = reflectionVector; }
	DirectX::SimpleMath::Vector3 GetReflectionVector() { return m_reflectionVector; }

	//�����̏�Ԃ��Q�b�^�[
	ICrabRobotState* GetTurretMotion() {return m_turretMotion.get(); }

	//���S�̏�Ԃ��Q�b�^�[
	ICrabRobotState* GetTurretKillMotion() { return m_turretKillMotion.get(); }

	//���݂̏�ԃZ�b�g
	void SetIState(ICrabRobotState* Istate)
	{
		m_pCurrentState = Istate;
		m_pCurrentState->Initialize();
	}

	//���݂̏�Ԃ̃Q�b�^�[
	ICrabRobotState* GetIState() { return m_pCurrentState; }

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="Hp">HP�̏����l</param>
	/// <param name="offensivePower">�U���͂̏����l</param>
	CrabRobot(const int& Hp, const int& offensivePower);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CrabRobot();

	
	/// <summary>
	/// ����������
	/// </summary>
	/// <param name="bulletManager">���̊Ǘ��҂̃A�h���X</param>
	/// <param name="crabRobotManager">�I���{�b�g�̊Ǘ��҂̃A�h���X</param>
	/// <param name="airshipManager">��s�D�̊Ǘ��҂̃A�h���X</param>
	/// <param name="floor">���̃A�h���X</param>
	/// <param name="sandstormManager">�����̃A�h���X</param>
	virtual void Initialize(
		BulletManager* bulletManager,
		CrabRobotManager* crabRobotManager,
		AirshipManager* airshipManager,
		Floor* floor,
		SandstormManager* sandstormManager
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
	/// �p�[�c�̕`��
	/// </summary>
	void PartsRender();

	/// <summary>
	//�p�[�c�𐶐�����
	//</summary>
	//<param name="Parts">�p�[�c�̃|�C���^</param>
	void AddParts(std::unique_ptr<ICrabRobotComponent> Parts) { m_parts.emplace_back(move(Parts)); }

public:
	/// <summary>
	/// �ʏ�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="motion">�ʏ�̏�Ԃ��|�C���^</param>
	void AddTurrertMotion(std::unique_ptr<ICrabRobotState> motion) { m_turretMotion = std::move(motion); }

	/// <summary>
	/// ���S�̏�Ԃ𐶐�
	/// </summary>
	/// <param name="killmotion">���S�̏�Ԃ��|�C���^</param>
	void AddTurretKillMotion(std::unique_ptr<ICrabRobotState> killmotion) { m_turretKillMotion = std::move(killmotion); }

private:
	//����
	bool m_survival;

	//�����̏�ԃ|�C���^
	std::unique_ptr<ICrabRobotState> m_turretMotion;

	//���S�̏�Ԃ̃|�C���^
	std::unique_ptr<ICrabRobotState> m_turretKillMotion;

	// ���݂̏�Ԃ̃A�h���X
	ICrabRobotState* m_pCurrentState;

	//���̃|�C���^
	BulletManager* m_pBulletManager;

	//��s�D�̃|�C���^
	AirshipManager* m_pAirshipManager;

	//���̃|�C���^
	Floor* m_pFloor;

	//�����̊Ǘ��҂̃|�C���^
	SandstormManager* m_pSandstormManager;

	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;

	//��]
	DirectX::SimpleMath::Quaternion m_rotate; 

	//HP
	int m_HP;

	//�U����
	int m_offensivePower;

	//���˃x�N�g��
	DirectX::SimpleMath::Vector3 m_reflectionVector;

	//�p�[�c�̔z��̃|�C���^
	std::vector<std::unique_ptr<ICrabRobotComponent>> m_parts;

	//�����蔻��̃|�C���^
	std::unique_ptr<Collider::Sphere> m_collider;

};
