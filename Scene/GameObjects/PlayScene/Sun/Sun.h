#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include"Scene/GameObjects/Models/Resources.h"
class Player;

/// <summary>
/// �A�C�e���̊��N���X���`����
/// </summary>
class Sun
{
public:
	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	DirectX::SimpleMath::Vector3 GetRightDirect() const { return m_rightDirect; }
	void SetRightDirect(const DirectX::SimpleMath::Vector3& rightDirect) { m_rightDirect = rightDirect; }

	//�ʒu�̃Z�b�^�[�A�Q�b�^�[
	float GetObjectsRight() const { return m_objectsRight; }
	void SetObjectsRight(const float& objectsRight) { m_objectsRight = objectsRight; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//���f���̃Z�b�^�[�A�Q�b�^�[
	DirectX::Model* GetSupplyPointModel() { return m_pSupplyPointModel; }
	void SetSupplyPointModel(DirectX::Model* supplyPointModel) { m_pSupplyPointModel = supplyPointModel; }

	//�����蔻��̃Q�b�^�[
	Collider::Sphere* GetCollider() { return m_collider.get(); }

	static const DirectX::SimpleMath::Vector3 INITIAL_POSITION;

	//�ʒu
	static const DirectX::SimpleMath::Quaternion INITIAL_ROTATE;

	static const float SUNSET_TIME;
	static const float LIGHT_INTENSITY_UPPER_LIMIT;
	static const float LIGHT_INTENSITY_LOWER_LIMIT;
	static const float SUNSHINE_HOURS;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Sun();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~Sun();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="elapsedTime">1�t���[������</param>
	virtual void Update(const float& elapsedTime);

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render();

	/// <summary>
	/// ��n��
	/// </summary>
	virtual void Finalize();
private:
	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;

	DirectX::SimpleMath::Vector3 m_rightDirect;

	//�ʒu
	DirectX::SimpleMath::Quaternion m_rotate;

	//�ʒu
	float m_objectsRight;

	//���f���̃|�C���^
	DirectX::Model* m_pSupplyPointModel;

	//�����蔻��̃|�C���^
	std::unique_ptr<Collider::Sphere> m_collider;


};
