#include "pch.h"
#include"PlayerAvoidanceMotion.h"
#include <math.h>
using namespace DirectX;
const float AVOIDANCE_SPEED_RESISTANCE(0.1f / 60);

PlayerAvoidanceMotion::PlayerAvoidanceMotion(
	Player* motions,
	RespawnManager* respawnManager,
	SupplyPointManager* supplyPointManager,
	CoinManager* coinManager
) :
	m_pPlayer(motions),
	m_pRespawnManager(respawnManager),
	m_pSupplyPointManager(supplyPointManager),
	m_pCoinManager(coinManager)
{
}

PlayerAvoidanceMotion::~PlayerAvoidanceMotion()
{

}

void PlayerAvoidanceMotion::Initialize()
{
	////リスポーン地点に位置をセット
	//m_pPlayer->SetPosition(m_pRespawnManager->GetRespawnPosition());

	//プレイヤーの状態によって半径が変わるのでセット
	m_pPlayer->GetCollider()->SetRadius(1.3f);
	//回転をセット
	m_pPlayer->SetAnimetionRotate(m_pPlayer->GetRotate());
}

void PlayerAvoidanceMotion::Update(const float& elapsedTime)
{
	elapsedTime;
	auto mouse = Mouse::Get().GetState();

	//WASDで方向を決める
	Motion(elapsedTime);

	m_pPlayer->GetBloodEffect()->Update(m_pPlayer->GetHP());

	//球の
	float bulletCoolTime = m_pPlayer->GetBulletCoolTime();

	//球のクールタイム
	if (bulletCoolTime > 0.0f)
		bulletCoolTime -= elapsedTime;
	else
		bulletCoolTime = 0.0f;

	m_pPlayer->SetBulletCoolTime(bulletCoolTime);

	//右クリで球発射
	if (mouse.leftButton)
		m_pPlayer->DoubleShot(Player::BULLET_COOL_TIME);

	//hpがなくなったらキルの動き
	if (m_pPlayer->GetHP() <= 0)
	{
		m_pPlayer->SetIState(m_pPlayer->GetKillMotion());
	}

	//hpがなくなったらキルの動き
	if (m_pPlayer->GetFuel() <= 0)
	{
		m_pPlayer->SetIState(m_pPlayer->GetKillMotion());
	}

	//パーツの更新
	m_pPlayer->PartsUpdate();

	if (m_pRespawnManager)
		//リスポーンの衝突処理
		m_pRespawnManager->CheckHitCharacter(m_pPlayer);

	if (m_pSupplyPointManager)
		//アイテムの衝突処理
		m_pSupplyPointManager->CheckHitCharacter(m_pPlayer);

	if (m_pCoinManager)
		//コインの衝突処理
		m_pCoinManager->CheckHitCharacter(m_pPlayer);
}

void PlayerAvoidanceMotion::Render()
{

	m_pPlayer->PartsRender();
	m_pPlayer->GetPlayerEffect()->Render();
	m_pPlayer->GetBloodEffect()->Render();
}

void PlayerAvoidanceMotion::Finalize()
{
}

void PlayerAvoidanceMotion::Motion(const float& elapsedTime)
{
	elapsedTime;
	auto keystate = KeyboardSingleton::GetInstance()->GetKeyboardState();

	//速度をゲット
	SimpleMath::Vector3 playerVelcity = m_pPlayer->GetVelcity();
	//角度をゲット
	SimpleMath::Vector3 playerAngle = m_pPlayer->GetAngle();
	//位置をゲット
	SimpleMath::Vector3 position = m_pPlayer->GetPosition();
	SimpleMath::Vector3 previousposition = position;
	//重力をゲット
	float gravity = m_pPlayer->GetGravity();
	//スピードをゲット
	float speed = m_pPlayer->GetSpeed();

	//注視点をプラスし差分をかける
	m_pPlayer->SetTiltAnimation(
		m_pPlayer->GetTiltAnimation() +
		((DirectX::XMConvertToRadians(725)) - m_pPlayer->GetTiltAnimation()) *
		0.01f
	);

	//プレイヤーのスピードの加速度計算
	speed += Player::PLAYER_ACCELERATION;

	//クオータニオン回転を作る
	SimpleMath::Quaternion p;
	p = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, m_pPlayer->GetTiltAnimation()
	);

	//spaseを押したら減速＆プロペラ止まる

	//スピード上限
	if (speed >= Player::PLAYER_MAX_SPEED)	speed = Player::PLAYER_MAX_SPEED;

	//スピードが減速したら落下
	if (speed <= Player::PLAYER_STRAT_FALLING_SPEED)	gravity += Player::PLAYER_FALL_SPEED__ACCELERATION;

	//落下スピードのマックス
	if (gravity >= Player::PLAYER_FALL_SPEED_MAX)	gravity = Player::PLAYER_FALL_SPEED_MAX;

	float ss = 1 - m_pPlayer->GetTiltAnimation() / DirectX::XMConvertToRadians(720);

	//破壊される方向に飛ばす
	position += SimpleMath::Vector3::Transform(SimpleMath::Vector3(1.f*ss, 0, -speed), m_pPlayer->GetAnimetionRotate());

	if (m_pPlayer->GetTiltAnimation() >= DirectX::XMConvertToRadians(720))
	{
		m_pPlayer->SetIState(m_pPlayer->GetMotion());
	}

	//座標に重力をつける
	position.y -= m_pPlayer->GetGravity();

	//重力をセット
	m_pPlayer->SetGravity(gravity);

	//速度をセット
	m_pPlayer->SetVelcity(playerVelcity);

	//角度をセット
	m_pPlayer->SetAngle(playerAngle);

	//スピードをセット
	m_pPlayer->SetSpeed(speed);

	//カメラの回転をセット
	m_pPlayer->SetRotate(p * m_pPlayer->GetAnimetionRotate()
	);

	//カメラの回転をセット
	m_pPlayer->SetCameraRotate(m_pPlayer->GetCameraRotate());

	//位置をセット
	m_pPlayer->SetPosition(position);
	//進行ベクトル
	DirectX::SimpleMath::Vector3 reflectionVector = position - previousposition;
	reflectionVector.Normalize();
	m_pPlayer->SetReflectionVector(reflectionVector);

}
