#include"pch.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"

#include"Bullet.h"
using namespace DirectX;

#define BULLET_MAX_SPEED		(150.0f / 60)		//球の最大スピード		(m/s)



Bullet::Bullet(const float& speed, const int& offensivePower, const float& scale):
	m_bulletparent(),
	m_position(SimpleMath::Vector3::Zero),
	m_isActive(),
	m_bulletModel(Resources::GetInstance()->GetBurretModel()),
	m_scale(SimpleMath::Vector3::One* scale),
	m_speed(speed),
	m_offensivePower(offensivePower), m_move()
{
}

Bullet::~Bullet()
{
}


void Bullet::Initialize(const BulletParent& shooterType, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate)
{
	//選択されたキャラ
	m_bulletparent = shooterType;

	//設定されたキャラのポジションを入れる
	m_position = position;

	m_isActive = true;

	//ボールの方向
	m_rotate = rotate;

	//当たり判定を生成
	m_collider = std::make_unique<Collider::Sphere>();

	//当たり判定に位置と半径をセット
	m_collider->SetPosition(m_position);
	m_collider->SetRadius(m_scale.x);

}

void Bullet::Update()
{
	//発射されているか

	//球の種類によって更新を分ける
	//減速度計算

	//前方に調整し減速
	m_move = SimpleMath::Vector3::Transform(SimpleMath::Vector3(0.0f, 0.0f, -m_speed), m_rotate);

	//ボールの移動
	m_position += m_move;

	//当たり判定に位置と半径をセット
	m_collider->SetPosition(m_position);
}

void Bullet::Render()
{
	//スケーリング、位置調整、回転をさせる
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;
	world *= SimpleMath::Matrix::CreateFromQuaternion(m_rotate);
	world *= SimpleMath::Matrix::CreateScale(m_scale);
	world *= SimpleMath::Matrix::CreateTranslation(m_position);

	// 飛行機の描画
	Draw::GetInstance()->ShadowMapRenderNoPicture(m_bulletModel, world);
	//Draw::GetInstance()->TestSphereModel(m_collider->GetRadius(), m_collider->GetPosition());
}
void Bullet::RenderShadowTex()
{
	//スケーリング、位置調整、回転をさせる
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	world *= SimpleMath::Matrix::CreateFromQuaternion(GetRotate());

	world *= SimpleMath::Matrix::CreateTranslation(GetPosition());

	//m_collider->Render(GetRotate());
	Draw::GetInstance()->ShadowMapTexCreateNoPicture(m_bulletModel, world);

}

void Bullet::Finalize()
{


}

