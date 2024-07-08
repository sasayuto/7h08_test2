#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"../Objects.h"
#include"Scene/GameObjects/PlayScene/Bullet/BulletManager.h"

#include"MoveObjectsParts/IMoveObjectsComponent.h"
class Player;
class MoveObjectsManager;
/// <summary>
/// �I�u�W�F�N�g�̃N���X���`����
/// </summary>
class MoveObjects
{
public:
	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	void SetRotateJson(const DirectX::SimpleMath::Vector3& rotate) {
		m_rotate = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(rotate.x),
			DirectX::XMConvertToRadians(rotate.y),
			DirectX::XMConvertToRadians(rotate.z)
		);
	}

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//��܂��ȓ����蔻��̃Q�b�^�[
	Collider::Sphere* GetRoughCollider() { return m_roughCollider.get(); }

	//���f���̃Z�b�^�[�A�Q�b�^�[
	DirectX::Model* GetModel() { return m_pPartModel; }
	void SetModel(DirectX::Model* supplyPointModel) { m_pPartModel = supplyPointModel; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	bool GetSurvival() const { return m_survival; }
	void SetSurvival(const bool& survival) { m_survival = survival; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	bool GetAllSurvivalFlag() const { return m_allSurvivalFlag; }

	std::vector<std::unique_ptr<IMoveObjectsComponent>>& GetParts() { return m_parts; };

	static const float ANIMATION_TIME;//�������[�V�����̎���

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	MoveObjects();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~MoveObjects();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize(BulletManager* bulletManager, MoveObjectsManager* benchManager);

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update(const float& elapsedTime);

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render();
		
	/// <summary>
	/// �V���h�E�}�b�v�p�̉摜�����
	/// </summary>
	virtual void RenderShadowTex();

	virtual void SetpositionRandam(const float& min, const float& max);

public:
	/// <summary>
	/// �p�[�c�𐶐�����
	/// </summary>
	/// <param name="Parts">�p�[�c�̃|�C���^</param>
	void AddParts(std::unique_ptr<IMoveObjectsComponent> Parts) { m_parts.emplace_back(move(Parts)); }

private:
	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;

	//���[���h�s��
	DirectX::SimpleMath::Matrix m_world;

	//��]�N�I�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotate;

	//��܂��ȓ����蔻��̃|�C���^
	std::unique_ptr<Collider::Sphere> m_roughCollider;

	BulletManager* m_pBulletManager;

	MoveObjectsManager* m_pBenchManager;
	//����
	bool m_survival;

	//�o�ߎ���
	float m_timer;

	bool m_killCountFlag;

	//�S�Đ����Ă��邩
	bool m_allSurvivalFlag;

	//�v���y���̃��f��
	DirectX::Model* m_pPartModel;

	////�p�[�c�̔z��̃|�C���^
	std::vector<std::unique_ptr<IMoveObjectsComponent>> m_parts;

};
