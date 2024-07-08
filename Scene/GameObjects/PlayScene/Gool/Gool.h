#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
class Player;

class Gool
{
public:
	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//�傫���̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetScale() { return m_scale; }
	void SetScale(const DirectX::SimpleMath::Vector3& scale) { m_scale = scale; }

	//�V�[���ύX�t���O�̃Q�b�^�[
	bool GetSceneFlag() { return m_sceneFlag; }

private:
	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;

	//�傫��
	DirectX::SimpleMath::Vector3 m_scale;

	//���f���̃|�C���^
	DirectX::Model* m_goolModel;

	//�V�[���ύX�̃t���O
	bool m_sceneFlag;

public:		
	//�v���C���[�Ƃ̓����蔻��
	bool HitCheck_Sphere2Sphere(const DirectX::SimpleMath::Vector3& Center, const float& Radius);

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Gool();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Gool();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ���������s����
	/// </summary>
	/// <param name="player">�v���C���[�̃|�C���^</param>
	void Update(Player* player);

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

};
