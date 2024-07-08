#pragma once
#include"Scene/GameObjects/PlayScene/Character/Player/IState.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
#include"Enemy.h"
class EnemyManager;
class Enemy;

/// <summary>
/// �G�̒ʏ���2�̃N���X���`����
/// </summary>
class EnemyMotion_02 :public IState
{
public:
	/// <summary>
	/// �R���e�L�X�g
	/// </summary>
	/// <param name="parent">�G�̃A�h���X</param>
	/// <param name="enemyManager">�G�̃}�l�[�W���[�̃A�h���X</param>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	EnemyMotion_02(
		Enemy* parent,
		EnemyManager* enemyManager,
		Player* player
	);


	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~EnemyMotion_02();

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

	/// <summary>
	/// �v���C���[�̓���
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	void Motion(const float& elapsedTime)override;
private:
	//�v���C���[�̃|�C���^
	Player* m_pPlayer;

	//�G�̃|�C���^
	Enemy* m_pEnemy;

	//�G�̃}�l�[�W���[�̃|�C���^
	EnemyManager* m_pEnemyManager;

	//�o�ߎ���
	float m_nowTimer;
};
