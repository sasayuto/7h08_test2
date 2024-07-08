#pragma once
#include"StreetLight.h"

class Enemy; 
class Airship;
class BulletManager;
class SandstormEffect;

/// <summary>
/// �I�u�W�F�N�g�̊Ǘ��҂̃N���X���`����
/// </summary>
class StreetLightManager
{
public:
	//�I�u�W�F�N�g�̎��
	const enum ObjectParent
	{
		None = 0,
		HOUSE = 1
	};

	//�L���J�E���g
	int GetStreetLightKillCount() { return m_streetLightKillCount; }
	void SetStreetLightKillCount(int streetLightKillCount) { m_streetLightKillCount = streetLightKillCount; }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="mapLoader">�}�b�v�̃A�h���X</param>
	StreetLightManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~StreetLightManager();

	/// <summary>
	/// ����������
	/// </summary>
	void Intialize(BulletManager* bulletManager);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update(const float& elapsedTime);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

	/// <summary>
	/// �V���h�E�}�b�v�p�̉摜�����
	/// </summary>
	virtual void RenderShadowTex(const bool flag);


	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize();

	/// <summary>
	/// �v���C���[�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	void CheckHitCharacter(Player* player);

	/// <summary>
	/// �v���C���[�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	void CheckHitEnemy(Enemy* enemy);	
	
	/// <summary>
	/// ��s�D�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="character">�G�̃A�h���X</param>
	void CheckHitAirship(Airship* airship);

	/// <summary>
/// ��s�D�Ƌ��̓����蔻��
/// </summary>
/// <param name="character">�G�̃A�h���X</param>
	void CheckHitSandstorm(SandstormEffect* sandstormEffect);



private:
	//�I�u�W�F�N�g�̃|�C���^
	std::vector<std::unique_ptr<StreetLight>> m_objectsList;
	BulletManager* m_bulletManager;
	//�L���J�E���g
	int m_streetLightKillCount;

};