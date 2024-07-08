#pragma once
#include"Scene/GameObjects/PlayScene/ObjectModel/Objects.h"

class Enemy; 
class Airship;

/// <summary>
/// �I�u�W�F�N�g�̊Ǘ��҂̃N���X���`����
/// </summary>
class BigBrickWallManager
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="mapLoader">�}�b�v�̃A�h���X</param>
	BigBrickWallManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BigBrickWallManager();

	/// <summary>
	/// ����������
	/// </summary>
	void Intialize();  
		void CollJson(const Json::Value& ary,Objects* obj); 

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



	//�I�u�W�F�N�g�̃|�C���^
	std::vector<std::unique_ptr<Objects>> m_objectsList;
};