#include "pch.h"
#include"WindmillBlade_01.h"
#include"WindmillPartFactory.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include<random>

const float WindmillBlade_01::FALL_SPEED_ACCELERATION	(0.12f / 60);	//落下の加速度			(m/s)
const float WindmillBlade_01::EXPLOSIVE_ROTATE			(120.0f / 60);	//モデルの回転の速さ	(°/s）
const float WindmillBlade_01::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//爆発の横のパワー		(m/s)
const float WindmillBlade_01::EXPLOSIVE_POWER(2.0f / 60);		//爆発の横のパワー		(m/s)

const float PROPELLER_ACCELERATION(2.0f / 60);//プロペラの回転の加速度(°/s）
const float PROPELLER_COOL_TIME(0.95f);	//空気抵抗

WindmillBlade_01::WindmillBlade_01(IWindmillComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	WindmillComponent(
		parent,
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(-6, 12.6f, 0), angle),
		angle
	),
	m_angle(),
	m_velcity()
{
	//モデルをセット
	SetPartModel(Resources::GetInstance()->GetWindmillBladeModel());
}

WindmillBlade_01::~WindmillBlade_01()
{

}

void WindmillBlade_01::Initialize()
{	
	//当たり判定の初期化
	GetCollider()->Initialize(
		GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		GetRotate(),
		GetPartModel()->meshes[0]->boundingBox.Extents
	);
	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Initialize();
	}
}

void WindmillBlade_01::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{	
	//加速度計算
	m_velcity.z += PROPELLER_ACCELERATION;

	//加速度に空気抵抗をかける
	m_velcity.z *= PROPELLER_COOL_TIME;

	//プロペランの角度に速度を足す
	m_angle.z += m_velcity.z;

	//親が動かないから更新しない//

	//クオータニオン回転を作る
	SetRotate(
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3::UnitX,
			DirectX::XMConvertToRadians(m_angle.z)
		) *
		angle
	);

	//当たり判定の更新
	GetCollider()->Update(
		GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		GetRotate()
		);

	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Update(GetPosition(), GetRotate());
	}

}

void WindmillBlade_01::Render()
{
	//スケーリング、位置調整、回転をさせる
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

	world = rotate * translation;

	// 飛行機の描画
	Draw::GetInstance()->ShadowMapRenderNoPicture(GetPartModel(), world);
	//Draw::GetInstance()->TestCubeModel(
	//	GetPartModel()->meshes[0]->boundingBox.Extents, 
	//	GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
	//	GetRotate()
	//);

		// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Render();
	}
}

void WindmillBlade_01::Finalize()
{
}

