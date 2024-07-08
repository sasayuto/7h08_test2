#pragma once
/// <summary>
/// Resources�N���X���`����
/// </summary>
class  Resources
{
public:
	//���̃��f�����擾����
	DirectX::Model* GetBurretModel() { return m_burretModel.get(); }

	//�v���C���[�̃��f�����擾����
	DirectX::Model* GetPlayerModel() { return m_playerModel.get(); }

	//�G�̃��f�����擾����
	DirectX::Model* GetEnemyModel() { return m_enemyModel.get(); }

	//�R���̃��f�����擾����
	DirectX::Model* GetSupplyPointModel() { return m_supplyPointModel.get(); }

	//HP�̃��f�����擾����
	DirectX::Model* GetHPSupplyPointModel() { return m_HPsupplyPointModel.get(); }

	//���X�|�[���n�_�̃��f�����擾����
	DirectX::Model* GetRespawnModel() { return m_respawnModel.get(); }

	//�Ƃ̃��f�����擾����
	DirectX::Model* GetHouseModel() { return m_houseModel.get(); }

	//�S�[���̃��f�����擾����
	DirectX::Model* GetGoolModel() { return m_goolModel.get(); }

	//�v���y���̃��f�����擾����
	DirectX::Model* GetPropellerModel() { return m_propellerModel.get(); }

	//�H�̃��f�����擾����
	DirectX::Model* GetWingModel() { return m_wingModel.get(); }

	//�{�f�B�[�̃��f�����擾����
	DirectX::Model* GetBodyModel() { return m_bodyModel.get(); }

	//���������̃��f�����擾����
	DirectX::Model* GetHorizontalStabilizerModelModel() { return m_horizontalStabilizerModel.get(); }

	//�K���̃��f�����擾����
	DirectX::Model* GetTailModel() { return m_tailModel.get(); }

	//�^�C���̃��f�����擾����
	DirectX::Model* GetTireModel() { return m_tireModel.get(); }

	//�z�C�[���T�|�[�g�̃��f�����擾����
	DirectX::Model* GetWheelSupportModel() { return m_wheelSupportModel.get(); }

	//�R�C���̃��f�����擾����
	DirectX::Model* GetCoinModel() { return m_coinModel.get(); }

	//�؂P�̃��f�����擾����
	DirectX::Model* GetTree01Model() { return m_tree01Model.get(); }

	//�؂P�̃��f�����擾����
	DirectX::Model* GetTree02Model() { return m_tree02Model.get(); }

	//�؂P�̃��f�����擾����
	DirectX::Model* GetCloudyBackGroundModel() { return m_cloudyBackGround.get(); }

	//Airship//
	//��s�D��
	DirectX::Model* GetAirshipBodyModel() { return m_airshipBodyModel.get(); }

	//��s�D��
	DirectX::Model* GetAirshipElevatorLeftModel() { return m_airshipElevatorLeftModel.get(); }

	//��s�D��
	DirectX::Model* GetAirshipElevatorRightModel() { return m_airshipElevatorRightModel.get(); }

	//��s�D��
	DirectX::Model* GetAirshipPropellerLeftModel() { return m_airshipPropellerLeftModel.get(); }

	//��s�D��
	DirectX::Model* GetAirshipPropellerSupportLeftModel() { return m_airshipPropellerSupportLeftModel.get(); }

	//��s�D��
	DirectX::Model* GetAirshipPropellerSupportRightModel() { return m_airshipPropellerSupportRightModel.get(); }

	//��s�D��
	DirectX::Model* GetAirshipRoomModel() { return m_airshipRoomModel.get(); }

	//��s�D��
	DirectX::Model* GetAirshipRoom_02Model() { return m_airshipRoom_02Model.get(); }

	//��s�D��
	DirectX::Model* GetAirshipRudderModel() { return m_airshipRudderModel.get(); }

	//����//
	//���Ԃ�
	DirectX::Model* GetWindmillFoundationModel() { return m_windmillFoundationModel.get(); }

	//���Ԃ�
	DirectX::Model* GetWindmillBladeModel() { return m_windmillBladeModel.get(); }

	//���Ԃ�
	DirectX::Model* GetWindmillRoomModel() { return m_windmillRoomModel.get(); }

	//���Ԃ�
	DirectX::Model* GetWindmillTowerModel() { return m_windmillTowerModel.get(); }
	//���Ԃ�
	DirectX::Model* GetWindmillStairsModel() { return m_windmillStairsModel.get(); }


	//�X��WindmillFoundation
	//	
	
	//�X����
	DirectX::Model* GetStreetLightConnectionModel() { return m_streetLightConnectionModel.get(); }

	//�X����
	DirectX::Model* GetStreetLightModel() { return m_streetLightModel.get(); }

	//�X����
	DirectX::Model* GetStreetLightFoundationModel() { return m_streetLightFoundationModel.get(); }

	//�X����
	DirectX::Model* GetStreetLightLightModel() { return m_streetLightLightModel.get(); }
	//


	//�I���{�b�g�̃��f��
	//�I���{�b�g��
	DirectX::Model* GetCrabRobotCalf_LeftBackModel() { return m_CrabRobotCalf_LeftBackModel.get(); }

	//�I���{�b�g��
	DirectX::Model* GetCrabRobotCalf_LeftFrontModel() { return m_CrabRobotCalf_LeftFrontModel.get(); }

	//�I���{�b�g��
	DirectX::Model* GetCrabRobotCalf_RightBackModel() { return m_CrabRobotCalf_RightBackModel.get(); }

	//�I���{�b�g��
	DirectX::Model* GetCrabRobotCalf_RightFrontModel() { return m_CrabRobotCalf_RightFrontModel.get(); }

	//�I���{�b�g��
	DirectX::Model* GetCrabRobotLeg_LeftBackModel() { return m_CrabRobotLeg_LeftBackModel.get(); }

	//�I���{�b�g��
	DirectX::Model* GetCrabRobotLeg_LeftFrontModel() { return m_CrabRobotLeg_LeftFrontModel.get(); }

	//�I���{�b�g��
	DirectX::Model* GetCrabRobotLeg_RightBackModel() { return m_CrabRobotLeg_RightBackModel.get(); }

	//�I���{�b�g��
	DirectX::Model* GetCrabRobotLeg_RightFrontModel() { return m_CrabRobotLeg_RightFrontModel.get(); }

	//�I���{�b�g��
	DirectX::Model* GetCrabRobotThigh_LeftBackModel() { return m_CrabRobotThigh_LeftBackModel.get(); }

	//�I���{�b�g��
	DirectX::Model* GetCrabRobotThigh_LeftFrontModel() { return m_CrabRobotThigh_LeftFrontModel.get(); }

	//�I���{�b�g��
	DirectX::Model* GetCrabRobotThigh_RightBackModel() { return m_CrabRobotThigh_RightBackModel.get(); }

	//�I���{�b�g��
	DirectX::Model* GetCrabRobotThigh_RightFrontModel() { return m_CrabRobotThigh_RightFrontModel.get(); }

	//�I���{�b�g��
	DirectX::Model* GetCrabRobotHead() { return m_CrabRobotHead.get(); }


	//�x���`��
	//	
	//�x���`��
	DirectX::Model* GetBenchBackWoodModel() { return m_benchBackWoodModel.get(); }

	//�x���`��
	DirectX::Model* GetBenchFrameModel() { return m_benchFrameModel.get(); }

	//�x���`��
	DirectX::Model* GetBenchModel() { return m_benchModel.get(); }

	//�x���`��
	DirectX::Model* GetBenchUnderWoodModel() { return m_benchUnderWoodModel.get(); }


	//�^���b�g�̃��f��
	//�^���b�g��
	DirectX::Model* GetTurretBaseModel() { return m_turretBaseModel.get(); }

	//�^���b�g��
	DirectX::Model* GetTurretCancerModel() { return m_turretCancerModel.get(); }

	//�^���b�g��
	DirectX::Model* GetTurretHeadModel() { return m_turretHeadModel.get(); }

	//�^���b�g��
	DirectX::Model* GetStoneFloorModel() { return m_stoneFloorModel.get(); }

	//�^���b�g��
	DirectX::Model* GetStoneStairsModel() { return m_stoneStairsModel.get(); }

	//�^���b�g��
	DirectX::Model* GetMinStoneStairsModel() { return m_minStoneStairsModel.get(); }

	//�^���b�g��
	DirectX::Model* GetHouse_02Model() { return m_house_02Model.get(); }

	//�^���b�g��
	DirectX::Model* GetHouse_03Model() { return m_house_03Model.get(); }

	//�^���b�g��
	DirectX::Model* GetDrunCanModel() { return m_DrunCanModel.get(); }


	//�^���b�g��
	DirectX::Model* GetBigBrickWallModel() { return m_BigBrickWall.get(); }

	//�^���b�g��
	DirectX::Model* GetPalaceModel() { return m_palaceModel.get(); }


	//�t�F���X�̃��f��
	//�t�F���X��
	DirectX::Model* GetFenceNailPlank_Center_01Model() { return m_FenceNailPlank_Center_01.get(); }

	//�t�F���X��
	DirectX::Model* GetFenceNailPlank_Center_02Model() { return m_FenceNailPlank_Center_02.get(); }

	//�t�F���X��
	DirectX::Model* GetFenceNailPlank_Center_03Model() { return m_FenceNailPlank_Center_03.get(); }

	//�t�F���X��
	DirectX::Model* GetFenceNailPlank_Top_01Model() { return m_FenceNailPlank_Top_01.get(); }

	//�t�F���X��
	DirectX::Model* GetFenceNailPlank_Top_02Model() { return m_FenceNailPlank_Top_02.get(); }

	//�t�F���X��
	DirectX::Model* GetFenceNailPlank_Top_03Model() { return m_FenceNailPlank_Top_03.get(); }

	//�t�F���X��
	DirectX::Model* GetFenceNailPlank_Under_01Model() { return m_FenceNailPlank_Under_01.get(); }

	//�t�F���X��
	DirectX::Model* GetFenceVerticalPlank_01Model() { return m_FenceVerticalPlank_01.get(); }

	//�t�F���X��
	DirectX::Model* GetFenceVerticalPlank_02Model() { return m_FenceVerticalPlank_02.get(); }

	//�t�F���X��
	DirectX::Model* GetFenceVerticalPlank_03Model() { return m_FenceVerticalPlank_03.get(); }

	//�t�F���X��
	DirectX::Model* GetFenceVerticalPlank_04Model() { return m_FenceVerticalPlank_04.get(); }

	DirectX::Model* Gethouse_03(int index)
	{
		if (m_house_03Models[index - 1].get()) return m_house_03Models[index - 1].get();
		return nullptr;
	}

	DirectX::Model* Gethouse_02(int index)
	{
		if (m_house_02Models[index - 1].get()) return m_house_02Models[index - 1].get();
		return nullptr;
	}

	DirectX::Model* Gethouse_01(int index)
	{
		if (m_house_01Models[index - 1].get()) return m_house_01Models[index - 1].get();
		return nullptr;
	}

	//�t�F���X��
	DirectX::Model* GetFenceModel() { return m_Fence.get(); }


	DirectX::Model* GetCube() { return m_Cube.get(); }
	DirectX::Model* GetSphere() { return m_Sphere.get(); }

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Resources();

	/// <summary>
	/// Resouces�N���X�̃C���X�^���X���擾����
	/// </summary>
	/// <returns>Resouces�N���X�̃C���X�^���X</returns>
	static Resources* GetInstance();

	/// <summary>
	/// ���\�[�X�����[�h����
	/// </summary>
	void LoadResource();

private:	
	// Resources�̃C���X�^���X�ւ̃|�C���^
	static std::unique_ptr<Resources> m_resources;

	//�f�o�C�X�̃|�C���^
	ID3D11Device1* m_pDevice;

	//
	std::unique_ptr<DirectX::EffectFactory> m_EffectFactory;

	//�v���C���[�̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_playerModel;

	//���̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_burretModel;

	//�G�̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_enemyModel;

	//�R���̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_supplyPointModel;

	//HP�̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_HPsupplyPointModel;

	//���X�|�[���n�_�̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_respawnModel;

	//�Ƃ̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_houseModel;

	//�S�[���̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_goolModel;

	//�{�f�B�[�̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_bodyModel;

	//���������̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_horizontalStabilizerModel;

	//�K���̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_tailModel;

	//�H�̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_wingModel;

	//�^�C���̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_tireModel;

	//�z�C�[���T�|�[�g�̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_wheelSupportModel;

	//�v���y���̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_propellerModel;

	//�R�C���̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_coinModel;

	//��1�̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_tree01Model;

	//��1�̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_tree02Model; 

	//��1�̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_cloudyBackGround;

	//��1�̃��f���̃|�C���^
	std::unique_ptr<DirectX::Model> m_stoneFloorModel;

		//Airship//
	std::unique_ptr<DirectX::Model> m_airshipBodyModel;

	std::unique_ptr<DirectX::Model> m_airshipRudderModel;

	std::unique_ptr<DirectX::Model> m_airshipPropellerLeftModel;

	std::unique_ptr<DirectX::Model> m_airshipRoom_02Model;

	std::unique_ptr<DirectX::Model> m_airshipRoomModel;

	std::unique_ptr<DirectX::Model> m_airshipPropellerSupportLeftModel;

	std::unique_ptr<DirectX::Model> m_airshipPropellerSupportRightModel;

	std::unique_ptr<DirectX::Model> m_airshipElevatorRightModel;

	std::unique_ptr<DirectX::Model> m_airshipElevatorLeftModel;
	//

	//����WindmillFoundation
	//
	std::unique_ptr<DirectX::Model> m_windmillFoundationModel;

	std::unique_ptr<DirectX::Model> m_windmillBladeModel;

	std::unique_ptr<DirectX::Model> m_windmillRoomModel;

	std::unique_ptr<DirectX::Model> m_windmillTowerModel; 
	std::unique_ptr<DirectX::Model> m_windmillStairsModel;
		//

	//�X��WindmillFoundation
	//	
	std::unique_ptr<DirectX::Model> m_streetLightConnectionModel;

	std::unique_ptr<DirectX::Model> m_streetLightModel;

	std::unique_ptr<DirectX::Model> m_streetLightFoundationModel;

	std::unique_ptr<DirectX::Model> m_streetLightLightModel;

	//�C�XWindmillFoundation
	std::unique_ptr<DirectX::Model> m_benchBackWoodModel;

	std::unique_ptr<DirectX::Model> m_benchUnderWoodModel;

	std::unique_ptr<DirectX::Model> m_benchFrameModel;

	std::unique_ptr<DirectX::Model> m_benchModel;

	//�^���b�g�̃��f��
	//�^���b�g��
	std::unique_ptr<DirectX::Model> m_turretBaseModel;

	//�^���b�g��
	std::unique_ptr<DirectX::Model> m_turretCancerModel;

	//�^���b�g��
	std::unique_ptr<DirectX::Model> m_turretHeadModel;


	//�I���{�b�g�̃��f��
	//�I���{�b�g��
	std::unique_ptr<DirectX::Model> m_CrabRobotCalf_LeftBackModel;

	//�I���{�b�g��
	std::unique_ptr<DirectX::Model> m_CrabRobotHead;

	//�I���{�b�g��
	std::unique_ptr<DirectX::Model> m_CrabRobotCalf_LeftFrontModel;

	//�I���{�b�g��
	std::unique_ptr<DirectX::Model> m_CrabRobotCalf_RightBackModel;

	//�I���{�b�g��
	std::unique_ptr<DirectX::Model> m_CrabRobotCalf_RightFrontModel;

	//�I���{�b�g��
	std::unique_ptr<DirectX::Model> m_CrabRobotLeg_LeftBackModel;

	//�I���{�b�g��
	std::unique_ptr<DirectX::Model> m_CrabRobotLeg_LeftFrontModel;

	//�I���{�b�g��
	std::unique_ptr<DirectX::Model> m_CrabRobotLeg_RightBackModel;

	//�I���{�b�g��
	std::unique_ptr<DirectX::Model> m_CrabRobotLeg_RightFrontModel;

	//�I���{�b�g��
	std::unique_ptr<DirectX::Model> m_CrabRobotThigh_LeftBackModel;

	//�I���{�b�g��
	std::unique_ptr<DirectX::Model> m_CrabRobotThigh_LeftFrontModel;

	//�I���{�b�g��
	std::unique_ptr<DirectX::Model> m_CrabRobotThigh_RightBackModel;

	//�I���{�b�g��
	std::unique_ptr<DirectX::Model> m_CrabRobotThigh_RightFrontModel;

		//�I���{�b�g��
	std::unique_ptr<DirectX::Model> m_BigBrickWall;

	//��
	std::unique_ptr<DirectX::Model> m_stoneStairsModel;

	//��
	std::unique_ptr<DirectX::Model> m_minStoneStairsModel;

	//��
	std::unique_ptr<DirectX::Model> m_DrunCanModel;

	//��
	std::unique_ptr<DirectX::Model> m_house_02Model;

	//��
	std::unique_ptr<DirectX::Model> m_house_03Model;

	//��
	std::unique_ptr<DirectX::Model> m_palaceModel;

	//��
	std::vector< std::unique_ptr<DirectX::Model>> m_house_03Models;
	std::vector< std::unique_ptr<DirectX::Model>> m_house_02Models;
	std::vector< std::unique_ptr<DirectX::Model>> m_house_01Models;

	//�t�F���X�̃��f��
	//�t�F���X��
	std::unique_ptr<DirectX::Model> m_FenceNailPlank_Center_01;

	//�t�F���X��
	std::unique_ptr<DirectX::Model> m_FenceNailPlank_Center_02;

	//�t�F���X��
	std::unique_ptr<DirectX::Model> m_FenceNailPlank_Center_03;

	//�t�F���X��
	std::unique_ptr<DirectX::Model> m_FenceNailPlank_Top_01;

	//�t�F���X��
	std::unique_ptr<DirectX::Model> m_FenceNailPlank_Top_02;

	//�t�F���X��
	std::unique_ptr<DirectX::Model> m_FenceNailPlank_Top_03;

	//�t�F���X��
	std::unique_ptr<DirectX::Model> m_FenceVerticalPlank_01;

	//�t�F���X��
	std::unique_ptr<DirectX::Model> m_FenceVerticalPlank_02;

	//�t�F���X��
	std::unique_ptr<DirectX::Model> m_FenceVerticalPlank_03;

	//�t�F���X��
	std::unique_ptr<DirectX::Model> m_FenceVerticalPlank_04;

	//�t�F���X��
	std::unique_ptr<DirectX::Model> m_FenceNailPlank_Under_01;

	//�t�F���X��
	std::unique_ptr<DirectX::Model> m_Fence;

	///
	std::unique_ptr<DirectX::Model> m_Cube;
	std::unique_ptr<DirectX::Model> m_Sphere;
	///

	std::vector<std::unique_ptr<DirectX::Model>> CreateModelsFromCMO(const std::wstring& baseString, int count, const wchar_t* cmoTexName, const wchar_t* NoemalMapName = nullptr);

	std::unique_ptr<DirectX::Model> CreateModelFromCMO(const wchar_t* cmoName, const wchar_t* cmoTexName = nullptr, const wchar_t* NoemalMapName = nullptr);
	std::unique_ptr<DirectX::Model> CreateModelFromCMO(const wchar_t* cmoName,std::vector<const wchar_t*> cmoTexName, std::vector < const wchar_t*> NoemalMapName = {});
};
