#include "pch.h"
#include"Body.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"Player/PlayerPartFactory.h"
#include<random>
const float Body::FALL_SPEED_ACCELERATION	(0.12f / 60);	//落下の加速度			(m/s)
const float Body::EXPLOSIVE_ROTATE			(120.0f / 60);	//モデルの回転の速さ	(°/s）
const float Body::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//爆発の横のパワー		(m/s)
const float Body::EXPLOSIVE_POWER		(5.0f / 60);		//爆発の横のパワー		(m/s)


Body::Body(IPlayerComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	PlayerComponent(parent, position, angle)
{
	//ボディーに羽を追加する
	AddPart(PlayerPartFactory::CreatePlayerWing(this, GetPosition(), GetRotate()));
	//ボディーにプロペラを追加する
	AddPart(PlayerPartFactory::CreatePlayerPro(this, GetPosition(), GetRotate()));
	//ボディーに尻尾を追加する
	AddPart(PlayerPartFactory::CreatePlayerTail(this, GetPosition(), GetRotate()));
	//ボディーに尻尾を追加する
	AddPart(PlayerPartFactory::CreatePlayerHorizontalStabilizer(this, GetPosition(), GetRotate()));
	//ボディーにホイールサポートを追加する
	AddPart(PlayerPartFactory::CreatePlayerWheelSupport(this, GetPosition(), GetRotate()));

	//モデルをセット
	SetPartModel(Resources::GetInstance()->GetBodyModel());

	//当たり判定の初期化
	GetCollider()->Initialize(
		GetPosition(),
		GetRotate(),
		GetPartModel()->meshes[0]->boundingBox.Extents
	);


}

Body::~Body()
{

}

void Body::Initialize(const DirectX::SimpleMath::Vector3& reflectionVector)
{	
	SetMove(DirectX::SimpleMath::Vector3::Zero);
	//親の反射ベクトルをセット（最初は反射ベクトルが同じなので）
	SetReflectionVector(reflectionVector);

	//360度ランダムな方向を取得
	std::random_device seed;
	std::default_random_engine engine(seed());

	//ランダムな方向を作る
	std::uniform_real_distribution<> dist(0, 6.28f);
	float explosionSpeedX = static_cast<float>(dist(engine));

	//ランダムな回転をセット
	SetRandomRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, explosionSpeedX));

	//爆発力をランダムにする
	std::uniform_real_distribution<> power(5, 10);
	float explosionPower = static_cast<float>(power(engine)) / 60;

	//爆発力を重力に付ける
	SetGravity(-explosionPower);


	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Initialize(reflectionVector);
	}
}

void Body::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//親の位置と合わせる
	SetPosition(position);

	//親の回転と合わせる
	SetRotate(angle);

	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Update(GetPosition(), GetRotate());
	}

	//当たり判定の更新
	GetCollider()->Update(
		GetPosition(),
		GetRotate()
	);
}

void Body::Render()
{
	//スケーリング、位置調整、回転をさせる
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

	// 飛行機の描画
	Draw::GetInstance()->ShadowMapRenderNoPicture(GetPartModel(), world);

	//Draw::GetInstance()->TestCubeModel(
	//	GetPartModel()->meshes[0]->boundingBox.Extents, 
	//	GetPosition(),
	//	GetRotate()
	//);

		// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Render();
	}
}

void Body::Explosion()
{
	using namespace DirectX;

	SimpleMath::Vector3 position = GetPosition();
	DirectX::SimpleMath::Vector3 move=DirectX::SimpleMath::Vector3::Zero;
	//ランダムな方向
	//move += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0, 0, EXPLOSIVE_RANDOM_POWER), GetRandomRotate());

	//破壊される方向に飛ばす(反射ベクトル)
	move += -GetReflectionVector() * EXPLOSIVE_POWER;

	//重力をつける
	SetGravity(GetGravity() + FALL_SPEED_ACCELERATION);

	//キル座標に重力をつける
	move.y -= GetGravity();

	SetMove(move);
	position += move;

	//爆発のクオータニオン回転
	SimpleMath::Quaternion q = SimpleMath::Quaternion::Identity;
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, XMConvertToRadians(EXPLOSIVE_ROTATE));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(EXPLOSIVE_ROTATE));

	//
	SetRotate(q * GetRotate());
	SetPosition(position);

	for (auto& playerPart : GetParts())
	{
		// パーツを更新する
		playerPart->Explosion();
	}

	//当たり判定の更新
	GetCollider()->Update(
		GetPosition(),
		GetRotate()
	);

}

void Body::Finalize()
{
}

void Body::Speed()
{
	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Speed();
	}
}


