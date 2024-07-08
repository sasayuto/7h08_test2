#pragma once

#include"IAirshipState.h"
#include"Scene/GameObjects/PlayScene/Character/Airship/Airship.h"
#include"Scene/GameObjects/PlayScene/Character/Player/Player.h"
/// <summary>
/// �G�̒ʏ��Ԃ̃N���X���`����
/// </summary>
class AirshipMotion_01 :public IStateAirship
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
	AirshipMotion_01(Airship* parent, Player* player);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~AirshipMotion_01();

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
	Airship* m_pAirship;
};
