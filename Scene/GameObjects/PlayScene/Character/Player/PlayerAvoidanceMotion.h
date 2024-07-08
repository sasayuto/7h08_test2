#pragma once
#include"Scene/GameObjects/PlayScene/Character/Player/IState.h"
#include"Player.h"
#include"Scene/GameObjects/PlayScene/Item/SupplyPointManager.h"
#include"Scene/GameObjects/PlayScene/Character/Enemy/EnemyManager.h"
#include"Scene/GameObjects/PlayScene/Item/RespawnManager.h"
#include"Scene/GameObjects/PlayScene/Item/CoinManager.h"
#include"Scene/GameObjects/PlayScene/Effect/PlayerEffect.h"
#include"Scene/GameObjects/PlayScene/Effect/BloodEffect.h"

class Player;
class EnemyManager;

/// <summary>
/// �����Ԃ̃N���X���`����
/// </summary>
class PlayerAvoidanceMotion :public IState
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�̃A�h���X</param>
	/// <param name="respawnManager">���X�|�[���n�_�̊Ǘ��҂̃A�h���X</param>
	/// <param name="supplyPointManager">�A�C�e���̊Ǘ��҂̃A�h���X</param>
	/// <param name="coinManager">�R�C���̊Ǘ��҂̃A�h���X</param>
	PlayerAvoidanceMotion(
		Player* parent,
		RespawnManager* respawnManager,
		SupplyPointManager* supplyPointManager,
		CoinManager* coinManager
	);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~PlayerAvoidanceMotion();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize()override;

	/// <summary>
	/// ���������s����
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	void Update(const float& elapsedTime)override;

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render()override;

		/// <summary>
	/// �v���C���[�̓���
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	void Motion(const float& elapsedTime)override;

	/// <summary>
	/// ��n��
	/// </summary>
	void Finalize()override;

private:
	//�e�̃|�C���^
	Player* m_pPlayer;

	//���X�|�[���n�_�̊Ǘ��҂̃|�C���^
	RespawnManager* m_pRespawnManager;

	//�A�C�e���̊Ǘ��҂̃|�C���^
	SupplyPointManager* m_pSupplyPointManager;

	//�G�̊Ǘ��҂̃|�C���^
	EnemyManager* m_pEnemyManager;

	//�R�C���̊Ǘ��҂̃|�C���^
	CoinManager* m_pCoinManager;
};
