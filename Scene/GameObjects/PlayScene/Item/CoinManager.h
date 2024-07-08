#pragma once
#include"FuelSupplyPoint.h"
#include"HpSupplyPoint.h"
#include"Coin.h"

/// <summary>
/// �R�C���̊Ǘ��҂̃N���X���`����
/// </summary>
class CoinManager
{
public:
	//�R�C�����̃Q�b�^�[
	unsigned int GetCount()const{ return m_coinCount; }

	//�V�[���ύX�t���O�̃Q�b�^�[
	bool GetSceneFlag()const { return m_sceneFlag; }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	CoinManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~CoinManager();

	//����������
	void Intialize(std::string failName);

	/// <summary>
	/// �X�V����
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
	/// �v���C���[�Ƌ��̓����蔻��
	/// </summary>
	/// <param name="player">�v���C���[�̃A�h���X</param>
	void CheckHitCharacter(Player* player);
private:
	//�A�C�e���̃|�C���^
	std::vector<std::unique_ptr<Item>> m_supplyPointList;

	//�R�C����
	unsigned int m_coinCount;

	//�V�[���ύX�̃t���O
	bool m_sceneFlag;
};