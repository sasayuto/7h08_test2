#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"
#include "ImaseLib/DebugCamera.h"
#include "ImaseLib/DepthStencil.h"
#include"Scene/GameObjects/PlayScene/Colliider/Collision.h"
#include <DirectXCollision.h>
#include"Scene/AdjustmentArrow.h"


enum class SelectProject
{
	EDIT,
	FILE,
	COUNT
};
class ModelSampleScene : public Imase::Scene<UserResources>
{
public:
	// �R���X�g���N�^
	ModelSampleScene();

	// ������
	void Initialize() override;

	// �X�V
	void Update(float elapsedTime) override;

	// �X�V
	void EditUpdate(float elapsedTime);

	// �X�V
	void FileSaveUpdate(float elapsedTime);

	// �`��
	void Render() override;

	// �I������
	void Finalize() override;

	// �f�o�C�X�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateDeviceDependentResources() override;

	// �E�C���h�E�T�C�Y�Ɉˑ����郊�\�[�X���쐬����֐�
	void CreateWindowSizeDependentResources() override;

	// �f�o�C�X���X�g�������ɌĂяo�����֐�
	void OnDeviceLost() override;

	int GetSpotLightNum()const { return m_spotLightNum; }
	void SetSpotLightNum(int spotLightNum) { m_spotLightNum = spotLightNum; }

/// <summary>
/// �ۑ�
/// </summary>
private:

	SelectProject m_selectProject;

private:

	// �f�o�b�O�J�����ւ̃|�C���^
	std::unique_ptr<Imase::DebugCamera> m_debugCamera;

	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_proj;
	DirectX::SimpleMath::Quaternion Rotate(float x, float y, float z);
private:

	// �����f���ւ̃|�C���^
	std::unique_ptr<DirectX::Model> m_floorModel;

private:

	// �g�[���X�̃��f��
	std::unique_ptr<DirectX::Model> m_torusModel;

	std::unique_ptr<DirectX::Model> m_torusMel;

private:
private:
	DirectX::SimpleMath::Vector3 m_keepExtents;
	DirectX::SimpleMath::Quaternion m_keepRotate;
	void CollJson();

	std::unique_ptr<Collider::Box2D> m_uiCol[10];
	DirectX::SimpleMath::Color m_uiColor[10];
	float m_eyeToObjectDistance;
	// ���C�g�̉�]

private:
	// �����W���f�o�b�O�\���̃J�[�\���ʒu
	int m_cursor;

	int m_spotLightNum;
	int SPOT_LIGHT_MAX_NUM = 1;

	float m_AdditionPercentageLeft;
	float m_AdditionPercentageRight;
	float m_apTimerLeft;
	float m_apTimerRight;
	// �X�|�b�g���C�g�̃��f���ւ̃|�C���^
	std::unique_ptr<DirectX::Model> m_spotLightModel;

	DirectX::SimpleMath::Vector3 RaycastFromMousePosition(const DirectX::SimpleMath::Vector2& mousePosition, const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix);
	DirectX::SimpleMath::Vector3 m_mouseRayDir;
	DirectX::SimpleMath::Quaternion m_mouseRayDirRotate;

	DirectX::SimpleMath::Vector3 m_RayPostion;
	float m_rayLength;
	DirectX::SimpleMath::Vector3 m_RayExtents;
	std::unique_ptr<AdjustmentArrow> m_AdjustmentArrow;
	int m_MouseSelectNum;
	std::vector<std::unique_ptr<DirectX::BoundingOrientedBox>> m_CubeCol;
	struct CopyColliderDate
	{
		DirectX::SimpleMath::Vector3 Position;
		DirectX::SimpleMath::Vector3 Extents =DirectX::SimpleMath::Vector3::One;
		DirectX::SimpleMath::Quaternion Rotate;
		bool CopyFlag=false;
	};
	//�R�s�[�R���C�_�[�f�[�^
	CopyColliderDate m_copyColliderDate;

	//�t�@�C�����O
	std::wstring m_ModelName;
	std::wstring m_JsonColName;
	//�t�@�C�����O
	std::string m_JsonName;
	int m_ModelNum;

	void SaveGunData();

	// ����]
	float m_yAngle, m_yTmp;

	// �c��]
	float m_xAngle, m_xTmp;

	// �h���b�O���ꂽ���W
	DirectX::SimpleMath::Vector3 m_keeppos;
	int m_x, m_y;

	float m_sx, m_sy;


	void UIUpdate();
};


