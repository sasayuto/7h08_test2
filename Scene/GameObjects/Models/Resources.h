#pragma once
/// <summary>
/// Resourcesクラスを定義する
/// </summary>
class  Resources
{
public:
	//球のモデルを取得する
	DirectX::Model* GetBurretModel() { return m_burretModel.get(); }

	//プレイヤーのモデルを取得する
	DirectX::Model* GetPlayerModel() { return m_playerModel.get(); }

	//敵のモデルを取得する
	DirectX::Model* GetEnemyModel() { return m_enemyModel.get(); }

	//燃料のモデルを取得する
	DirectX::Model* GetSupplyPointModel() { return m_supplyPointModel.get(); }

	//HPのモデルを取得する
	DirectX::Model* GetHPSupplyPointModel() { return m_HPsupplyPointModel.get(); }

	//リスポーン地点のモデルを取得する
	DirectX::Model* GetRespawnModel() { return m_respawnModel.get(); }

	//家のモデルを取得する
	DirectX::Model* GetHouseModel() { return m_houseModel.get(); }

	//ゴールのモデルを取得する
	DirectX::Model* GetGoolModel() { return m_goolModel.get(); }

	//プロペラのモデルを取得する
	DirectX::Model* GetPropellerModel() { return m_propellerModel.get(); }

	//羽のモデルを取得する
	DirectX::Model* GetWingModel() { return m_wingModel.get(); }

	//ボディーのモデルを取得する
	DirectX::Model* GetBodyModel() { return m_bodyModel.get(); }

	//水平尾翼のモデルを取得する
	DirectX::Model* GetHorizontalStabilizerModelModel() { return m_horizontalStabilizerModel.get(); }

	//尻尾のモデルを取得する
	DirectX::Model* GetTailModel() { return m_tailModel.get(); }

	//タイヤのモデルを取得する
	DirectX::Model* GetTireModel() { return m_tireModel.get(); }

	//ホイールサポートのモデルを取得する
	DirectX::Model* GetWheelSupportModel() { return m_wheelSupportModel.get(); }

	//コインのモデルを取得する
	DirectX::Model* GetCoinModel() { return m_coinModel.get(); }

	//木１のモデルを取得する
	DirectX::Model* GetTree01Model() { return m_tree01Model.get(); }

	//木１のモデルを取得する
	DirectX::Model* GetTree02Model() { return m_tree02Model.get(); }

	//木１のモデルを取得する
	DirectX::Model* GetCloudyBackGroundModel() { return m_cloudyBackGround.get(); }

	//Airship//
	//飛行船の
	DirectX::Model* GetAirshipBodyModel() { return m_airshipBodyModel.get(); }

	//飛行船の
	DirectX::Model* GetAirshipElevatorLeftModel() { return m_airshipElevatorLeftModel.get(); }

	//飛行船の
	DirectX::Model* GetAirshipElevatorRightModel() { return m_airshipElevatorRightModel.get(); }

	//飛行船の
	DirectX::Model* GetAirshipPropellerLeftModel() { return m_airshipPropellerLeftModel.get(); }

	//飛行船の
	DirectX::Model* GetAirshipPropellerSupportLeftModel() { return m_airshipPropellerSupportLeftModel.get(); }

	//飛行船の
	DirectX::Model* GetAirshipPropellerSupportRightModel() { return m_airshipPropellerSupportRightModel.get(); }

	//飛行船の
	DirectX::Model* GetAirshipRoomModel() { return m_airshipRoomModel.get(); }

	//飛行船の
	DirectX::Model* GetAirshipRoom_02Model() { return m_airshipRoom_02Model.get(); }

	//飛行船の
	DirectX::Model* GetAirshipRudderModel() { return m_airshipRudderModel.get(); }

	//風車//
	//風車の
	DirectX::Model* GetWindmillFoundationModel() { return m_windmillFoundationModel.get(); }

	//風車の
	DirectX::Model* GetWindmillBladeModel() { return m_windmillBladeModel.get(); }

	//風車の
	DirectX::Model* GetWindmillRoomModel() { return m_windmillRoomModel.get(); }

	//風車の
	DirectX::Model* GetWindmillTowerModel() { return m_windmillTowerModel.get(); }
	//風車の
	DirectX::Model* GetWindmillStairsModel() { return m_windmillStairsModel.get(); }


	//街灯WindmillFoundation
	//	
	
	//街灯の
	DirectX::Model* GetStreetLightConnectionModel() { return m_streetLightConnectionModel.get(); }

	//街灯の
	DirectX::Model* GetStreetLightModel() { return m_streetLightModel.get(); }

	//街灯の
	DirectX::Model* GetStreetLightFoundationModel() { return m_streetLightFoundationModel.get(); }

	//街灯の
	DirectX::Model* GetStreetLightLightModel() { return m_streetLightLightModel.get(); }
	//


	//蟹ロボットのモデル
	//蟹ロボットの
	DirectX::Model* GetCrabRobotCalf_LeftBackModel() { return m_CrabRobotCalf_LeftBackModel.get(); }

	//蟹ロボットの
	DirectX::Model* GetCrabRobotCalf_LeftFrontModel() { return m_CrabRobotCalf_LeftFrontModel.get(); }

	//蟹ロボットの
	DirectX::Model* GetCrabRobotCalf_RightBackModel() { return m_CrabRobotCalf_RightBackModel.get(); }

	//蟹ロボットの
	DirectX::Model* GetCrabRobotCalf_RightFrontModel() { return m_CrabRobotCalf_RightFrontModel.get(); }

	//蟹ロボットの
	DirectX::Model* GetCrabRobotLeg_LeftBackModel() { return m_CrabRobotLeg_LeftBackModel.get(); }

	//蟹ロボットの
	DirectX::Model* GetCrabRobotLeg_LeftFrontModel() { return m_CrabRobotLeg_LeftFrontModel.get(); }

	//蟹ロボットの
	DirectX::Model* GetCrabRobotLeg_RightBackModel() { return m_CrabRobotLeg_RightBackModel.get(); }

	//蟹ロボットの
	DirectX::Model* GetCrabRobotLeg_RightFrontModel() { return m_CrabRobotLeg_RightFrontModel.get(); }

	//蟹ロボットの
	DirectX::Model* GetCrabRobotThigh_LeftBackModel() { return m_CrabRobotThigh_LeftBackModel.get(); }

	//蟹ロボットの
	DirectX::Model* GetCrabRobotThigh_LeftFrontModel() { return m_CrabRobotThigh_LeftFrontModel.get(); }

	//蟹ロボットの
	DirectX::Model* GetCrabRobotThigh_RightBackModel() { return m_CrabRobotThigh_RightBackModel.get(); }

	//蟹ロボットの
	DirectX::Model* GetCrabRobotThigh_RightFrontModel() { return m_CrabRobotThigh_RightFrontModel.get(); }

	//蟹ロボットの
	DirectX::Model* GetCrabRobotHead() { return m_CrabRobotHead.get(); }


	//ベンチの
	//	
	//ベンチの
	DirectX::Model* GetBenchBackWoodModel() { return m_benchBackWoodModel.get(); }

	//ベンチの
	DirectX::Model* GetBenchFrameModel() { return m_benchFrameModel.get(); }

	//ベンチの
	DirectX::Model* GetBenchModel() { return m_benchModel.get(); }

	//ベンチの
	DirectX::Model* GetBenchUnderWoodModel() { return m_benchUnderWoodModel.get(); }


	//タレットのモデル
	//タレットの
	DirectX::Model* GetTurretBaseModel() { return m_turretBaseModel.get(); }

	//タレットの
	DirectX::Model* GetTurretCancerModel() { return m_turretCancerModel.get(); }

	//タレットの
	DirectX::Model* GetTurretHeadModel() { return m_turretHeadModel.get(); }

	//タレットの
	DirectX::Model* GetStoneFloorModel() { return m_stoneFloorModel.get(); }

	//タレットの
	DirectX::Model* GetStoneStairsModel() { return m_stoneStairsModel.get(); }

	//タレットの
	DirectX::Model* GetMinStoneStairsModel() { return m_minStoneStairsModel.get(); }

	//タレットの
	DirectX::Model* GetHouse_02Model() { return m_house_02Model.get(); }

	//タレットの
	DirectX::Model* GetHouse_03Model() { return m_house_03Model.get(); }

	//タレットの
	DirectX::Model* GetDrunCanModel() { return m_DrunCanModel.get(); }


	//タレットの
	DirectX::Model* GetBigBrickWallModel() { return m_BigBrickWall.get(); }

	//タレットの
	DirectX::Model* GetPalaceModel() { return m_palaceModel.get(); }


	//フェンスのモデル
	//フェンスの
	DirectX::Model* GetFenceNailPlank_Center_01Model() { return m_FenceNailPlank_Center_01.get(); }

	//フェンスの
	DirectX::Model* GetFenceNailPlank_Center_02Model() { return m_FenceNailPlank_Center_02.get(); }

	//フェンスの
	DirectX::Model* GetFenceNailPlank_Center_03Model() { return m_FenceNailPlank_Center_03.get(); }

	//フェンスの
	DirectX::Model* GetFenceNailPlank_Top_01Model() { return m_FenceNailPlank_Top_01.get(); }

	//フェンスの
	DirectX::Model* GetFenceNailPlank_Top_02Model() { return m_FenceNailPlank_Top_02.get(); }

	//フェンスの
	DirectX::Model* GetFenceNailPlank_Top_03Model() { return m_FenceNailPlank_Top_03.get(); }

	//フェンスの
	DirectX::Model* GetFenceNailPlank_Under_01Model() { return m_FenceNailPlank_Under_01.get(); }

	//フェンスの
	DirectX::Model* GetFenceVerticalPlank_01Model() { return m_FenceVerticalPlank_01.get(); }

	//フェンスの
	DirectX::Model* GetFenceVerticalPlank_02Model() { return m_FenceVerticalPlank_02.get(); }

	//フェンスの
	DirectX::Model* GetFenceVerticalPlank_03Model() { return m_FenceVerticalPlank_03.get(); }

	//フェンスの
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

	//フェンスの
	DirectX::Model* GetFenceModel() { return m_Fence.get(); }


	DirectX::Model* GetCube() { return m_Cube.get(); }
	DirectX::Model* GetSphere() { return m_Sphere.get(); }

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Resources();

	/// <summary>
	/// Resoucesクラスのインスタンスを取得する
	/// </summary>
	/// <returns>Resoucesクラスのインスタンス</returns>
	static Resources* GetInstance();

	/// <summary>
	/// リソースをロードする
	/// </summary>
	void LoadResource();

private:	
	// Resourcesのインスタンスへのポインタ
	static std::unique_ptr<Resources> m_resources;

	//デバイスのポインタ
	ID3D11Device1* m_pDevice;

	//
	std::unique_ptr<DirectX::EffectFactory> m_EffectFactory;

	//プレイヤーのモデルのポインタ
	std::unique_ptr<DirectX::Model> m_playerModel;

	//球のモデルのポインタ
	std::unique_ptr<DirectX::Model> m_burretModel;

	//敵のモデルのポインタ
	std::unique_ptr<DirectX::Model> m_enemyModel;

	//燃料のモデルのポインタ
	std::unique_ptr<DirectX::Model> m_supplyPointModel;

	//HPのモデルのポインタ
	std::unique_ptr<DirectX::Model> m_HPsupplyPointModel;

	//リスポーン地点のモデルのポインタ
	std::unique_ptr<DirectX::Model> m_respawnModel;

	//家のモデルのポインタ
	std::unique_ptr<DirectX::Model> m_houseModel;

	//ゴールのモデルのポインタ
	std::unique_ptr<DirectX::Model> m_goolModel;

	//ボディーのモデルのポインタ
	std::unique_ptr<DirectX::Model> m_bodyModel;

	//水平尾翼のモデルのポインタ
	std::unique_ptr<DirectX::Model> m_horizontalStabilizerModel;

	//尻尾のモデルのポインタ
	std::unique_ptr<DirectX::Model> m_tailModel;

	//羽のモデルのポインタ
	std::unique_ptr<DirectX::Model> m_wingModel;

	//タイヤのモデルのポインタ
	std::unique_ptr<DirectX::Model> m_tireModel;

	//ホイールサポートのモデルのポインタ
	std::unique_ptr<DirectX::Model> m_wheelSupportModel;

	//プロペラのモデルのポインタ
	std::unique_ptr<DirectX::Model> m_propellerModel;

	//コインのモデルのポインタ
	std::unique_ptr<DirectX::Model> m_coinModel;

	//木1のモデルのポインタ
	std::unique_ptr<DirectX::Model> m_tree01Model;

	//木1のモデルのポインタ
	std::unique_ptr<DirectX::Model> m_tree02Model; 

	//木1のモデルのポインタ
	std::unique_ptr<DirectX::Model> m_cloudyBackGround;

	//木1のモデルのポインタ
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

	//風車WindmillFoundation
	//
	std::unique_ptr<DirectX::Model> m_windmillFoundationModel;

	std::unique_ptr<DirectX::Model> m_windmillBladeModel;

	std::unique_ptr<DirectX::Model> m_windmillRoomModel;

	std::unique_ptr<DirectX::Model> m_windmillTowerModel; 
	std::unique_ptr<DirectX::Model> m_windmillStairsModel;
		//

	//街灯WindmillFoundation
	//	
	std::unique_ptr<DirectX::Model> m_streetLightConnectionModel;

	std::unique_ptr<DirectX::Model> m_streetLightModel;

	std::unique_ptr<DirectX::Model> m_streetLightFoundationModel;

	std::unique_ptr<DirectX::Model> m_streetLightLightModel;

	//イスWindmillFoundation
	std::unique_ptr<DirectX::Model> m_benchBackWoodModel;

	std::unique_ptr<DirectX::Model> m_benchUnderWoodModel;

	std::unique_ptr<DirectX::Model> m_benchFrameModel;

	std::unique_ptr<DirectX::Model> m_benchModel;

	//タレットのモデル
	//タレットの
	std::unique_ptr<DirectX::Model> m_turretBaseModel;

	//タレットの
	std::unique_ptr<DirectX::Model> m_turretCancerModel;

	//タレットの
	std::unique_ptr<DirectX::Model> m_turretHeadModel;


	//蟹ロボットのモデル
	//蟹ロボットの
	std::unique_ptr<DirectX::Model> m_CrabRobotCalf_LeftBackModel;

	//蟹ロボットの
	std::unique_ptr<DirectX::Model> m_CrabRobotHead;

	//蟹ロボットの
	std::unique_ptr<DirectX::Model> m_CrabRobotCalf_LeftFrontModel;

	//蟹ロボットの
	std::unique_ptr<DirectX::Model> m_CrabRobotCalf_RightBackModel;

	//蟹ロボットの
	std::unique_ptr<DirectX::Model> m_CrabRobotCalf_RightFrontModel;

	//蟹ロボットの
	std::unique_ptr<DirectX::Model> m_CrabRobotLeg_LeftBackModel;

	//蟹ロボットの
	std::unique_ptr<DirectX::Model> m_CrabRobotLeg_LeftFrontModel;

	//蟹ロボットの
	std::unique_ptr<DirectX::Model> m_CrabRobotLeg_RightBackModel;

	//蟹ロボットの
	std::unique_ptr<DirectX::Model> m_CrabRobotLeg_RightFrontModel;

	//蟹ロボットの
	std::unique_ptr<DirectX::Model> m_CrabRobotThigh_LeftBackModel;

	//蟹ロボットの
	std::unique_ptr<DirectX::Model> m_CrabRobotThigh_LeftFrontModel;

	//蟹ロボットの
	std::unique_ptr<DirectX::Model> m_CrabRobotThigh_RightBackModel;

	//蟹ロボットの
	std::unique_ptr<DirectX::Model> m_CrabRobotThigh_RightFrontModel;

		//蟹ロボットの
	std::unique_ptr<DirectX::Model> m_BigBrickWall;

	//の
	std::unique_ptr<DirectX::Model> m_stoneStairsModel;

	//の
	std::unique_ptr<DirectX::Model> m_minStoneStairsModel;

	//の
	std::unique_ptr<DirectX::Model> m_DrunCanModel;

	//の
	std::unique_ptr<DirectX::Model> m_house_02Model;

	//の
	std::unique_ptr<DirectX::Model> m_house_03Model;

	//の
	std::unique_ptr<DirectX::Model> m_palaceModel;

	//の
	std::vector< std::unique_ptr<DirectX::Model>> m_house_03Models;
	std::vector< std::unique_ptr<DirectX::Model>> m_house_02Models;
	std::vector< std::unique_ptr<DirectX::Model>> m_house_01Models;

	//フェンスのモデル
	//フェンスの
	std::unique_ptr<DirectX::Model> m_FenceNailPlank_Center_01;

	//フェンスの
	std::unique_ptr<DirectX::Model> m_FenceNailPlank_Center_02;

	//フェンスの
	std::unique_ptr<DirectX::Model> m_FenceNailPlank_Center_03;

	//フェンスの
	std::unique_ptr<DirectX::Model> m_FenceNailPlank_Top_01;

	//フェンスの
	std::unique_ptr<DirectX::Model> m_FenceNailPlank_Top_02;

	//フェンスの
	std::unique_ptr<DirectX::Model> m_FenceNailPlank_Top_03;

	//フェンスの
	std::unique_ptr<DirectX::Model> m_FenceVerticalPlank_01;

	//フェンスの
	std::unique_ptr<DirectX::Model> m_FenceVerticalPlank_02;

	//フェンスの
	std::unique_ptr<DirectX::Model> m_FenceVerticalPlank_03;

	//フェンスの
	std::unique_ptr<DirectX::Model> m_FenceVerticalPlank_04;

	//フェンスの
	std::unique_ptr<DirectX::Model> m_FenceNailPlank_Under_01;

	//フェンスの
	std::unique_ptr<DirectX::Model> m_Fence;

	///
	std::unique_ptr<DirectX::Model> m_Cube;
	std::unique_ptr<DirectX::Model> m_Sphere;
	///

	std::vector<std::unique_ptr<DirectX::Model>> CreateModelsFromCMO(const std::wstring& baseString, int count, const wchar_t* cmoTexName, const wchar_t* NoemalMapName = nullptr);

	std::unique_ptr<DirectX::Model> CreateModelFromCMO(const wchar_t* cmoName, const wchar_t* cmoTexName = nullptr, const wchar_t* NoemalMapName = nullptr);
	std::unique_ptr<DirectX::Model> CreateModelFromCMO(const wchar_t* cmoName,std::vector<const wchar_t*> cmoTexName, std::vector < const wchar_t*> NoemalMapName = {});
};
