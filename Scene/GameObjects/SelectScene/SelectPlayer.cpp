#include "pch.h"
#include"SelectPlayer.h"
#include <math.h>

#include"Scene/GameObjects/PlayScene/Character/Player/PlayerPartFactory.h"
//#include"Scene/GameObjects/PlayScene/MiniMap/GetPosotion/GetPosition.h"
//#include"Scene/GameObjects/PlayScene/Character/Airship/AirshipManager.h"
//#include"Scene/GameObjects/PlayScene/ObjectModel/Windmill/WindmillManager.h"
//#include"Scene/GameObjects/PlayScene/ObjectModel/Objects/Walls/BigBrickWall/BigBrickWallManager.h"
//#include"Scene/GameObjects/PlayScene/Sandstorm/SandstormManager.h"
//#include"Scene/GameObjects/PlayScene/Character/Turret/TurretManager.h"
#include"Scene/GameObjects/PlayScene/Effect/PlayerEffect.h"

using namespace DirectX;

const float  SelectPlayer::PLAYER_BEND_ACCELERATION(30.0f);
const int SelectPlayer::PLAYER_MAX_HP(2000);							//プレイヤーのHP	

SelectPlayer::SelectPlayer() :
	m_cameraRotate(SimpleMath::Quaternion::Identity),
	m_AnimetionRotate(),
	m_TiltAnimation(0.0f),
	m_playerEffect(nullptr),
	m_position(SimpleMath::Vector3(0,1,0)),
	m_velcity(SimpleMath::Vector3::Zero),
	m_rotate(SimpleMath::Quaternion::Identity),
	m_bulletCoolTime(),
	m_HP(PLAYER_MAX_HP),
	m_fuel(PLAYER_MAX_FUEL),
	m_offensivePower(PLAYER_OFFENSIVE_POWER),
	m_speed(),
	m_angle(SimpleMath::Vector3::Zero),
	m_bulletType(Bullet::BulletType::None),
	m_pBulletManager(nullptr),
	m_gravity(){
}

SelectPlayer::~SelectPlayer()
{
}

void SelectPlayer::Initialize(BulletManager* bulletManager)
{
	//ゲージとベースを描画する
	for (int i = 0; i < 2; i++)
	{
		//ゲージののリスポーンのインスタンスを生成する
		m_HorizontalTriangle[i] = std::make_unique<tito::MoveUserInterface>();
		m_HorizontalTrianglecol[i] = std::make_unique<Collider::Box2D>();

	}
	//必要な情報をセットする
	m_HorizontalTriangle[0]->Create(
		L"Resources/Textures/HorizontalTrianglel.png"
		, DirectX::SimpleMath::Vector2(-1120, 0)
		, DirectX::SimpleMath::Vector2::One
		, tito::ANCHOR::MIDDLE_RIGHT
		, tito::POSITION_ANCHOR::MIDDLE_RIGHT
	);
	//必要な情報をセットする
	m_HorizontalTriangle[1]->Create(
		L"Resources/Textures/HorizontalTriangle.png"
		, DirectX::SimpleMath::Vector2(-90, 0)
		, DirectX::SimpleMath::Vector2::One
		, tito::ANCHOR::MIDDLE_RIGHT
		, tito::POSITION_ANCHOR::MIDDLE_RIGHT
	);

	for (int i = 0; i < 2; i++)
	{
		//当たり判定の初期化
		//位置、サイズを修正した値を渡す
		m_HorizontalTrianglecol[i]->Initialize(
			m_HorizontalTriangle[i]->TexPositionCalculation(),
			m_HorizontalTriangle[i]->TexSizeCalculation()
		);
	}

	//初期回転
	m_angle.y = 15.0f;
	m_velcity.y = 15.0f;

	//球のアドレス
	m_pBulletManager = bulletManager;

	m_playerEffect = std::make_unique<PlayerEffect>();
	m_playerEffect->Initialize();
	//当たり判定を生成
	m_collider = std::make_unique<Collider::Sphere>();

	//当たり判定に位置と半径をセット
	m_collider->SetPosition(m_position);

	m_collider->SetRadius(1.3f);

	//リセットの後に書く（位置や角度を持たせるから）
	// プレイヤーにプロペラを追加する
	AddParts(PlayerPartFactory::CreatePlayerBody(nullptr, GetPosition(), GetRotate()));

	for (auto& parts : m_parts)
	{
		// パーツを初期化
		parts->Initialize(DirectX::SimpleMath::Vector3::Zero);
	}

}

void SelectPlayer::Update(const float& elapsedTime, const bool& decisionFlag, const bool& returnDecisionFlag)
{
	//当たり判定に位置と半径をセット
	m_collider->SetPosition(m_position);

	//決定してたら前進
	if (decisionFlag)
	{
		if (!returnDecisionFlag)
		{
			m_speed += 0.5f / 60.0f;
			//破壊される方向に飛ばす
			m_position += SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.0f, -m_speed), m_rotate);


			for (auto& parts : m_parts)
			{
				// パーツを更新する
				parts->Speed();
			}
			m_playerEffect->Update(elapsedTime, m_position, m_rotate, m_HP);
		}
	}

	//決定してなかったら左右選択可能
	if (!decisionFlag)
	{
		//前のシーンに戻るときにもやめる
		if (!returnDecisionFlag)
		{
			auto mouseTr = KeyboardTracker::GetInstance()->GetMouseTracker();
			auto mouse = KeyboardSingleton::GetInstance()->GetMouseState();

			if (m_HorizontalTrianglecol[0]->CheckHitPoint(mouse.x, mouse.y))
				if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
					m_angle.y += SelectPlayer::PLAYER_BEND_ACCELERATION;
			if (m_HorizontalTrianglecol[1]->CheckHitPoint(mouse.x, mouse.y))
				if (mouseTr.leftButton == Mouse::ButtonStateTracker::ButtonState::RELEASED)
					m_angle.y -= SelectPlayer::PLAYER_BEND_ACCELERATION; 

		}
	}

	//角度に差分をかける
	m_velcity.y = ((m_angle.y - m_velcity.y) * 0.10f) + m_velcity.y;

	//クオータニオン回転を作る
	m_rotate = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, XMConvertToRadians(m_velcity.y));

	for (auto& parts : m_parts)
	{
		// パーツを更新する
		parts->Update(GetPosition(), GetRotate());
	}

}

void SelectPlayer::Render()
{	
	m_playerEffect->Render();
	for (auto& part : m_parts)
	{
		//パーツを更新する
		part->Render();
	}

}

void SelectPlayer::Finalize()
{
}

void SelectPlayer::ShadowMapRender()
{
	for (auto& part : m_parts)
	{
		//パーツを更新する
		part->RenderShadowTex();
	}

}

void SelectPlayer::PartsInitialize()
{
	for (auto& parts : m_parts)
	{
		// パーツを初期化
		parts->Initialize(DirectX::SimpleMath::Vector3::Zero);
	}
}

void SelectPlayer::PartsUpdate()
{
}

void SelectPlayer::PartsExplosion()
{
	for (auto& parts : m_parts)
	{
		// パーツを更新する
		parts->Explosion();
	}
}

void SelectPlayer::PartsMotion()
{
	for (auto& parts : m_parts)
	{
		// パーツを更新する
		parts->Speed();
	}
}

void SelectPlayer::PartsRender()
{
	for (auto& part : m_parts)
	{
		//パーツを更新する
		part->Render();
	}

}
