#include "pch.h"
#include "Resources.h"
#include <iomanip>

using namespace DirectX;

std::unique_ptr<Resources> Resources::m_resources = nullptr;

Resources::Resources():
	m_pDevice(nullptr),
	m_playerModel(nullptr),
	m_enemyModel(nullptr),
	m_burretModel(nullptr),
	m_HPsupplyPointModel(nullptr),
	m_supplyPointModel(nullptr),
	m_houseModel(nullptr),
	m_goolModel(nullptr), 
	m_bodyModel(nullptr),
	m_horizontalStabilizerModel(nullptr),
	m_wheelSupportModel(nullptr),
	m_tireModel(nullptr),
	m_tree01Model(nullptr),
	m_tree02Model(nullptr),
	m_tailModel(nullptr),
	m_wingModel(nullptr), 
	m_coinModel(nullptr),
	m_EffectFactory(nullptr),
	m_Sphere(nullptr),
	m_airshipBodyModel(nullptr),
	m_airshipElevatorLeftModel(nullptr),
	m_airshipElevatorRightModel(nullptr),
	m_airshipPropellerLeftModel(nullptr),
	m_airshipPropellerSupportLeftModel(nullptr),
	m_airshipPropellerSupportRightModel(nullptr),
	m_airshipRoomModel(nullptr),
	m_airshipRoom_02Model(nullptr),
	m_airshipRudderModel(nullptr),
	m_windmillFoundationModel(nullptr),
	m_windmillBladeModel(nullptr),
	m_windmillStairsModel(nullptr),
	m_windmillRoomModel(nullptr),
	m_windmillTowerModel(nullptr),
	m_benchBackWoodModel(nullptr),
	m_benchFrameModel(nullptr),
	m_benchModel(nullptr),
	m_benchUnderWoodModel(nullptr),
	m_streetLightConnectionModel(nullptr),
	m_streetLightFoundationModel(nullptr),
	m_streetLightLightModel(nullptr),
	m_streetLightModel(nullptr),
	m_cloudyBackGround(nullptr),
	m_turretBaseModel(nullptr),
	m_turretCancerModel(nullptr),
	m_turretHeadModel(nullptr),
	m_CrabRobotCalf_LeftBackModel(nullptr),
	m_CrabRobotCalf_LeftFrontModel(nullptr),
	m_CrabRobotCalf_RightBackModel(nullptr),
	m_CrabRobotCalf_RightFrontModel(nullptr),
	m_CrabRobotLeg_LeftBackModel(nullptr),
	m_CrabRobotLeg_LeftFrontModel(nullptr),
	m_CrabRobotLeg_RightBackModel(nullptr),
	m_CrabRobotLeg_RightFrontModel(nullptr),
	m_CrabRobotThigh_LeftBackModel(nullptr),
	m_CrabRobotThigh_LeftFrontModel(nullptr),
	m_CrabRobotThigh_RightBackModel(nullptr),
	m_CrabRobotThigh_RightFrontModel(nullptr),
	m_CrabRobotHead(nullptr),
	m_stoneFloorModel(nullptr),
	m_minStoneStairsModel(nullptr),
	m_stoneStairsModel(nullptr),
	m_DrunCanModel(nullptr),
	m_house_02Model(nullptr),
	m_house_03Model(nullptr),
	m_BigBrickWall(nullptr),
	m_palaceModel(nullptr),
	m_FenceNailPlank_Center_01(nullptr),
	m_FenceNailPlank_Center_02(nullptr),
	m_FenceNailPlank_Center_03(nullptr),
	m_FenceNailPlank_Top_02(nullptr),
	m_FenceNailPlank_Top_03(nullptr),
	m_FenceNailPlank_Top_01(nullptr),
	m_FenceNailPlank_Under_01(nullptr),
	m_FenceVerticalPlank_01(nullptr),
	m_FenceVerticalPlank_02(nullptr),
	m_FenceVerticalPlank_03(nullptr),
	m_FenceVerticalPlank_04(nullptr)
{
}

Resources* Resources::GetInstance()
{
	//すでに生成されてるか
	if (m_resources == nullptr)
	{
		// Resourcesのインスタンスを生成する
		m_resources.reset(new Resources());
	}
	// Resourcesのインスタンスを返す
	return m_resources.get();
}
void Resources::LoadResource()
{
	m_pDevice = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	//エフェクトのインスタンスを生成する
	m_EffectFactory = std::make_unique<EffectFactory>(m_pDevice);

	//画像のパスをセット
	m_EffectFactory->SetDirectory(L"Resources/cmo");

	// プレイヤーのモデルをロードする
	m_playerModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/toyPlane.cmo", *m_EffectFactory.get());

	// 敵のモデルをロードする
	m_enemyModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/EnemyPlane.cmo", *m_EffectFactory.get());

	// 球のモデルをロードする
	m_burretModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Bullet_04.cmo", *m_EffectFactory.get());

	// 燃料のモデルをロードする
	m_supplyPointModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Fuel.cmo", *m_EffectFactory.get());

	// HPのモデルをロードする
	m_HPsupplyPointModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/heart.cmo", *m_EffectFactory.get());

	// リスポーン地点のモデルをロードする
	m_respawnModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/chear.cmo", *m_EffectFactory.get());

	// 家のモデルをロードする
	m_houseModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/House_01.cmo", *m_EffectFactory.get());

	// ゴールのモデルをロードする
	m_goolModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Gool.cmo", *m_EffectFactory.get());

	// プロペラのモデルをロードする
	m_propellerModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Propeller.cmo", *m_EffectFactory.get());

	// 羽のモデルをロードする
	m_wingModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Wing.cmo", *m_EffectFactory.get());

	// ボディーのモデルをロードする
	m_bodyModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Body2.cmo", *m_EffectFactory.get());

	// 水平尾翼のモデルをロードする
	m_horizontalStabilizerModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/HorizontalStabilizer.cmo", *m_EffectFactory.get());

	// 尻尾のモデルをロードする
	m_tailModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Tail.cmo", *m_EffectFactory.get());

	// タイヤのモデルをロードする
	m_tireModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Tire.cmo", *m_EffectFactory.get());

	//ホイールサポートのモデルをロードする
	m_wheelSupportModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/wheelSupport.cmo", *m_EffectFactory.get());


	// コインのモデルをロードする
	m_coinModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Coin.cmo", *m_EffectFactory.get());

	// 木1のモデルをロードする
	m_tree01Model = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Tree_01.cmo", *m_EffectFactory.get());

	// 木1のモデルをロードする
	m_tree02Model = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Tree_01.cmo", *m_EffectFactory.get());

	// 木1のモデルをロードする
	m_cloudyBackGround = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/CloudyBackGround.cmo", *m_EffectFactory.get());

	// 飛行船の　をロードする
	m_airshipBodyModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/AirshipBody.cmo", *m_EffectFactory.get());

	// 飛行船の　をロードする
	m_airshipElevatorLeftModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Elevator_Left.cmo", *m_EffectFactory.get());

	// 飛行船の　をロードする
	m_airshipElevatorRightModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Elevator_Right.cmo", *m_EffectFactory.get());

	// 飛行船の　をロードする
	m_airshipPropellerLeftModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Propeller_Left.cmo", *m_EffectFactory.get());

	// 飛行船の　をロードする
	m_airshipPropellerSupportLeftModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/PropellerSupportLeft.cmo", *m_EffectFactory.get());

	// 飛行船の　をロードする
	m_airshipPropellerSupportRightModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/PropellerSupportRight.cmo", *m_EffectFactory.get());

	// 飛行船の　をロードする
	m_airshipRoomModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Room.cmo", *m_EffectFactory.get());

	// 飛行船の　をロードする
	m_airshipRoom_02Model = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Room_02.cmo", *m_EffectFactory.get());

	// 飛行船の　をロードする
	m_airshipRudderModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Rudder.cmo", *m_EffectFactory.get());

	// 風車の　をロードする
	m_windmillFoundationModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/WindmillFoundation.cmo", *m_EffectFactory.get());

	// 風車の　をロードする
	m_windmillBladeModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/WindmillBlade.cmo", *m_EffectFactory.get());

	// 風車の　をロードする
	m_windmillRoomModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/WindmillRoom.cmo", *m_EffectFactory.get());

	// 風車の　をロードする
	m_windmillTowerModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/WindmillTower.cmo", *m_EffectFactory.get());

	// 風車の　をロードする
	m_windmillStairsModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/WindmillStairs.cmo", *m_EffectFactory.get());

	// 街灯の　をロードする
	m_streetLightConnectionModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/StreetLightConnection.cmo", *m_EffectFactory.get());

	// 街灯の　をロードする
	m_streetLightModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/StreetLight.cmo", *m_EffectFactory.get());

	// 街灯の　をロードする
	m_streetLightFoundationModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/StreetLightFoundation.cmo", *m_EffectFactory.get());

	// 街灯の　をロードする
	m_streetLightLightModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/StreetLightLight.cmo", *m_EffectFactory.get());

	// ベンチの　をロードする
	m_benchBackWoodModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/BenchBackWood.cmo", *m_EffectFactory.get());

	// ベンチの　をロードする
	m_benchFrameModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/BenchFrame.cmo", *m_EffectFactory.get());

	// ベンチの　をロードする
	m_benchModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Bench.cmo", *m_EffectFactory.get());

	// ベンチの　をロードする
	m_benchUnderWoodModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/BenchUnderWood.cmo", *m_EffectFactory.get());

	//タレットの　をロードする
	m_turretBaseModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/TurretBase.cmo", *m_EffectFactory.get());

	//タレットの　をロードする
	m_turretCancerModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/TurretCancer.cmo", *m_EffectFactory.get());

	//タレットの　をロードする
	m_turretHeadModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/TurretHead.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_turretHeadModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/TurretHead.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_CrabRobotCalf_LeftBackModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/CrabRobotCalf_LeftBack.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_CrabRobotCalf_LeftFrontModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/CrabRobotCalf_LeftFroat.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_CrabRobotCalf_RightBackModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/CrabRobotCalf_RightBack.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_CrabRobotCalf_RightFrontModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/CrabRobotCalf_RightFront.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_CrabRobotLeg_LeftBackModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/CrabRobotLeg_LeftBack.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_CrabRobotLeg_LeftFrontModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/CrabRobotLeg_LeftFroat.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_CrabRobotLeg_RightBackModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/CrabRobotLeg_RightBack.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_CrabRobotLeg_RightFrontModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/CrabRobotLeg_RightFront.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_CrabRobotThigh_LeftBackModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/CrabRobotThigh_LeftBack.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_CrabRobotThigh_LeftFrontModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/CrabRobotThigh_LeftFroat.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_CrabRobotThigh_RightBackModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/CrabRobotThigh_RightBack.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_CrabRobotThigh_RightFrontModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/CrabRobotThigh_RightFront.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_CrabRobotHead = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/CrabRobotHead.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_stoneFloorModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/StoneFloor.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_minStoneStairsModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/MinStoneFloor.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_stoneStairsModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/StoneStairs_04.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_BigBrickWall = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/BigBrickWall.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_DrunCanModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/DrunCan.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_house_02Model = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/House_02.cmo", *m_EffectFactory.get());

	//蟹ロボットの　をロードする
	m_house_03Model = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/House_03.cmo", *m_EffectFactory.get());
	// Load the normal map texture
	m_house_03Models = CreateModelsFromCMO(L"Resources/cmo/House_03", 16, L"_Users_it222102_Documents_23__前期_ゲーム制作演習_就職作品飛行機ゲーム_就職作品土台一覧_就職作品土台10h26_Resources_Models_fbx_HouseTex__02.png");
	m_house_02Models = CreateModelsFromCMO(L"Resources/cmo/House_02", 10, L"_Users_it222102_Documents_23__前期_ゲーム制作演習_就職作品飛行機ゲーム_就職作品土台一覧_就職作品土台10h26_Resources_Models_fbx_HouseTex__02.png");
	m_house_01Models = CreateModelsFromCMO(L"Resources/cmo/House_01", 7, L"_Users_it222102_Documents_23__前期_ゲーム制作演習_就職作品飛行機ゲーム_就職作品土台一覧_就職作品土台10h26_Resources_Models_fbx_HouseTex__02.png");

	//m_House_03s.model = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/House_03.cmo", *m_EffectFactory.get());
	//CreateModelsFromCMONum(m_House_03s, L"Resources/cmo/House_03", m_nums.ONE);
	//	CreateModelsFromCMONum(m_House_03s.childrenParts[m_nums.ONE], L"Resources/cmo/House_03", m_nums.FIFTEEN);

	//CreateModelsFromCMONum(m_House_03s, L"Resources/cmo/House_03", m_nums.THREE);
	//	CreateModelsFromCMONum(m_House_03s.childrenParts[m_nums.THREE], L"Resources/cmo/House_03",m_nums.TWO);

	//CreateModelsFromCMONum(m_House_03s, L"Resources/cmo/House_03", m_nums.FOUR);
	//CreateModelsFromCMONum(m_House_03s, L"Resources/cmo/House_03", m_nums.FIVE);
	//CreateModelsFromCMONum(m_House_03s, L"Resources/cmo/House_03",  m_nums.SIX);
	//	CreateModelsFromCMONum(m_House_03s.childrenParts[m_nums.SIX], L"Resources/cmo/House_03", m_nums.SEVEN);

	//CreateModelsFromCMONum(m_House_03s, L"Resources/cmo/House_03", m_nums.EIGHT);
	//	CreateModelsFromCMONum(m_House_03s.childrenParts[m_nums.EIGHT], L"Resources/cmo/House_03", m_nums.NINE);
	//		CreateModelsFromCMONum(m_House_03s.childrenParts[m_nums.EIGHT].childrenParts[m_nums.NINE], L"Resources/cmo/House_03", m_nums.TEN);

	//CreateModelsFromCMONum(m_House_03s, L"Resources/cmo/House_03", m_nums.ELEVEN);
	//	CreateModelsFromCMONum(m_House_03s.childrenParts[m_nums.ELEVEN], L"Resources/cmo/House_03",m_nums.TWELVE);
	//		CreateModelsFromCMONum(m_House_03s.childrenParts[m_nums.ELEVEN].childrenParts[m_nums.TWELVE], L"Resources/cmo/House_03", m_nums.THIRTEEN);

	//CreateModelsFromCMONum(m_House_03s, L"Resources/cmo/House_03",  m_nums.SIXTEEN);
	//CreateModelsFromCMONum(m_House_03s.childrenParts[m_nums.SIXTEEN], L"Resources/cmo/House_03", m_nums.FOURTEEN);

	m_FenceNailPlank_Center_01 = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/FenceNailPlank_Center_01.cmo", *m_EffectFactory.get());

	//フェンスの　をロードする
	m_FenceNailPlank_Center_02 = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/FenceNailPlank_Center_02.cmo", *m_EffectFactory.get());

	//フェンスの　をロードする
	m_FenceNailPlank_Center_03 = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/FenceNailPlank_Center_03.cmo", *m_EffectFactory.get());

	//フェンスの　をロードする
	m_FenceNailPlank_Top_01 = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/FenceNailPlank_Top_01.cmo", *m_EffectFactory.get());

	//フェンスの　をロードする
	m_FenceNailPlank_Top_02 = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/FenceNailPlank_Top_02.cmo", *m_EffectFactory.get());

	//フェンスの　をロードする
	m_FenceNailPlank_Top_03 = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/FenceNailPlank_Top_03.cmo", *m_EffectFactory.get());

	//フェンスの　をロードする
	m_FenceNailPlank_Under_01 = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/FenceNailPlank_Under_01.cmo", *m_EffectFactory.get());

	//フェンスの　をロードする
	m_FenceVerticalPlank_01 = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/FenceVerticalPlank_01.cmo", *m_EffectFactory.get());

	//フェンスの　をロードする
	m_FenceVerticalPlank_02 = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/FenceVerticalPlank_02.cmo", *m_EffectFactory.get());

	//フェンスの　をロードする
	m_FenceVerticalPlank_03 = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/FenceVerticalPlank_03.cmo", *m_EffectFactory.get());

	//フェンスの　をロードする
	m_FenceVerticalPlank_04 = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/FenceVerticalPlank_04.cmo", *m_EffectFactory.get());

	//フェンスの　をロードする
	m_Fence = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Fence.cmo", *m_EffectFactory.get());


	//　をロードする
	m_palaceModel = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/GalleryRound_flatfloor_03.cmo", *m_EffectFactory.get()); 
	///
	m_Cube = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Cube.cmo", *m_EffectFactory.get());
	m_Sphere = DirectX::Model::CreateFromCMO(m_pDevice, L"Resources/cmo/Sphere.cmo", *m_EffectFactory.get());
	///
}

std::vector<std::unique_ptr<DirectX::Model>> Resources::CreateModelsFromCMO(const std::wstring& baseString, int count, const wchar_t* cmoTexName, const wchar_t* NoemalMapName) {
	std::vector<std::unique_ptr<DirectX::Model>> partsmpdel;

	// 文字列の置換
	for (int i = 1; i <= count; ++i) {
		std::wstring replacedString = baseString;
		std::wstring numberString = std::to_wstring(i);

		// 一桁の場合は数字の前に0を追加
		if (numberString.length() == 1) {
			numberString = L"0" + numberString;
		}

		// "_01", "_02", "_03" を追加
		replacedString += L"_";
		replacedString += numberString;
		replacedString += L".cmo";
		// const wchar_t* への変換
		const wchar_t* constString = replacedString.c_str();

		// ここで constString を使って何か処理を行うか、出力するなど
		std::wcout << constString << std::endl;
		std::unique_ptr<DirectX::Model> house_03Model = DirectX::Model::CreateFromCMO(m_pDevice, constString, *m_EffectFactory.get());
		//normalマップある？
		if (NoemalMapName)
		{
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> normalMapSRV;
			DX::ThrowIfFailed(CreateDDSTextureFromFile(m_pDevice, NoemalMapName, nullptr, normalMapSRV.ReleaseAndGetAddressOf()));
			house_03Model->UpdateEffects([normalMapSRV](IEffect* effect)
				{
					// Assuming the effect has a NormalMap variable
					if (auto normalMapEffect = dynamic_cast<BasicEffect*>(effect))
					{
						normalMapEffect->SetTexture(normalMapSRV.Get());
					}
				});
		}

		if (house_03Model) {
			partsmpdel.push_back(std::move(house_03Model));
		}
	}

	return partsmpdel;
}
std::unique_ptr<DirectX::Model> Resources::CreateModelFromCMO(const wchar_t* cmoName, const wchar_t* cmoTexName, const wchar_t* NoemalMapName)
{

	std::unique_ptr<DirectX::Model> model;
	model = DirectX::Model::CreateFromCMO(m_pDevice, cmoName, *m_EffectFactory.get());

	// Create NormalMapEffect
	std::shared_ptr<DirectX::NormalMapEffect> m_normalMapEffect = std::make_unique<DirectX::NormalMapEffect>(m_pDevice);

	// Iterate through each mesh in the model and apply NormalMapEffect
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> normalMapSRV;
		if(NoemalMapName)
		DX::ThrowIfFailed(CreateDDSTextureFromFile(m_pDevice, NoemalMapName, nullptr, normalMapSRV.ReleaseAndGetAddressOf()));
		else
			DX::ThrowIfFailed(CreateDDSTextureFromFile(m_pDevice, L"Resources/Textures/NoNormalMap.dds", nullptr, normalMapSRV.ReleaseAndGetAddressOf()));

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hormalMapSRV;
		DX::ThrowIfFailed(CreateDDSTextureFromFile(m_pDevice, cmoTexName, nullptr, hormalMapSRV.ReleaseAndGetAddressOf()));

		m_normalMapEffect->SetTexture(hormalMapSRV.Get());
		m_normalMapEffect->SetNormalTexture(normalMapSRV.Get());
		// Disable specular reflection
		m_normalMapEffect->SetSpecularColor(DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f));
		m_normalMapEffect->SetSpecularPower(1.0f);
		// Disable Fog
		m_normalMapEffect->SetFogEnabled(false); // This is a hypothetical function, the actual function may vary based on the implementation

		// Apply the NormalMapEffect to the mesh
		model->meshes[0]->meshParts[0]->effect = m_normalMapEffect;
	return model;
}
std::unique_ptr<DirectX::Model> Resources::CreateModelFromCMO(const wchar_t* cmoName, std::vector<const wchar_t*> cmoTexName, std::vector<const wchar_t*> NoemalMapName)
{
	std::unique_ptr<DirectX::Model> model;
	model = DirectX::Model::CreateFromCMO(m_pDevice, cmoName, *m_EffectFactory.get());

	// Create NormalMapEffect
	std::shared_ptr<DirectX::NormalMapEffect> m_normalMapEffect = std::make_unique<DirectX::NormalMapEffect>(m_pDevice);

	// Iterate through each mesh in the model and apply NormalMapEffect
	for (size_t i = 0; i < model->meshes.size(); i++)
	{

			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> normalMapSRV;
			if (NoemalMapName.size())
			{
				if (NoemalMapName[i])
					DX::ThrowIfFailed(CreateDDSTextureFromFile(m_pDevice, NoemalMapName[i], nullptr, normalMapSRV.ReleaseAndGetAddressOf()));
				else
					DX::ThrowIfFailed(CreateDDSTextureFromFile(m_pDevice, L"Resources/Textures/NoNormalMap.dds", nullptr, normalMapSRV.ReleaseAndGetAddressOf()));
			}
			else
				DX::ThrowIfFailed(CreateDDSTextureFromFile(m_pDevice, L"Resources/Textures/NoNormalMap.dds", nullptr, normalMapSRV.ReleaseAndGetAddressOf()));

		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> hormalMapSRV;
		DX::ThrowIfFailed(CreateDDSTextureFromFile(m_pDevice, cmoTexName[i], nullptr, hormalMapSRV.ReleaseAndGetAddressOf()));

		m_normalMapEffect->SetNormalTexture(normalMapSRV.Get());
		m_normalMapEffect->SetTexture(hormalMapSRV.Get());
		// Disable specular reflection
		m_normalMapEffect->SetSpecularColor(DirectX::SimpleMath::Color(0.0f, 0.0f, 0.0f));
		m_normalMapEffect->SetSpecularPower(1.0f);
		// Disable Fog
		m_normalMapEffect->SetFogEnabled(false); // This is a hypothetical function, the actual function may vary based on the implementation

		// Apply the NormalMapEffect to the mesh
		model->meshes[i]->meshParts[0]->effect = m_normalMapEffect;
	}
	return model;
}
//void Resources::CreateModelsFromCMONum(PartList& partsList, const std::wstring& baseString, int& arrayNum)
//{
//	std::wstring replacedString = baseString;
//	std::wstring numberString = std::to_wstring(arrayNum);
//	partsList.ModelPartNum = arrayNum;
//	arrayNum = partsList.childrenParts.size();
//
//	// 一桁の場合は数字の前に0を追加
//	if (numberString.length() == 1) {
//		numberString = L"0" + numberString;
//	}
//
//	replacedString += L"_";
//	replacedString += numberString;
//	replacedString += L".cmo";
//	// const wchar_t* への変換
//	const wchar_t* constString = replacedString.c_str();
//
//	PartList a = {};
//	a.model = DirectX::Model::CreateFromCMO(m_pDevice, constString, *m_EffectFactory.get());
//	partsList.childrenParts.push_back(std::move(a));
//}
