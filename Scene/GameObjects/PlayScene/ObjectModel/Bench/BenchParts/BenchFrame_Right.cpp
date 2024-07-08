#include "pch.h"
#include"BenchFrame_Right.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"BenchPartFactory.h"
#include<random>

const float BenchFrame_Right::FALL_SPEED_ACCELERATION(0.18f / 60);	//�����̉����x			(m/s)
const float BenchFrame_Right::EXPLOSIVE_ROTATE			(50.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float BenchFrame_Right::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float BenchFrame_Right::EXPLOSIVE_POWER(2.0f / 60);		//�����̉��̃p���[		(m/s)

BenchFrame_Right::BenchFrame_Right(IMoveObjectsComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	MoveObjectsComponent(
		parent,
		DirectX::SimpleMath::Vector3(4.0f, 0, 0),
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(4.0f,0 ,0), angle),
		angle,
		FALL_SPEED_ACCELERATION,
		EXPLOSIVE_ROTATE,
		EXPLOSIVE_RANDOM_POWER,
		EXPLOSIVE_POWER
	)
{

	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetBenchFrameModel());
}
