#include "pch.h"
#include"PlayerStopMotion.h"
#include <math.h>
using namespace DirectX;


PlayerStopMotion::PlayerStopMotion(
	Player* motions,
	BulletManager* bulletManager,
	RespawnManager* respawnManager,
	SupplyPointManager* supplyPointManager,
	EnemyManager* enemyManager,
	CoinManager* coinManager
) :
	m_pPlayer(motions),
	m_pRespawnManager(respawnManager),
	m_pSupplyPointManager(supplyPointManager),
	m_pEnemyManager(enemyManager),
	m_pCoinManager(coinManager),
	m_pBulletManager(bulletManager)
{
}

PlayerStopMotion::~PlayerStopMotion()
{

}

void PlayerStopMotion::Initialize()
{
	////リスポーン地点に位置をセット
	//m_pPlayer->SetPosition(m_pRespawnManager->GetRespawnPosition());

	//プレイヤーの状態によって半径が変わるのでセット
	m_pPlayer->GetCollider()->SetRadius(1.3f);
}

void PlayerStopMotion::Update(const float& elapsedTime)
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

	//仮の燃料切れのモーション
	if (m_pPlayer->GetFuel() <= 0)
	{
		m_pPlayer->SetFuel(m_pPlayer->GetFuel()-1);
		if (m_pPlayer->GetFuel() <= -200)
		{
			//死んだので強制的に血の演出をさせる
			m_pPlayer->SetHP(0);
			m_pPlayer->GetBloodEffect()->Update(m_pPlayer->GetHP());

			m_pPlayer->SetIState(m_pPlayer->GetKillMotion());
		}

	}

	//パーツの更新
	m_pPlayer->PartsUpdate();

	if (m_pRespawnManager)
		//リスポーンの衝突処理
		m_pRespawnManager->CheckHitCharacter(m_pPlayer);

	if (m_pSupplyPointManager)
		//アイテムの衝突処理
		m_pSupplyPointManager->CheckHitCharacter(m_pPlayer);

	if (m_pEnemyManager)
		//敵の衝突処理
		m_pEnemyManager->CheckHitCharacter(m_pPlayer);

	if (m_pCoinManager)
		//コインの衝突処理
		m_pCoinManager->CheckHitCharacter(m_pPlayer);

	if (m_pBulletManager)
		//コインの衝突処理
		m_pBulletManager->CheckHitDamegeObjects(m_pPlayer, Bullet::BulletParent::PlayerBullet);
}

void PlayerStopMotion::Render()
{
	m_pPlayer->PartsRender();
	m_pPlayer->GetPlayerEffect()->Render();
	m_pPlayer->GetBloodEffect()->Render();
}

void PlayerStopMotion::Finalize()
{
}

void PlayerStopMotion::Motion(const float& elapsedTime)
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

	//WASDキーで角度の加速度計算
	if (KeyboardSingleton::GetInstance()->Up())			playerVelcity.x += Player::PLAYER_BEND_ACCELERATION;
	if (KeyboardSingleton::GetInstance()->Down())		playerVelcity.x -= Player::PLAYER_BEND_ACCELERATION;
	if (KeyboardSingleton::GetInstance()->Left())		playerVelcity.y += Player::PLAYER_BEND_ACCELERATION;
	if (KeyboardSingleton::GetInstance()->Right())		playerVelcity.y -= Player::PLAYER_BEND_ACCELERATION;
	if (KeyboardSingleton::GetInstance()->LeftRool())	playerVelcity.z += Player::PLAYER_BEND_ACCELERATION;
	if (KeyboardSingleton::GetInstance()->RightRool())	playerVelcity.z -= Player::PLAYER_BEND_ACCELERATION;

	//角度に速度を足す
	playerAngle = playerVelcity;

	m_pPlayer->SetTiltAnimation(playerVelcity.y);

	//クオータニオン回転を作る
	SimpleMath::Quaternion p;
	p = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, m_pPlayer->GetTiltAnimation()
	);

	//クオータニオン回転を作る
	SimpleMath::Quaternion q;
	q = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitZ, XMConvertToRadians(playerAngle.z));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitX, XMConvertToRadians(playerAngle.x));
	q *= SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(playerAngle.y));
	m_pPlayer->SetAnimetionRotate(q * m_pPlayer->GetAnimetionRotate());

	//spaseを押したら減速＆プロペラ止まる
	if (keystate.LeftShift){}
	else
		if(m_pPlayer->GetFuel() >= 0)
			m_pPlayer->SetIState(m_pPlayer->GetMotion());
		
	//スピードが減速したら落下
	if (speed <= Player::PLAYER_STRAT_FALLING_SPEED)	gravity += Player::PLAYER_FALL_SPEED__ACCELERATION;

	//落下スピードのマックス
	if (gravity >= Player::PLAYER_FALL_SPEED_MAX)	gravity = Player::PLAYER_FALL_SPEED_MAX;

	//破壊される方向に飛ばす
	position += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.0f, -speed), m_pPlayer->GetRotate());

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

	//回転をセット
	m_pPlayer->SetRotate(p * m_pPlayer->GetAnimetionRotate());

	//カメラの回転をセット
	m_pPlayer->SetCameraRotate(m_pPlayer->GetAnimetionRotate());

	//位置をセット
	m_pPlayer->SetPosition(position);
	//進行ベクトル
	DirectX::SimpleMath::Vector3 reflectionVector = position - previousposition;
	reflectionVector.Normalize();
	m_pPlayer->SetReflectionVector(reflectionVector);

}
