#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"../Objects.h"
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"

#include"StreetLightParts/IStreetLightComponent.h"
class Player;
class StreetLightManager;
/// <summary>
/// �I�u�W�F�N�g�̃N���X���`����
/// </summary>
class StreetLight
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

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	bool GetSurvival() const { return m_survival; }
	void SetSurvival(const bool& survival) { m_survival = survival; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	bool GetAllSurvivalFlag() const { return m_allSurvivalFlag; }


	std::vector<std::unique_ptr<IStreetLightComponent>>& GetParts() { return m_parts; };

	static const float ANIMATION_TIME;//�������[�V�����̎���

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	StreetLight();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~StreetLight();

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize(BulletManager* bulletManager, StreetLightManager* streetLightManager);

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update(const float& elapsedTime);

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
	void AddParts(std::unique_ptr<IStreetLightComponent> Parts) { m_parts.emplace_back(move(Parts)); }

	////�p�[�c�̔z��̃|�C���^
	std::vector<std::unique_ptr<IStreetLightComponent>> m_parts;

private:
	//�v���y���̃��f��
	DirectX::Model* m_pStreetLight;

	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;

	//��]�N�I�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotate;

	//��]�N�I�[�^�j�I��
	DirectX::SimpleMath::Matrix m_world;

	//��܂��ȓ����蔻��̃|�C���^
	std::unique_ptr<Collider::Sphere> m_roughCollider;

	BulletManager* m_pBulletManager;
	//����
	bool m_survival;

	//�o�ߎ���
	float m_timer;
	//�S�Đ����Ă��邩
	bool m_allSurvivalFlag;

	StreetLightManager* m_pStreetLightManager;

	bool m_killCountFlag;
};
