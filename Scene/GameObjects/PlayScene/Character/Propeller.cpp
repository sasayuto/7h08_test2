#include "pch.h"
#include"Propeller.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include<random>


using namespace DirectX;

const float Propeller::FALL_SPEED_ACCELERATION(0.08f / 60);	//落下の加速度			(m/s)
const float Propeller::PROPELLER_ACCELERATION(60.0f / 60);//プロペラの回転の加速度(°/s）
const float Propeller::PROPELLER_COOL_TIME(0.95f);	//空気抵抗
const float Propeller::EXPLOSIVE_ROTATE(120.0f / 60);		//モデルの回転の速さ(°/s）
const float Propeller::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//爆発の横のパワー		(m/s)
const float Propeller::EXPLOSIVE_POWER(5.0f / 60);			//爆発の横のパワー		(m/s)


Propeller::Propeller(IPlayerComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	PlayerComponent(parent, position, angle),
	m_angle(angle),
	m_velcity(SimpleMath::Vector3::Zero)
{
	//モデルをセット
	SetPartModel(Resources::GetInstance()->GetPropellerModel());

	//当たり判定の初期化
	GetCollider()->Initialize(
		GetPosition(),
		GetRotate(),
		GetPartModel()->meshes[0]->boundingBox.Extents
	);
}

Propeller::~Propeller()
{

}

void Propeller::Initialize(const DirectX::SimpleMath::Vector3& reflectionVector)
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

void Propeller::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	//加速度に空気抵抗をかける
	m_velcity.z *= PROPELLER_COOL_TIME;

	//プロペランの角度に速度を足す
	m_angle.z += m_velcity.z;

	//モデル位置調整
	SetPosition(SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.10f, -0.76f), angle));

	//親の位置と合わせる
	SetPosition(position + GetPosition());

	//クオータニオン回転を作る
	SimpleMath::Quaternion q;
	q = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, XMConvertToRadians(m_angle.z));
	//親の回転と合わせる
	SetRotate(q * angle);

	//当たり判定の更新
	GetCollider()->Update(
		GetPosition(),
		GetRotate()
	);
}


void Propeller::Render()
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

void Propeller::Explosion()
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

void Propeller::Finalize()
{
}

void Propeller::Speed()
{
	//加速度計算
	m_velcity.z += PROPELLER_ACCELERATION;
}


