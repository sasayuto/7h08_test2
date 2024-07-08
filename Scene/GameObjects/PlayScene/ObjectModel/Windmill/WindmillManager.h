#pragma once
#include"Windmill.h"

class MapLoader;
class Enemy; 
class Airship;

/// <summary>
/// �I�u�W�F�N�g�̊Ǘ��҂̃N���X���`����
/// </summary>
class WindmillManager
{
public:
	//�I�u�W�F�N�g�̎��
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
	WindmillManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~WindmillManager();

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

private:
	//�I�u�W�F�N�g�̎��
	ObjectParent m_objectParent;

	//�I�u�W�F�N�g�̃|�C���^
	std::vector<std::unique_ptr<Windmill>> m_objectsList;

	//�}�b�v�̃|�C���^
	MapLoader* m_mapLoader;
};