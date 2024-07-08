#include "pch.h"
#include"AdjustmentArrow.h"
#include <math.h>
#include<random>

using namespace DirectX;

AdjustmentArrow::AdjustmentArrow(DX::DeviceResources* deviceResources, DirectX::CommonStates* states) :
	m_position(SimpleMath::Vector3::Zero),
	m_AdjustmentArrowModel(),
	m_rotate(SimpleMath::Quaternion::Identity),
	m_ArrowLeftTouchFlag(false),
	m_ArrowRightTouchFlag(false),
	m_ArrowUpTouchFlag(false),
	m_rotateHitNum(NONE_AND_COUNT),
	m_PositionHitNum(NONE_AND_COUNT)
{
	m_states = states;
	m_deviceResources = deviceResources;
	auto device = m_deviceResources->GetD3DDevice();
	EffectFactory fx(device);
	fx.SetDirectory(L"Resources/Models");

	m_AdjustmentArrowModel[0] = Model::CreateFromCMO(device, L"CMO/AdjustmentArrowZ.cmo", fx);
	m_AdjustmentArrowModel[1] = Model::CreateFromCMO(device, L"CMO/AdjustmentArrowX.cmo", fx);
	m_AdjustmentArrowModel[2] = Model::CreateFromCMO(device, L"CMO/AdjustmentArrowY.cmo", fx);
	m_AdjustmentArrowModel[3] = Model::CreateFromCMO(device, L"CMO/AdjustmentArrowOll.cmo", fx);
	m_rotateModel = Model::CreateFromCMO(device, L"CMO/rotateModel.cmo", fx);
	m_rotateModels[0] = Model::CreateFromCMO(device, L"CMO/rotateModelX.cmo", fx);
	m_rotateModels[1] = Model::CreateFromCMO(device, L"CMO/rotateModelY.cmo", fx);
	m_rotateModels[2] = Model::CreateFromCMO(device, L"CMO/rotateModelZ.cmo", fx);
	m_rotateModels[3] = Model::CreateFromCMO(device, L"CMO/AdjustmentArrowOll.cmo", fx);
	m_Cube = Model::CreateFromCMO(device, L"CMO/Cube.cmo", fx);
	for (int i = 0; i < 3; i++)
	{
		//当たり判定を生成
		m_RotateBoxCol[i] = std::make_unique<DirectX::BoundingOrientedBox>();
		//当たり判定を生成
		m_AdjustmentArrowCollider[i] = std::make_unique<DirectX::BoundingOrientedBox>();

	}
	//当たり判定を生成
	m_RotateSphereCol = std::make_unique<DirectX::BoundingSphere>();
	//当たり判定を生成
	m_RotateOll = std::make_unique<DirectX::BoundingSphere>();
}

AdjustmentArrow::~AdjustmentArrow()
{

}

void AdjustmentArrow::Initialize()
{

	auto device = m_deviceResources->GetD3DDevice();
	// ----- 深度ステンシルの作成 ----- //

		D3D11_DEPTH_STENCIL_DESC desc = {};

	// 深度テストを無効にする
	desc.DepthEnable = FALSE;
	// 深度バッファを更新しない
	desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;

	desc.StencilEnable = TRUE;									// ステンシルテストを行う
	desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;		// 0xff
	desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;	// 0xff

	// 表面
	desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;	// OK　１＋
	desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;		// NG　何もしない
	desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;	// NG　何もしない

	desc.BackFace = desc.FrontFace;	// 裏面も同じ

	device->CreateDepthStencilState(&desc, m_depthStencilState_Shadow.ReleaseAndGetAddressOf());
	for (int i = 0; i < 3; i++)
	{
		//当たり判定を生成
		m_RotateBoxCol[i]->Center = GetPosition();
		m_RotateBoxCol[i]->Orientation = GetRotate();

	}
	//当たり判定を生成
	m_RotateSphereCol->Center = GetPosition();
	//当たり判定を生成
	m_RotateOll->Center = GetPosition();
	//当たり判定を生成
	m_RotateSphereCol->Radius = 16;
	//当たり判定を生成
	m_RotateOll->Radius = 3;
	//当たり判定を生成
	m_RotateBoxCol[0]->Extents = DirectX::SimpleMath::Vector3(16, 0.6f, 16);
	//当たり判定を生成
	m_RotateBoxCol[1]->Extents = DirectX::SimpleMath::Vector3(16, 16, 0.6f);
	//当たり判定を生成
	m_RotateBoxCol[2]->Extents = DirectX::SimpleMath::Vector3(0.6f, 16, 16);

	m_AdjustmentArrowCollider[0]->Center = GetPosition() + DirectX::SimpleMath::Vector3(7, 0, 0);
	m_AdjustmentArrowCollider[0]->Extents = DirectX::SimpleMath::Vector3(10, 2,2);
	m_AdjustmentArrowCollider[0]->Orientation = GetRotate();

	m_AdjustmentArrowCollider[1]->Center = GetPosition() + DirectX::SimpleMath::Vector3(0, 0, -7);
	m_AdjustmentArrowCollider[1]->Extents = DirectX::SimpleMath::Vector3(2, 2, 10);
	m_AdjustmentArrowCollider[1]->Orientation = GetRotate();

	m_AdjustmentArrowCollider[2]->Center = GetPosition() + DirectX::SimpleMath::Vector3(0, 7, 0);
	m_AdjustmentArrowCollider[2]->Extents = DirectX::SimpleMath::Vector3(2, 10, 2);
	m_AdjustmentArrowCollider[2]->Orientation = GetRotate();
}

void AdjustmentArrow::Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& ratate, float size)
{
	m_size = size;
	m_position = position;
	m_rotate = ratate;
	for (int i = 0; i < 3; i++)
	{
		//当たり判定を生成
		m_RotateBoxCol[i]->Center = GetPosition();
	}

	//当たり判定を生成
	m_RotateSphereCol->Center = GetPosition();
	//当たり判定を生成
	m_RotateOll->Center = GetPosition();
	//当たり判定を生成
	m_RotateSphereCol->Radius = 16 * size;
	//当たり判定を生成
	m_RotateOll->Radius = 3 * size;
	//当たり判定を生成
	m_RotateBoxCol[0]->Extents = DirectX::SimpleMath::Vector3(16, 0.6f, 16) * size;
	//当たり判定を生成
	m_RotateBoxCol[1]->Extents = DirectX::SimpleMath::Vector3(16, 16, 0.6f) * size;
	//当たり判定を生成
	m_RotateBoxCol[2]->Extents = DirectX::SimpleMath::Vector3(0.6f, 16, 16) * size;
	m_AdjustmentArrowCollider[0]->Center = GetPosition() + (DirectX::SimpleMath::Vector3(7, 0, 0) * size);

	m_AdjustmentArrowCollider[1]->Center = GetPosition() + (DirectX::SimpleMath::Vector3(0, 0, -7) * size);

	m_AdjustmentArrowCollider[2]->Center = GetPosition() + (DirectX::SimpleMath::Vector3(0, 7, 0) * size);

	m_AdjustmentArrowCollider[0]->Extents = DirectX::SimpleMath::Vector3(9, 2, 2) * size;

	m_AdjustmentArrowCollider[1]->Extents = DirectX::SimpleMath::Vector3(2, 2, 9) * size;

	m_AdjustmentArrowCollider[2]->Extents = DirectX::SimpleMath::Vector3(2, 9, 2) * size;

}

void AdjustmentArrow::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{	
	auto context = m_deviceResources->GetD3DDeviceContext();
	//スケーリング、位置調整、回転をさせる
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(SimpleMath::Vector3(15, 15, 15)* m_size);
	SimpleMath::Matrix pos = SimpleMath::Matrix::CreateTranslation(GetPosition());
	world = scale  * pos;

		//半透明描画指定
	ID3D11BlendState* blendstate = m_states->NonPremultiplied();

	// 透明判定処理
	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);

	for (int i = 0; i < HitOperationModel::NONE_AND_COUNT; i++)
	{
		m_AdjustmentArrowModel[i]->UpdateEffects([&](IEffect* effect) {
			auto basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
				basicEffect->SetEmissiveColor(SimpleMath::Color(0, 0, 0, 0)); // 自己発光の色を設定する
			});

	}
	if (m_PositionHitNum != NONE_AND_COUNT)
		m_AdjustmentArrowModel[m_PositionHitNum]->UpdateEffects([&](IEffect* effect) {
		auto basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
			basicEffect->SetEmissiveColor(SimpleMath::Color(0.4f, 0.4f, 0.4f, 0.4f));
			});

	for (int i = 0; i < HitOperationModel::NONE_AND_COUNT; i++)
		m_AdjustmentArrowModel[i]->Draw(context, *m_states, world, view, proj, false, [&]()
			{
				// 深度ステンシルの設定
				context->OMSetDepthStencilState(m_depthStencilState_Shadow.Get(), 1);
			});

	//m_Cube->UpdateEffects([&](IEffect* effect) {
	//	auto basicEffect = dynamic_cast<BasicEffect*>(effect);
	//	if (basicEffect)
	//		basicEffect->SetEmissiveColor(Colors::Aqua);
	//	});

	//pos = SimpleMath::Matrix::CreateTranslation(m_AdjustmentArrowLeftCollider->Center);
	//scale = SimpleMath::Matrix::CreateScale(m_AdjustmentArrowLeftCollider->Extents);

	//world = scale  * pos;
	//m_Cube->Draw(context, *m_states, world, view, proj, true);
	//pos = SimpleMath::Matrix::CreateTranslation(m_AdjustmentArrowRightCollider->Center);
	//scale = SimpleMath::Matrix::CreateScale(m_AdjustmentArrowRightCollider->Extents);
	//world = scale * pos;

	//m_Cube->Draw(context, *m_states, world, view, proj, true);
	//pos = SimpleMath::Matrix::CreateTranslation(m_AdjustmentArrowUpCollider->Center);
	//scale = SimpleMath::Matrix::CreateScale(m_AdjustmentArrowUpCollider->Extents);
	//world = scale * pos;

	//m_Cube->Draw(context, *m_states, world, view, proj, true);
}

void AdjustmentArrow::RotateRender(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
{
	auto context = m_deviceResources->GetD3DDeviceContext();
	//スケーリング、位置調整、回転をさせる
	SimpleMath::Matrix world = SimpleMath::Matrix::Identity;

	SimpleMath::Matrix scale;
	SimpleMath::Matrix pos;
	scale = SimpleMath::Matrix::CreateScale(SimpleMath::Vector3(15, 15, 15) * m_size);
	pos = SimpleMath::Matrix::CreateTranslation(GetPosition());
	world = scale * pos;

	for (int i = 0; i < HitOperationModel::NONE_AND_COUNT; i++)
	{
		m_rotateModels[i]->UpdateEffects([&](IEffect* effect) {
			auto basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
				basicEffect->SetEmissiveColor(SimpleMath::Color(0, 0, 0, 0)); // 自己発光の色を設定する
			});

	}
	if (m_rotateHitNum != NONE_AND_COUNT)
		m_rotateModels[m_rotateHitNum]->UpdateEffects([&](IEffect* effect) {
		auto basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
			basicEffect->SetEmissiveColor(SimpleMath::Color(0.4f, 0.4f, 0.4f, 0.4f));
			});
	for (int i = 0; i < HitOperationModel::NONE_AND_COUNT; i++)
		m_rotateModels[i]->Draw(context, *m_states, world, view, proj, false, [&]()
			{
				// 深度ステンシルの設定
				context->OMSetDepthStencilState(m_depthStencilState_Shadow.Get(), 1);
			});

	//for (int i = 0; i < 3; i++)
	//{
	//	pos = SimpleMath::Matrix::CreateTranslation(m_RotateBoxCol[i]->Center);
	//	scale = SimpleMath::Matrix::CreateScale(m_RotateBoxCol[i]->Extents);

	//	world = scale * pos;
	//	m_Cube->Draw(context, *m_states, world, view, proj, true);

	//}
}

void AdjustmentArrow::SetpositionRandam(const float& min, const float& max)
{
	std::random_device seed;
	std::default_random_engine engine(seed());
	std::uniform_real_distribution<> distance(min, max);

	float x = static_cast<float>(distance(engine));
	float z = static_cast<float>(distance(engine));

	m_position = SimpleMath::Vector3(x, 4, z);
	m_rotate = SimpleMath::Quaternion::CreateFromAxisAngle(SimpleMath::Vector3::UnitY, x);
}
HitOperationModel AdjustmentArrow::RotateCol(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 dir)
{
	float keepdis = 1000000;
	m_rotateHitNum = NONE_AND_COUNT;
	float dis = 0;

	if (m_RotateOll->Intersects(eye, dir, dis))
	{
		m_rotateHitNum = HitOperationModel::OLL;
		return m_rotateHitNum;
	}

	for (int i = 0; i < 3; i++)
	{
		if (m_RotateSphereCol->Intersects(eye, dir, dis))
			if (m_RotateBoxCol[i]->Intersects(eye, dir, dis))
			{
				if (keepdis > dis)
				{
					m_rotateHitNum = static_cast<HitOperationModel>(i);
					keepdis = dis;
				}

			}
	}
	return m_rotateHitNum;
}

HitOperationModel AdjustmentArrow::PositionCol(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 dir)
{
	float keepdis = 1000000;
	m_PositionHitNum = NONE_AND_COUNT;
	float dis = 0;

	if (m_RotateOll->Intersects(eye, dir, dis))
	{
		m_PositionHitNum = HitOperationModel::OLL;
		return m_PositionHitNum;
	}

	for (int i = 0; i < 3; i++)
	{
		if (m_AdjustmentArrowCollider[i]->Intersects(eye, dir, dis))
		{
			if (keepdis > dis)
			{
				m_PositionHitNum = static_cast<HitOperationModel>(i);
				keepdis = dis;
			}

		}
	}
	return m_PositionHitNum;
}

