#include "pch.h"
#include"StreetLightConnection.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"StreetLightPartFactory.h"
#include<random>

const float StreetLightConnection::FALL_SPEED_ACCELERATION	(0.12f / 60);	//落下の加速度			(m/s)
const float StreetLightConnection::EXPLOSIVE_ROTATE			(120.0f / 60);	//モデルの回転の速さ	(°/s）
const float StreetLightConnection::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//爆発の横のパワー		(m/s)
const float StreetLightConnection::EXPLOSIVE_POWER(2.0f / 60);		//爆発の横のパワー		(m/s)

StreetLightConnection::StreetLightConnection(IStreetLightComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	StreetLightComponent(
		parent,
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0.66f, 3.66f, 0), angle),
		angle
	)
{
	AddPart(StreetLightPartFactory::CreateStreetLightLight(nullptr, GetPosition(), GetRotate()));

	//モデルをセット
	SetPartModel(Resources::GetInstance()->GetStreetLightConnectionModel());
}

StreetLightConnection::~StreetLightConnection()
{

}

void StreetLightConnection::Initialize()
{	
	//360度ランダムな方向を取得
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> dist(0, 6.28f);
	float explosionSpeedX = static_cast<float>(dist(engine));

	//ランダムな回転をセット
	SetRandomRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, explosionSpeedX));

	//爆発力をランダムにする
	std::uniform_real_distribution<> power(5, 10);
	float explosionPower = static_cast<float>(power(engine)) / 60;

	//爆発力を重力に付ける
	SetGravity(-explosionPower);

	//当たり判定の初期化
	GetCollider()->Initialize(
		GetPosition(),
		GetRotate(),
		GetPartModel()->meshes[0]->boundingBox.Extents
	);
	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Initialize();
	}
}

void StreetLightConnection::Update(const float& elapsedTime, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{

	//親が動かないから更新しない//
	////親の位置と合わせる
	//SetPosition(position);
	////親の回転と合わせる
	//SetRotate(angle);
	////当たり判定の更新
	//GetCollider()->Update(
	//	GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
	//	GetRotate()
	//	);

	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		if (playerPart->GetSurvival())	playerPart->Update(elapsedTime, GetPosition(), GetRotate());
		else							playerPart->Explosion(elapsedTime);
	}
}
void StreetLightConnection::Explosion(const float& elapsedTime)
{
	//アニメーションを超えたら更新しない
	if (GetTimer() >= Bench::ANIMATION_TIME)
		return;

	//時間を計測
	SetTimer(GetTimer() + elapsedTime);
	DirectX::SimpleMath::Vector3 position = GetPosition();

	//ランダムな方向
	position += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, 0, EXPLOSIVE_RANDOM_POWER), GetRandomRotate());

	////破壊される方向に飛ばす(反射ベクトル)
	//position += -GetReflectionVector() * EXPLOSIVE_POWER;

	//重力をつける
	SetGravity(GetGravity() + FALL_SPEED_ACCELERATION);

	//キル座標に重力をつける
	position.y -= GetGravity();

	//爆発のクオータニオン回転
	DirectX::SimpleMath::Quaternion q = DirectX::SimpleMath::Quaternion::Identity;
	q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(EXPLOSIVE_ROTATE));
	q *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(EXPLOSIVE_ROTATE));

	SetPosition(position);

	//当たり判定の更新
	GetCollider()->Update(
		GetPosition(),
		GetRotate()
	);
	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Explosion(elapsedTime);
	}

	//if (GetPosition().y <= 0)
	//	SetPosition(DirectX::SimpleMath::Vector3(GetPosition().x, 0, GetPosition().z));
	//else
	SetRotate(q * GetRotate());

}

void StreetLightConnection::Render()
{
	//アニメーションを超えたら描画しない
	if (GetTimer() >= Bench::ANIMATION_TIME)
		return;

	//視界に入っているか
	if (Draw::GetInstance()->VisibilityRange(GetPosition(), 10))
		return;

	//スケーリング、位置調整、回転をさせる
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

	// 飛行機の描画
	Draw::GetInstance()->ShadowMapRenderNoPicture(GetPartModel(), world);

	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Render();
	}
}


void StreetLightConnection::Finalize()
{
}
