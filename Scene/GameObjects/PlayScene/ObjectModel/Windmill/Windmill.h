#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"../Objects.h"

#include"WindmillParts/IWindmillComponent.h"
class Player;

/// <summary>
/// �I�u�W�F�N�g�̃N���X���`����
/// </summary>
class Windmill 
{
public:
	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//��܂��ȓ����蔻��̃Q�b�^�[
	Collider::Sphere* GetRoughCollider() { return m_roughCollider.get(); }

	std::vector<std::unique_ptr<IWindmillComponent>>& GetParts() { return m_parts; };

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Windmill();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~Windmill();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update();

	/// <summary>
	/// �`�悷��
	/// </summary>
	void Render();

	/// <summary>
	/// �V���h�E�}�b�v�p�̉摜�����
	/// </summary>
	void RenderShadowTex();

	void SetpositionRandam(const float& min, const float& max);

private:
	/// <summary>
/// �p�[�c�𐶐�����
/// </summary>
/// <param name="Parts">�p�[�c�̃|�C���^</param>
	void AddParts(std::unique_ptr<IWindmillComponent> Parts) { m_parts.emplace_back(move(Parts)); }

	////�p�[�c�̔z��̃|�C���^
	std::vector<std::unique_ptr<IWindmillComponent>> m_parts;

private:
	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;

	//��]�N�I�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotate;

	//��܂��ȓ����蔻��̃|�C���^
	std::unique_ptr<Collider::Sphere> m_roughCollider;
};
