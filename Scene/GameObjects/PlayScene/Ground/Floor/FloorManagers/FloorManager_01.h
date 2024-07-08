#pragma once
#include"../Floor.h"

class Enemy; 
class Airship;

/// <summary>
/// ���̊Ǘ��҂̃N���X���`����
/// </summary>
class FloorManager_01
{
public:
	//���̎��
	const enum ObjectParent
	{
		None = 0,
		HOUSE = 1
	};

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="mapLoader">�}�b�v�̃A�h���X</param>
	FloorManager_01();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~FloorManager_01();

	/// <summary>
	/// ����������
	/// </summary>
	void Intialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

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

private:
	//���̎��
	ObjectParent m_objectParent;

	//���̃|�C���^
	std::vector<std::unique_ptr<Floor>> m_floorsList;
};