#include "pch.h"
#include"HouseMoveObjects.h"
#include"IHouseMoveObjectsComponent.h"
#include"HouseMoveObjectsComponent.h"
#include <math.h>
#include<random>
using namespace DirectX;
#include"HouseMoveObjectsManager.h"

#include"../Bench/BenchParts/BenchPartFactory.h"
const float HouseMoveObjects::ANIMATION_TIME(10.0f);//爆発モーションの時間

const float FALL_SPEED_ACCELERATION(0.18f / 60);	//落下の加速度			(m/s)
const float EXPLOSIVE_ROTATE(50.0f / 60);	//モデルの回転の速さ	(°/s）
const float EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//爆発の横のパワー		(m/s)
const float EXPLOSIVE_POWER(2.0f / 60);		//爆発の横のパワー		(m/s)
HouseMove_03::HouseMove_03() :
	HouseMoveObjects()
{

}
void HouseMove_03::Initialize(BulletManager* bulletManager, HouseMoveObjectsManager* benchManager,
	std::vector<DirectX::SimpleMath::Vector3> ColiderPosition[],
	std::vector<DirectX::SimpleMath::Vector3> ColliderExtents[],
	std::vector<DirectX::SimpleMath::Quaternion> ColliderRotate[])
{
	auto rsources = Resources::GetInstance();
	Num nums = {};


	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_03(nums.ONE), nums.ONE, ColiderPosition[nums.ONE - 1], ColliderExtents[nums.ONE - 1], ColliderRotate[nums.ONE - 1]);


	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_03(nums.THREE), nums.THREE, ColiderPosition[nums.THREE - 1], ColliderExtents[nums.THREE - 1], ColliderRotate[nums.THREE - 1]);

	CreateModelsFromCMONum(m_PartList.childrenParts[nums.THREE], rsources->Gethouse_03(nums.TWO), nums.TWO, ColiderPosition[nums.TWO - 1], ColliderExtents[nums.TWO - 1], ColliderRotate[nums.TWO - 1]);

	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_03(nums.FOUR), nums.FOUR, ColiderPosition[nums.FOUR - 1], ColliderExtents[nums.FOUR - 1], ColliderRotate[nums.FOUR - 1]);
	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_03(nums.FIVE), nums.FIVE, ColiderPosition[nums.FIVE - 1], ColliderExtents[nums.FIVE - 1], ColliderRotate[nums.FIVE - 1]);
	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_03(nums.SIX), nums.SIX, ColiderPosition[nums.SIX - 1], ColliderExtents[nums.SIX - 1], ColliderRotate[nums.SIX - 1]);
	CreateModelsFromCMONum(m_PartList.childrenParts[nums.SIX], rsources->Gethouse_03(nums.SEVEN), nums.SEVEN, ColiderPosition[nums.SEVEN - 1], ColliderExtents[nums.SEVEN - 1], ColliderRotate[nums.SEVEN - 1]);

	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_03(nums.EIGHT), nums.EIGHT, ColiderPosition[nums.EIGHT - 1], ColliderExtents[nums.EIGHT - 1], ColliderRotate[nums.EIGHT - 1]);
	CreateModelsFromCMONum(m_PartList.childrenParts[nums.EIGHT], rsources->Gethouse_03(nums.NINE), nums.NINE, ColiderPosition[nums.NINE - 1], ColliderExtents[nums.NINE - 1], ColliderRotate[nums.NINE - 1]);
	CreateModelsFromCMONum(m_PartList.childrenParts[nums.EIGHT].childrenParts[nums.NINE], rsources->Gethouse_03(nums.TEN), nums.TEN, ColiderPosition[nums.TEN - 1], ColliderExtents[nums.TEN - 1], ColliderRotate[nums.TEN - 1]);

	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_03(nums.ELEVEN), nums.ELEVEN, ColiderPosition[nums.ELEVEN - 1], ColliderExtents[nums.ELEVEN - 1], ColliderRotate[nums.ELEVEN - 1]);
	CreateModelsFromCMONum(m_PartList.childrenParts[nums.ELEVEN], rsources->Gethouse_03(nums.TWELVE), nums.TWELVE, ColiderPosition[nums.TWELVE - 1], ColliderExtents[nums.TWELVE - 1], ColliderRotate[nums.TWELVE - 1]);
	CreateModelsFromCMONum(m_PartList.childrenParts[nums.ELEVEN].childrenParts[nums.TWELVE], rsources->Gethouse_03(nums.THIRTEEN), nums.THIRTEEN, ColiderPosition[nums.THIRTEEN - 1], ColliderExtents[nums.THIRTEEN - 1], ColliderRotate[nums.THIRTEEN - 1]);

	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_03(nums.SIXTEEN), nums.SIXTEEN, ColiderPosition[nums.SIXTEEN - 1], ColliderExtents[nums.SIXTEEN - 1], ColliderRotate[nums.SIXTEEN - 1]);
	CreateModelsFromCMONum(m_PartList.childrenParts[nums.SIXTEEN], rsources->Gethouse_03(nums.FOURTEEN), nums.FOURTEEN, ColiderPosition[nums.FOURTEEN - 1], ColliderExtents[nums.FOURTEEN - 1], ColliderRotate[nums.FOURTEEN - 1]);

	for (auto& partdate : m_PartList.childrenParts)
	{
		std::unique_ptr<IHouseMoveObjectsComponent> part = std::make_unique<HouseMoveObjectsComponent>(
			nullptr,
			GetPosition(),
			GetRotate(),
			FALL_SPEED_ACCELERATION,
			EXPLOSIVE_ROTATE,
			EXPLOSIVE_RANDOM_POWER,
			EXPLOSIVE_POWER,
			partdate
		);
		AddParts(std::move(part));
	}
	SetModel(rsources->GetHouse_03Model());
	GetRoughCollider()->SetPosition(GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.f, 5.f, -1.f), GetRotate()));
	GetRoughCollider()->SetRadius(GetModel()->meshes[0]->boundingSphere.Radius);

	HouseMoveObjects::Initialize(bulletManager, benchManager, ColiderPosition, ColliderExtents, ColliderRotate);

}

void HouseMove_03::Render()
{
	if (GetAllSurvivalFlag())
	{
		//視界に入っているか
		if (Draw::GetInstance()->VisibilityRange(GetPosition(), GetModel()->meshes[0]->boundingSphere.Radius))
			return;

		// 飛行機の描画
		Draw::GetInstance()->ShadowMapRender(GetModel(), GetWorld());
	}
	else
		for (auto& parts : GetParts())
			parts->Render();

	//Draw::GetInstance()->TestSphereModel(GetRoughCollider()->GetRadius(), GetRoughCollider()->GetPosition());
}
void HouseMove_02::Render()
{
	if (GetAllSurvivalFlag())
	{
		//視界に入っているか
		if (Draw::GetInstance()->VisibilityRange(GetPosition(), GetModel()->meshes[0]->boundingSphere.Radius))
			return;

		// 飛行機の描画
		Draw::GetInstance()->ShadowMapRender(GetModel(), GetWorld());
	}
	else
		for (auto& parts : GetParts())
			parts->Render();

	//Draw::GetInstance()->TestSphereModel(GetRoughCollider()->GetRadius(), GetRoughCollider()->GetPosition());
}
void HouseMove_01::Render()
{
	if (GetAllSurvivalFlag())
	{
		//視界に入っているか
		if (Draw::GetInstance()->VisibilityRange(GetPosition(), GetModel()->meshes[0]->boundingSphere.Radius))
			return;

		// 飛行機の描画
		Draw::GetInstance()->ShadowMapRender(GetModel(), GetWorld(), GetNormalMap());
	}
	else
		for (auto& parts : GetParts())
			parts->Render();

	//Draw::GetInstance()->TestSphereModel(GetRoughCollider()->GetRadius(), GetRoughCollider()->GetPosition());
}

HouseMove_02::HouseMove_02() :
	HouseMoveObjects()
{

}
void HouseMove_02::Initialize(BulletManager* bulletManager, HouseMoveObjectsManager* benchManager,
	std::vector<DirectX::SimpleMath::Vector3> ColiderPosition[],
	std::vector<DirectX::SimpleMath::Vector3> ColliderExtents[],
	std::vector<DirectX::SimpleMath::Quaternion> ColliderRotate[])
{
	auto rsources = Resources::GetInstance();
	Num nums = {};


	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_02(nums.ONE), nums.ONE, ColiderPosition[nums.ONE - 1], ColliderExtents[nums.ONE - 1], ColliderRotate[nums.ONE - 1]);
	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_02(nums.TWO), nums.TWO, ColiderPosition[nums.TWO - 1], ColliderExtents[nums.TWO - 1], ColliderRotate[nums.TWO - 1]);
	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_02(nums.THREE), nums.THREE, ColiderPosition[nums.THREE - 1], ColliderExtents[nums.THREE - 1], ColliderRotate[nums.THREE - 1]);
	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_02(nums.FOUR), nums.FOUR, ColiderPosition[nums.FOUR - 1], ColliderExtents[nums.FOUR - 1], ColliderRotate[nums.FOUR - 1]);
	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_02(nums.FIVE), nums.FIVE, ColiderPosition[nums.FIVE - 1], ColliderExtents[nums.FIVE - 1], ColliderRotate[nums.FIVE - 1]);
	{
		CreateModelsFromCMONum(m_PartList.childrenParts[nums.FIVE], rsources->Gethouse_02(nums.SIX), nums.SIX, ColiderPosition[nums.SIX - 1], ColliderExtents[nums.SIX - 1], ColliderRotate[nums.SIX - 1]);
		CreateModelsFromCMONum(m_PartList.childrenParts[nums.FIVE], rsources->Gethouse_02(nums.SEVEN), nums.SEVEN, ColiderPosition[nums.SEVEN - 1], ColliderExtents[nums.SEVEN - 1], ColliderRotate[nums.SEVEN - 1]);
	}
	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_02(nums.EIGHT), nums.EIGHT, ColiderPosition[nums.EIGHT - 1], ColliderExtents[nums.EIGHT - 1], ColliderRotate[nums.EIGHT - 1]);
	{
		CreateModelsFromCMONum(m_PartList.childrenParts[nums.EIGHT], rsources->Gethouse_02(nums.NINE), nums.NINE, ColiderPosition[nums.NINE - 1], ColliderExtents[nums.NINE - 1], ColliderRotate[nums.NINE - 1]);
	}
	CreateModelsFromCMONum(m_PartList.childrenParts[nums.NINE], rsources->Gethouse_02(nums.TEN), nums.TEN, ColiderPosition[nums.TEN - 1], ColliderExtents[nums.TEN - 1], ColliderRotate[nums.TEN - 1]);


	for (auto& partdate : m_PartList.childrenParts)
	{
		std::unique_ptr<IHouseMoveObjectsComponent> part = std::make_unique<HouseMoveObjectsComponent>(
			nullptr,
			GetPosition(),
			GetRotate(),
			FALL_SPEED_ACCELERATION,
			EXPLOSIVE_ROTATE,
			EXPLOSIVE_RANDOM_POWER,
			EXPLOSIVE_POWER,
			partdate
		);
		AddParts(std::move(part));
	}
	SetModel(rsources->GetHouse_02Model());
	GetRoughCollider()->SetPosition(GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.f, 4.5f, 0.f), GetRotate()));
	GetRoughCollider()->SetRadius(GetModel()->meshes[0]->boundingSphere.Radius);


	HouseMoveObjects::Initialize(bulletManager, benchManager, ColiderPosition, ColliderExtents, ColliderRotate);

}
HouseMove_01::HouseMove_01() :
	HouseMoveObjects()
{
	SetNormalMap(Textures::GetInstance()->GetHouse_01NormalMap());
}
void HouseMove_01::Initialize(BulletManager* bulletManager, HouseMoveObjectsManager* benchManager,
	std::vector<DirectX::SimpleMath::Vector3> ColiderPosition[],
	std::vector<DirectX::SimpleMath::Vector3> ColliderExtents[],
	std::vector<DirectX::SimpleMath::Quaternion> ColliderRotate[])
{
	auto rsources = Resources::GetInstance();
	Num nums = {};


	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_01(nums.ONE), nums.ONE, ColiderPosition[nums.ONE - 1], ColliderExtents[nums.ONE - 1], ColliderRotate[nums.ONE - 1],GetNormalMap());
	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_01(nums.TWO), nums.TWO, ColiderPosition[nums.TWO - 1], ColliderExtents[nums.TWO - 1], ColliderRotate[nums.TWO - 1],GetNormalMap());
	{
		CreateModelsFromCMONum(m_PartList.childrenParts[nums.TWO], rsources->Gethouse_01(nums.SEVEN), nums.SEVEN, ColiderPosition[nums.SEVEN - 1], ColliderExtents[nums.SEVEN - 1], ColliderRotate[nums.SEVEN - 1], GetNormalMap());
	}
	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_01(nums.THREE), nums.THREE, ColiderPosition[nums.THREE - 1], ColliderExtents[nums.THREE - 1], ColliderRotate[nums.THREE - 1], GetNormalMap());
	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_01(nums.FOUR), nums.FOUR, ColiderPosition[nums.FOUR - 1], ColliderExtents[nums.FOUR - 1], ColliderRotate[nums.FOUR - 1],GetNormalMap());
	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_01(nums.FIVE), nums.FIVE, ColiderPosition[nums.FIVE - 1], ColliderExtents[nums.FIVE - 1], ColliderRotate[nums.FIVE - 1], GetNormalMap());
	CreateModelsFromCMONum(m_PartList, rsources->Gethouse_01(nums.SIX), nums.SIX, ColiderPosition[nums.SIX - 1], ColliderExtents[nums.SIX - 1], ColliderRotate[nums.SIX - 1], GetNormalMap());


	for (auto& partdate : m_PartList.childrenParts)
	{
		std::unique_ptr<IHouseMoveObjectsComponent> part = std::make_unique<HouseMoveObjectsComponent>(
			nullptr,
			GetPosition(),
			GetRotate(),
			FALL_SPEED_ACCELERATION,
			EXPLOSIVE_ROTATE,
			EXPLOSIVE_RANDOM_POWER,
			EXPLOSIVE_POWER,
			partdate
		);
		AddParts(std::move(part));
	}
	SetModel(rsources->GetHouseModel());
	GetRoughCollider()->SetPosition(GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.f, 4.5f, 0.f), GetRotate()));
	GetRoughCollider()->SetRadius(GetModel()->meshes[0]->boundingSphere.Radius);


	HouseMoveObjects::Initialize(bulletManager, benchManager, ColiderPosition, ColliderExtents, ColliderRotate);

}


HouseMoveObjects::HouseMoveObjects():
	m_position(SimpleMath::Vector3::Zero),
	m_rotate(SimpleMath::Quaternion::Identity),
	m_survival(false),
	m_timer(0),
	m_killCountFlag(false),
	m_allSurvivalFlag(true),
	m_pPartModel(nullptr),
	m_world(),
	m_normalMap(nullptr)
{
	m_roughCollider = std::make_unique<Collider::Sphere>();
}

HouseMoveObjects::~HouseMoveObjects()
{
}
void HouseMoveObjects::Initialize(BulletManager* bulletManager, HouseMoveObjectsManager* benchManager,
	std::vector<DirectX::SimpleMath::Vector3> ColiderPosition[],
	std::vector<DirectX::SimpleMath::Vector3> ColliderExtents[],
	std::vector<DirectX::SimpleMath::Quaternion> ColliderRotate[])
{
	ColiderPosition;
	ColliderExtents;
	ColliderRotate;
	m_pBulletManager = bulletManager;

	m_pBenchManager = benchManager;
	//当たり判定を生成
	m_timer = 0;

	//スケーリング、位置調整、回転をさせる
	m_world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	m_world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

	for (auto& parts : m_parts)
	{
		parts->Initialize();
	}
	m_survival = true;

}
void HouseMoveObjects::Update(const float& elapsedTime)
{	
	//パーツが生きているか
	bool PartsSurvival = false;
	for (auto& parts : m_parts)
	{
		if (parts->GetSurvival())
		{
			parts->Update(elapsedTime,m_position, m_rotate);
			PartsSurvival = true;
		}
		else
			parts->Explosion(elapsedTime);
	}
	//パーツがすべて死んだらアニメーションの時間を図る
	if (!PartsSurvival)
	{
		m_timer += elapsedTime;
		//キルカウントしてなかったらする
		if (!m_killCountFlag)
		{
			m_pBenchManager->SetBenchKillCount(m_pBenchManager->GetBenchKillCount() + 1);
			//カウントしたらtrueにする
			m_killCountFlag = true;
		}

		//アニメーションが終わったらなくす
		if (m_timer >= ANIMATION_TIME)
			m_survival = false;
	}
	if (m_pBulletManager)
		m_pBulletManager->CheckHitDestructionObjects(this);

	//一つでも壊れているか
	for (auto& parts : m_parts)
	{
		if (!parts->SurvivalCheck())
		{
			m_allSurvivalFlag = false;
			break;
		}
	}
}

void HouseMoveObjects::Render()
{
	if (m_allSurvivalFlag)
	{
		//視界に入っているか
		if (Draw::GetInstance()->VisibilityRange(GetPosition(), GetModel()->meshes[0]->boundingSphere.Radius))
			return;

		// 飛行機の描画
		Draw::GetInstance()->ShadowMapRender(m_pPartModel, m_world,m_normalMap);
	}
	else
		for (auto& parts : m_parts)
			parts->Render();

		//Draw::GetInstance()->TestSphereModel(GetRoughCollider()->GetRadius(), GetRoughCollider()->GetPosition());
}

void HouseMoveObjects::RenderShadowTex()
{
	if (m_allSurvivalFlag)
	{
		// 飛行機の描画
		Draw::GetInstance()->ShadowMapTexCreate(m_pPartModel, m_world);
	}
	else
		for (auto& parts : m_parts)
			parts->RenderShadowTex();
}

void HouseMoveObjects::SetpositionRandam(const float& min, const float& max)
{
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> distance(min, max);

	float x = static_cast<float>(distance(engine));
	float z = static_cast<float>(distance(engine));

	m_position = SimpleMath::Vector3(x, 0, z);
	m_rotate = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, x);
}


void HouseMoveObjects::CreateModelsFromCMONum(PartListObj& partsList, DirectX::Model* model, int& arrayNum,
	std::vector<DirectX::SimpleMath::Vector3> ColiderPosition,
	std::vector<DirectX::SimpleMath::Vector3> ColliderExtents,
	std::vector<DirectX::SimpleMath::Quaternion> ColliderRotate,
	ID3D11ShaderResourceView* normalMap
)
{
	std::unique_ptr<Collider::MultipleHitDetermination> colliders = std::make_unique<Collider::MultipleHitDetermination>();
	std::unique_ptr<Collider::Sphere> colliderSphere = std::make_unique<Collider::Sphere>();

	// floatからVector3に変換
	colliderSphere->SetPosition(DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(model->meshes[0]->boundingBox.Center), GetRotate()) + GetPosition());

	colliderSphere->SetRadius(model->meshes[0]->boundingSphere.Radius);

	for (size_t i = 0; i < ColiderPosition.size(); i++)
	{
		// CreateOBBColliderでコライダーを作成し追加します。
		colliders->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(
			GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(model->meshes[0]->boundingBox.Center),GetRotate()),					//モデルの中心がずれているので調整
			GetRotate(),
			ColiderPosition[i],
			ColliderRotate[i],
			ColliderExtents[i]
		));

	}

	arrayNum = static_cast<int>(partsList.childrenParts.size());
	PartListObj a = {};
	a.model = model;
	a.col = std::move(colliders);
	a.colSphere = std::move(colliderSphere);
	a.normalMap = normalMap;
	partsList.childrenParts.push_back(std::move(a));

}
