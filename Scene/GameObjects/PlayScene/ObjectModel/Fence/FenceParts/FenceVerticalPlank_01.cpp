#include "pch.h"
#include"FenceVerticalPlank_01.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include"FencePartFactory.h"
#include<random>

const float FenceVerticalPlank_01::FALL_SPEED_ACCELERATION(0.18f / 60);	//�����̉����x			(m/s)
const float FenceVerticalPlank_01::EXPLOSIVE_ROTATE(50.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float FenceVerticalPlank_01::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float FenceVerticalPlank_01::EXPLOSIVE_POWER(2.0f / 60);		//�����̉��̃p���[		(m/s)

FenceVerticalPlank_01::FenceVerticalPlank_01(IMoveObjectsComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	MoveObjectsComponent(
		parent,
		DirectX::SimpleMath::Vector3(-10, 2.8f, -0.28f),
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(2.4f, 4, 0), angle),
		angle,
		FALL_SPEED_ACCELERATION,
		EXPLOSIVE_ROTATE,
		EXPLOSIVE_RANDOM_POWER,
		EXPLOSIVE_POWER
	)
{
	AddPart(FencePartFactory::Create(FencePartFactory::FenceParts::FENCE_NAIL_PLANK_CENTER_01, nullptr, GetPosition(), GetRotate()));
	AddPart(FencePartFactory::Create(FencePartFactory::FenceParts::FENCE_NAIL_PLANK_TOP_01, nullptr, GetPosition(), GetRotate()));
	AddPart(FencePartFactory::Create(FencePartFactory::FenceParts::FENCE_NAIL_PLANK_UNDER_01, nullptr, GetPosition(), GetRotate()));

	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetFenceVerticalPlank_01Model());
}

const float FenceVerticalPlank_02::FALL_SPEED_ACCELERATION(0.18f / 60);	//�����̉����x			(m/s)
const float FenceVerticalPlank_02::EXPLOSIVE_ROTATE(50.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float FenceVerticalPlank_02::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float FenceVerticalPlank_02::EXPLOSIVE_POWER(2.0f / 60);		//�����̉��̃p���[		(m/s)

FenceVerticalPlank_02::FenceVerticalPlank_02(IMoveObjectsComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	MoveObjectsComponent(
		parent,
		DirectX::SimpleMath::Vector3(-3.3f, 2.8f, -0.28f),
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(2.4f, 4, 0), angle),
		angle,
		FALL_SPEED_ACCELERATION,
		EXPLOSIVE_ROTATE,
		EXPLOSIVE_RANDOM_POWER,
		EXPLOSIVE_POWER
	)
{
	AddPart(FencePartFactory::Create(FencePartFactory::FenceParts::FENCE_NAIL_PLANK_CENTER_02, nullptr, GetPosition(), GetRotate()));
	AddPart(FencePartFactory::Create(FencePartFactory::FenceParts::FENCE_NAIL_PLANK_TOP_02, nullptr, GetPosition(), GetRotate()));

	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetFenceVerticalPlank_02Model());
}

const float FenceVerticalPlank_03::FALL_SPEED_ACCELERATION(0.18f / 60);	//�����̉����x			(m/s)
const float FenceVerticalPlank_03::EXPLOSIVE_ROTATE(50.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float FenceVerticalPlank_03::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float FenceVerticalPlank_03::EXPLOSIVE_POWER(2.0f / 60);		//�����̉��̃p���[		(m/s)

FenceVerticalPlank_03::FenceVerticalPlank_03(IMoveObjectsComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	MoveObjectsComponent(
		parent,
		DirectX::SimpleMath::Vector3(3.45f, 2.8f, -0.28f),
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(2.4f, 4, 0), angle),
		angle,
		FALL_SPEED_ACCELERATION,
		EXPLOSIVE_ROTATE,
		EXPLOSIVE_RANDOM_POWER,
		EXPLOSIVE_POWER
	)
{
	AddPart(FencePartFactory::Create(FencePartFactory::FenceParts::FENCE_NAIL_PLANK_CENTER_03, nullptr, GetPosition(), GetRotate()));
	AddPart(FencePartFactory::Create(FencePartFactory::FenceParts::FENCE_NAIL_PLANK_TOP_03, nullptr, GetPosition(), GetRotate()));

	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetFenceVerticalPlank_03Model());
}

const float FenceVerticalPlank_04::FALL_SPEED_ACCELERATION(0.18f / 60);	//�����̉����x			(m/s)
const float FenceVerticalPlank_04::EXPLOSIVE_ROTATE(50.0f / 60);	//���f���̉�]�̑���	(��/s�j
const float FenceVerticalPlank_04::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//�����̉��̃p���[		(m/s)
const float FenceVerticalPlank_04::EXPLOSIVE_POWER(2.0f / 60);		//�����̉��̃p���[		(m/s)

FenceVerticalPlank_04::FenceVerticalPlank_04(IMoveObjectsComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	MoveObjectsComponent(
		parent,
		DirectX::SimpleMath::Vector3(10.27f, 2.8f, -0.28f),
		position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(2.4f, 4, 0), angle),
		angle,
		FALL_SPEED_ACCELERATION,
		EXPLOSIVE_ROTATE,
		EXPLOSIVE_RANDOM_POWER,
		EXPLOSIVE_POWER
	)
{
	//���f�����Z�b�g
	SetPartModel(Resources::GetInstance()->GetFenceVerticalPlank_04Model());
}
