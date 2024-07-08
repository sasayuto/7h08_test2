#include "pch.h"
#include"WindmillRoom.h"
#include"WindmillPartFactory.h"
#include"Scene/GameObjects/Models/Draw.h"
#include"Scene/GameObjects/Models/Resources.h"
#include<random>

const float WindmillRoom::FALL_SPEED_ACCELERATION	(0.12f / 60);	//落下の加速度			(m/s)
const float WindmillRoom::EXPLOSIVE_ROTATE			(120.0f / 60);	//モデルの回転の速さ	(°/s）
const float WindmillRoom::EXPLOSIVE_RANDOM_POWER(1.4f / 60);		//爆発の横のパワー		(m/s)
const float WindmillRoom::EXPLOSIVE_POWER(2.0f / 60);		//爆発の横のパワー		(m/s)


WindmillRoom::WindmillRoom(IWindmillComponent* parent, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) :
	WindmillComponent(parent, position, angle)
{
	//モデルをセット
	SetPartModel(Resources::GetInstance()->GetWindmillRoomModel());
}

WindmillRoom::~WindmillRoom()
{

}

void WindmillRoom::Initialize()
{	

	//当たり判定の初期化
	GetCollider()->Initialize(
		GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
		GetRotate(),
		GetPartModel()->meshes[0]->boundingBox.Extents
	);
	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Initialize();
	}

}

void WindmillRoom::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{	
	//親が動かないから更新しない//
	////親の位置と合わせる
	//SetPosition(position);
	////親の回転と合わせる
	//SetRotate(angle);
	////当たり判定の更新
	//GetCollider()->Update(
	//	GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
	//	GetRotate()
	//	);

	// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Update(GetPosition(), GetRotate());
	}

}

void WindmillRoom::Render()
{

	//スケーリング、位置調整、回転をさせる
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	DirectX::SimpleMath::Matrix rotate = DirectX::SimpleMath::Matrix::CreateFromQuaternion(GetRotate());
	DirectX::SimpleMath::Matrix translation = DirectX::SimpleMath::Matrix::CreateTranslation(GetPosition());

	world = rotate * translation;


	// 飛行機の描画
	Draw::GetInstance()->ShadowMapRenderNoPicture(GetPartModel(), world);

	//Draw::GetInstance()->TestCubeModel(
	//	GetPartModel()->meshes[0]->boundingBox.Extents, 
	//	GetPosition() + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(GetPartModel()->meshes[0]->boundingBox.Center), GetRotate()),
	//	GetRotate()
	//);

		// パーツを更新する
	for (auto& playerPart : GetParts())
	{
		playerPart->Render();
	}
}


void WindmillRoom::Finalize()
{
}
