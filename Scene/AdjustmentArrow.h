#pragma once
#include <DirectXCollision.h>

#include "DeviceResources.h"

enum HitOperationModel
{
	X,
	Y,
	Z,
	OLL,
	NONE_AND_COUNT,
};
/// <summary>
/// �I�u�W�F�N�g�̃N���X���`����
/// </summary>
class AdjustmentArrow
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

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	bool GetArrowRightTouchFlag() const { return m_ArrowRightTouchFlag; }
	void SetArrowRightTouchFlag(const bool& editorSelectFlag) { m_ArrowRightTouchFlag = editorSelectFlag; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	bool GetArrowLeftTouchFlag() const { return m_ArrowLeftTouchFlag; }
	void SetArrowLeftTouchFlag(const bool& editorSelectFlag) { m_ArrowLeftTouchFlag = editorSelectFlag; }

	//��]�N�I�[�^�j�I���̃Q�b�^�[�Z�b�^�[
	bool GetArrowUpTouchFlag() const { return m_ArrowUpTouchFlag; }
	void SetArrowUpTouchFlag(const bool& editorSelectFlag) { m_ArrowUpTouchFlag = editorSelectFlag; }


	void SetRotateHitNum(HitOperationModel rotateHitNum) { m_rotateHitNum = rotateHitNum; }
	HitOperationModel GetRotateHitNum() { return m_rotateHitNum; }
	HitOperationModel RotateCol(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 dir);

	void SetPositionHitNum(HitOperationModel rotateHitNum) { m_PositionHitNum = rotateHitNum; }
	HitOperationModel GetPositionHitNum() { return m_PositionHitNum; }
	HitOperationModel PositionCol(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 dir);
private:
	//�ʒu
	DirectX::SimpleMath::Vector3 m_position;
	//��]�N�I�[�^�j�I��
	DirectX::SimpleMath::Quaternion m_rotate;
	
	// ���ʃX�e�[�g
	DirectX::CommonStates* m_states;

	//���f���̃|�C���^
	std::unique_ptr < DirectX::Model> m_AdjustmentArrowModel[NONE_AND_COUNT];

	//���f���̃|�C���^
	std::unique_ptr < DirectX::Model> m_Cube;

	//���f���̃|�C���^
	std::unique_ptr < DirectX::Model> m_rotateModel;

	//���f���̃|�C���^
	std::unique_ptr < DirectX::Model> m_rotateModels[NONE_AND_COUNT];

	// �[�x�X�e���V���X�e�[�g�i�e�j
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState_Shadow;

	//�����蔻��̃|�C���^
	std::unique_ptr<DirectX::BoundingOrientedBox> m_AdjustmentArrowCollider[3];

	//�����蔻��̃|�C���^
	std::unique_ptr<DirectX::BoundingOrientedBox> m_RotateBoxCol[3];
	std::unique_ptr<DirectX::BoundingSphere> m_RotateSphereCol;
	std::unique_ptr<DirectX::BoundingSphere> m_RotateOll;

	bool m_ArrowRightTouchFlag;
	bool m_ArrowLeftTouchFlag;
	bool m_ArrowUpTouchFlag;
	HitOperationModel m_rotateHitNum;
	HitOperationModel m_PositionHitNum;
	DX::DeviceResources* m_deviceResources;

	float m_size;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	AdjustmentArrow(DX::DeviceResources* deviceResources, DirectX::CommonStates* states);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~AdjustmentArrow();

	/// <summary>
	/// ����������
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// �X�V����
	/// </summary>
	virtual void Update(const DirectX::SimpleMath::Vector3& position,const DirectX::SimpleMath::Quaternion& ratate,float size);

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	/// <summary>
	/// �`�悷��
	/// </summary>
	virtual void RotateRender(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	/// <summary>
	/// �G�������_���ɐ���
	/// </summary>
	/// <param name="min">�ŏ�</param>
	/// <param name="max">�ő�</param>
	void SetpositionRandam(const float& min, const float& max);

};
