#pragma once
#include"../../../Objects.h"

/// <summary>
/// �Ƃ̃N���X���`����
/// </summary>
class BigBrickWall : public Objects
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	BigBrickWall();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~BigBrickWall()override;

	/// <summary>
/// ����������
/// </summary>
	void Initialize()override;

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update()override;

	/// <summary>
	/// �X�V����
	/// </summary>
	void Render()override;

	/// <summary>
	/// �V���h�E�}�b�v�p�̉摜�����
	/// </summary>
	void RenderShadowTex()override;

};
