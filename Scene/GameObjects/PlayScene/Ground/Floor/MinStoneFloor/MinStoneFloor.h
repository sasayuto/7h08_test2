#pragma once
#include"../Floor.h"
/// <summary>
/// �n�ʂ̃N���X���`����
/// </summary>
class MinStoneFloor :public Floor
{
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	MinStoneFloor();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~MinStoneFloor();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize()override;

	/// <summary>
/// �X�V����
/// </summary>
	void Update()override;

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render()override;


};
