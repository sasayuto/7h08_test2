#include "pch.h"
#include"BenchFrame_Left.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"BenchPartFactory.h"
#include<random>

const float BenchFrame_Left::FALL_SPEED_ACCELERATION	(0.18f / 60);	//落下の加速度			(m/s)
const float BenchFrame_Left::EXPLOSIVE_ROTATE			(50.0f / 60);	//モデルの回転の速さ	(°/s）
const float BenchFrame_Left::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//爆発の横のパワー		(m/s)
const float BenchFrame_Left::EXPLOSIVE_POWER(2.0f / 60);		//爆発の横のパワー		(m/s)

BenchFrame_Left::BenchFrame_Left(IMoveObjectsComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	MoveObjectsComponent(
		parent,
		DirectX::SimpleMath::Vector3(-4.0f, 0, 0),
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(-4.0f, 0, 0), angle),
		angle,
		FALL_SPEED_ACCELERATION,
		EXPLOSIVE_ROTATE,
		EXPLOSIVE_RANDOM_POWER,
		EXPLOSIVE_POWER
	)
{
	AddPart(BenchPartFactory::CreateBenchBackWood(this, GetPosition(), GetRotate()));
	AddPart(BenchPartFactory::CreateBenchUnderWood(this, GetPosition(), GetRotate()));

	//モデルをセット
	SetPartModel(Resources::GetInstance()->GetBenchFrameModel());
}
