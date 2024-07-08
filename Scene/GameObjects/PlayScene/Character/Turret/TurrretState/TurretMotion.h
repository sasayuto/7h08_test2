#pragma once
#include"Scene/GameObjects/PlayScene/Character/Player/IState.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Enemy.h"
class EnemyManager;
class Enemy;

/// <summary>
/// �G�̒ʏ��Ԃ̃N���X���`����
/// </summary>
class EnemyMotion :public IState
{
public:		
	/// <summary>
	/// �v���C���[�̓���
	/// </summary>
	void Motion();

public:
	/// <summary>
	/// �R���e�L�X�g
	/// </summary>
	/// <param name="parent">�G�̃A�h���X</param>
	/// <param name="enemyManager">�G�̃}�l�[�W���[�̃A�h���X</param>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	EnemyMotion(Enemy* parent, EnemyManager* enemyManager, Player* player);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyMotion();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">�P�t���[������</param>
	void Update(const float& elapsedTime)override;

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render()override;

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize()override;

private:
	//�v���C���[�̃|�C���^
	Player* m_pPlayer;

	//�G�̃|�C���^
	Enemy* m_pEnemy;

	//�G�̃}�l�[�W���[�̃|�C���^
	EnemyManager* m_pEnemyManager;
};
