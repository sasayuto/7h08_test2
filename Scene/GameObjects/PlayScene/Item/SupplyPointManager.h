#pragma once
#include"FuelSupplyPoint.h"
#include"HpSupplyPoint.h"
struct IPlayerComponent;

//�A�C�e���̊Ǘ��҂̃N���X���`����
class SupplyPointManager
{
public:
	int GetItemGetCount()const { return m_itemGetCount; }
	void SetItemGetCount(const int& itemGetCount) { m_itemGetCount = itemGetCount; }
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SupplyPointManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~SupplyPointManager();

	//����������
	void Intialize(std::string failName = "");

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

	int m_itemGetCount;
};