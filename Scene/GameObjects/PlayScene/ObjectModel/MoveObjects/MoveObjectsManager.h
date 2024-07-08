#pragma once
#include"MoveObjects.h"

class Enemy;
class Player;
class Airship;
class BulletManager;
class SandstormEffect;
/// <summary>
/// �I�u�W�F�N�g�̊Ǘ��҂̃N���X���`����
/// </summary>
class MoveObjectsManager
{
public:
	//�L���J�E���g
	int GetBenchKillCount() { return m_benchKillCount; }
	void SetBenchKillCount(int benchKillCount) { m_benchKillCount = benchKillCount; }

	//�q�̃p�[�c�𐶐�
	void AddMoveObjects(std::unique_ptr<MoveObjects> moveObjects)  { m_MoveObjectsManager.push_back(std::move(moveObjects)); }

	//�I�u�W�F�N�g�̃|�C���^
	std::vector<std::unique_ptr<MoveObjects>>& GetMoveObjectsManager() { return m_MoveObjectsManager; };

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="mapLoader">�}�b�v�̃A�h���X</param>
	MoveObjectsManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~MoveObjectsManager();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Intialize(BulletManager* bulletManager);

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update(const float& elapsedTime);

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render();

	/// <summary>
	/// �V���h�E�}�b�v�p�̉摜�����
	/// </summary>
	virtual void RenderShadowTex(const bool flag);


	/// <summary>
	/// ��n��
	/// </summary>
	virtual void Finalize();

	/// <summary>
	/// �v���C���[�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	virtual void CheckHitCharacter(Player* player);

	/// <summary>
	/// �v���C���[�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	virtual void CheckHitEnemy(Enemy* enemy);
	
	/// <summary>
	/// ��s�D�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="character">�G�̃A�h���X</param>
	virtual void CheckHitAirship(Airship* airship);

	/// <summary>
	/// ��s�D�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="character">�G�̃A�h���X</param>
	virtual void CheckHitSandstorm(SandstormEffect* sandstormEffect);

private:
	//�I�u�W�F�N�g�̃|�C���^
	std::vector<std::unique_ptr<MoveObjects>> m_breakObjectsManager;

	//�I�u�W�F�N�g�̃|�C���^
	std::vector<std::unique_ptr<MoveObjects>> m_MoveObjectsManager;

	BulletManager* m_pBulletManager;

	//�L���J�E���g
	int m_benchKillCount;
};