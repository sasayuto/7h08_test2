#include "pch.h"
#include"Tail.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include<random>
#include"Propeller.h"

using namespace DirectX;

const float Tail::FALL_SPEED_ACCELERATION(0.09f / 60);	//落下の加速度			(m/s)
const float Tail::EXPLOSIVE_ROTATE(120.0f / 60);	//モデルの回転の速さ(°/s）
const float Tail::EXPLOSIVE_RANDOM_POWER(1.4f / 60);	//爆発の横のパワー		(m/s)
const float Tail::EXPLOSIVE_POWER(5.0f / 60);			//爆発の横のパワー		(m/s)

Tail::Tail(IPlayerComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	PlayerComponent(parent, position, angle)
{
	SetPartModel(Resources::GetInstance()->GetTailModel());

	GetCollider()->Initialize(
		GetPosition(),
		GetRotate(),
		GetPartModel()->meshes[0]->boundingBox.Extents
	);

}

Tail::~Tail()
{

}

void Tail::Initialize(const DirectX::SimpleMath::Vector3& reflectionVector)
{
	//親の反射ベクトルをセット（最初は反射ベクトルが同じなので）
	SetReflectionVector(reflectionVector);

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
}

void Tail::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//モデル位置調整
	SetPosition(SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.04f, 0.69f), angle));

	//親の位置と合わせる
	SetPosition(position + GetPosition());

	//親の回転と合わせる
	SetRotate(angle);

	//当たり判定の更新
	GetCollider()->Update(
		GetPosition(),
		GetRotate()
	);
}


void Tail::Render()
{
	//スケーリング、位置調整、回転をさせる
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	world *= SimpleMath::Matrix::CreateTranslation(GetPosition());

	// 飛行機の描画
	Draw::GetInstance()->ShadowMapRenderNoPicture(GetPartModel(), world);

	//Draw::GetInstance()->TestCubeModel(
	//	GetPartModel()->meshes[0]->boundingBox.Extents,
	//	GetPosition(),
	//	GetRotate()
	//);
}

void Tail::Explosion()
{
	SimpleMath::Vector3 position = GetPosition();
	DirectX::SimpleMath::Vector3 move = DirectX::SimpleMath::Vector3::Zero;
	//ランダムな方向
	move += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0, 0, EXPLOSIVE_RANDOM_POWER), GetRandomRotate());

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

	SetRotate(q * GetRotate());
	SetPosition(position);

	//当たり判定の更新
	GetCollider()->Update(
		GetPosition(),
		GetRotate()
	);
}

void Tail::Finalize()
{
}

void Tail::Speed()
{
}


