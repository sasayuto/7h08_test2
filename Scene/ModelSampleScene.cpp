#include "pch.h"
#include "ModelSampleScene.h"
#include "ReadData.h"
#include <iomanip>
#include <locale>
#include <codecvt>
#include"Scene/GameObjects/Models/Resources.h"
using namespace DirectX;
#include"SystemClass/KeyboardName.h"
// std::wstringをstd::stringに変換する関数
std::string wstring_to_string(const std::wstring& wstr) {
	// ロケールを設定して、std::wstringをstd::stringに変換する
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(wstr);
}
ModelSampleScene::ModelSampleScene() :
	m_spotLightNum(0),
	m_cursor(0),
	m_AdditionPercentageLeft(0),
	m_AdditionPercentageRight(0),
	m_apTimerLeft(0),
	m_apTimerRight(0),
	m_MouseSelectNum(-1)
	,m_yAngle(0.0f), m_yTmp(0.0f), m_xAngle(0.0f), m_xTmp(0.0f), m_keeppos(), m_keepExtents()
	, m_eyeToObjectDistance(), m_keepRotate(), m_ModelNum(),
	m_selectProject(SelectProject::EDIT)

{
	m_JsonName = "Resources/ColliderDate/Save/House_02.json";


	m_ModelName = L"Resources/cmo/House_02_01";
	m_JsonColName = L"01";
	m_copyColliderDate = {};
}

DirectX::SimpleMath::Vector3 CalculateRayDirection(int screenWidth, int screenHeight, const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection, DirectX::SimpleMath::Vector2 mousePos) {
	
	// マウスの位置をスクリーン座標系からNDC座標系に変換
	float mouseX = (2.0f * mousePos.x) / screenWidth - 1.0f;
	float mouseY = 1.0f - (2.0f * mousePos.y) / screenHeight;

	// ビューポート行列の逆行列を計算
	DirectX::SimpleMath::Matrix invViewProjection = (view * projection).Invert();

	// レイの方向を計算 (ワールド座標系で)
	DirectX::SimpleMath::Vector3 rayNDC(mouseX, mouseY, 1.0f);
	DirectX::SimpleMath::Vector4 rayClip4(rayNDC.x, rayNDC.y, 1.0f, 1.0f);
	DirectX::SimpleMath::Vector4 rayWorld4 = DirectX::SimpleMath::Vector4::Transform(rayClip4, invViewProjection);
	DirectX::SimpleMath::Vector3 rayWorld(rayWorld4.x, rayWorld4.y, rayWorld4.z);
	// レイの方向を正規化
	rayWorld.Normalize();

	return rayWorld;
}

DirectX::SimpleMath::Quaternion QuaternionFromRayDirection(const DirectX::SimpleMath::Vector3& rayDirection) {
	// ベクトルを回転クオータニオンに変換

 // DirectX::SimpleMath::Quaternionを使用して方向ベクトルをクォータニオンに変換
	DirectX::SimpleMath::Matrix rotationMatrix = DirectX::SimpleMath::Matrix::CreateWorld(
		DirectX::SimpleMath::Vector3::Zero, rayDirection, DirectX::SimpleMath::Vector3::Up);
	return DirectX::SimpleMath::Quaternion::CreateFromRotationMatrix(rotationMatrix);
}

void ModelSampleScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
	auto debugFont = SingletonDebugFont::GetInstance();

	for (int i = 0; i < 1000; i++)
	{
		auto Col = std::make_unique<DirectX::BoundingOrientedBox>();
		Col->Center = DirectX::SimpleMath::Vector3(0, 0, 0);
		Col->Extents = DirectX::SimpleMath::Vector3(3, 3, 3);
		Col->Orientation = Rotate(-0, 0, 0.0f);

		m_CubeCol.push_back(std::move(Col));
	}


	int pos = static_cast<int>(debugFont->GetFontHeight());
	for (int i = 0; i < 10; i++)
	{
		m_uiCol[i] = std::make_unique<Collider::Box2D>();
		m_uiCol[i]->Initialize(DirectX::SimpleMath::Vector2(150., 110. + static_cast<float>(pos * i)), DirectX::SimpleMath::Vector2(150, pos / 2));
	}

	// デバッグカメラの作成
	RECT rect = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetOutputSize();
	m_debugCamera = std::make_unique<Imase::DebugCamera>(rect.right, rect.bottom);
	auto context = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto mouseTracker = KeyboardTracker::GetInstance()->GetMouseTracker();
	// 画面サイズに対する相対的なスケールに調整
	m_sx = 1.0f / float(rect.right);
	m_sy = 1.0f / float(rect.bottom);

	auto mouseState = mouseTracker.GetLastState();

	m_mouseRayDir = CalculateRayDirection(rect.right, rect.bottom, m_view, m_proj, DirectX::SimpleMath::Vector2(mouseState.x, mouseState.y));

	m_mouseRayDirRotate = QuaternionFromRayDirection(m_mouseRayDir);

	//m_rayLength = 3000;
	//m_RayExtents = DirectX::SimpleMath::Vector3(0.001f, 0.001f, m_rayLength);
	//m_RayPostion = DirectX::SimpleMath::Vector3(m_debugCamera->GetEyePosition()
	//	- DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, 0, m_rayLength), m_mouseRayDirRotate));

}

void ModelSampleScene::Update(float elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	auto mouseTracker = KeyboardTracker::GetInstance()->GetMouseTracker();

	DirectX::SimpleMath::Vector3 selectTarget = DirectX::SimpleMath::Vector3::Zero;
	// デバッグカメラの更新
	if (m_spotLightNum != -1)	selectTarget = m_CubeCol[m_spotLightNum]->Center;
	m_debugCamera->Update(mouseTracker, kbTracker, selectTarget);

	m_view = m_debugCamera->GetCameraMatrix();


	switch (m_selectProject)
	{
	case SelectProject::EDIT:
		EditUpdate(elapsedTime);
		break;
	case SelectProject::FILE:
		FileSaveUpdate(elapsedTime);
		break;
	default:
		break;
	}

}

void ModelSampleScene::EditUpdate(float elapsedTime)
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	auto kb = KeyboardSingleton::GetInstance()->GetKeyboardState();
	auto mouseTracker = KeyboardTracker::GetInstance()->GetMouseTracker();
	auto mouseState = KeyboardSingleton::GetInstance()->GetMouseState();
	auto debugFont = SingletonDebugFont::GetInstance();
	RECT rect = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetOutputSize();

	m_mouseRayDir = CalculateRayDirection(rect.right, rect.bottom, m_view, m_proj, DirectX::SimpleMath::Vector2(mouseState.x, mouseState.y));

	m_mouseRayDirRotate = QuaternionFromRayDirection(-DirectX::SimpleMath::Vector3(m_view._13, m_view._23, m_view._33));

	if (m_spotLightNum != -1)
		m_eyeToObjectDistance = fabs((m_CubeCol[m_spotLightNum]->Center - m_debugCamera->GetEyePosition()).Length());

	//m_RayPostion = DirectX::SimpleMath::Vector3(m_debugCamera->GetEyePosition()
	//	- DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, 0, m_rayLength + 0.5f), m_mouseRayDirRotate));


	// uiセレクト
	const int nnnun = 4;
	for (int i = 0; i < nnnun; i++)
	{
		m_uiColor[i] = Colors::White;
		if (m_uiCol[i]->CheckHitPoint(mouseState.x, mouseState.y))
		{
			m_uiColor[i] = DirectX::SimpleMath::Color(1, 0.7f, 0.5f, 1);
			if (mouseTracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
			{
				m_cursor = i;
				return;
			}
		}
	}

	//レイキャスティングから一番近いオブジェクトを決定
	float keepDistance = 100000;
	m_MouseSelectNum = -1;
	for (int index = 0; index < SPOT_LIGHT_MAX_NUM; index++)
	{
		float dis = 0;
		//ntnの場合があるから

		if (m_CubeCol[index]->Intersects(m_debugCamera->GetEyePosition(), m_mouseRayDir, dis))
		{
			if (dis <= keepDistance)
			{
				keepDistance = dis;
				m_MouseSelectNum = index;
			}
			// 自己発光するようにエフェクトを設定する
		}
	}

	std::wostringstream oss[nnnun];
	oss[m_cursor] << L">";

	if (mouseTracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
	{
		float dis = 0;
		if (m_spotLightNum == -1)
			m_spotLightNum = m_MouseSelectNum;
	}

	UIUpdate();
	//コピー
	if (kb.LeftControl)
		if (kbTracker.pressed.C)
		{
			//コピー可能か
			if (m_spotLightNum != -1)
			{
				m_copyColliderDate.Position = m_CubeCol[m_spotLightNum]->Center;
				m_copyColliderDate.Rotate = m_CubeCol[m_spotLightNum]->Orientation;
				m_copyColliderDate.Extents = m_CubeCol[m_spotLightNum]->Extents;
				m_copyColliderDate.CopyFlag = true;
			}
			else
				m_copyColliderDate.CopyFlag = false;
		}

	if (kb.LeftControl)
		if (kbTracker.pressed.V)
		{
			//コピーがあるか
			if (m_copyColliderDate.CopyFlag)
			{
				SPOT_LIGHT_MAX_NUM += 1;
				m_spotLightNum = SPOT_LIGHT_MAX_NUM - 1;

				m_CubeCol[m_spotLightNum]->Center = m_copyColliderDate.Position;
				m_CubeCol[m_spotLightNum]->Extents = m_copyColliderDate.Extents;
				m_CubeCol[m_spotLightNum]->Orientation = m_copyColliderDate.Rotate;

				if (SPOT_LIGHT_MAX_NUM > 1000) SPOT_LIGHT_MAX_NUM = 1000;
			}
		}

	if (m_spotLightNum != -1)
	{

		m_AdjustmentArrow->Update(m_CubeCol[m_spotLightNum]->Center, m_CubeCol[m_spotLightNum]->Orientation, m_eyeToObjectDistance * 0.007f);

		oss[1] << L" Pos" << L" : " << std::fixed << std::setprecision(2) << m_CubeCol[m_spotLightNum]->Center.x << L"," << m_CubeCol[m_spotLightNum]->Center.y << L"," << m_CubeCol[m_spotLightNum]->Center.z;
		debugFont->AddString(oss[1].str().c_str(), SimpleMath::Vector2(0, debugFont->GetFontHeight() * (1 + 3)), m_uiColor[1]);
		oss[2] << L" Ext" << L" : " << std::fixed << std::setprecision(2) << m_CubeCol[m_spotLightNum]->Extents.x << L"," << m_CubeCol[m_spotLightNum]->Extents.y << L"," << m_CubeCol[m_spotLightNum]->Extents.z;;
		debugFont->AddString(oss[2].str().c_str(), SimpleMath::Vector2(0, debugFont->GetFontHeight() * (2 + 3)), m_uiColor[2]);

		// クオータニオンからオイラー角を取得
		DirectX::SimpleMath::Quaternion rotate = m_CubeCol[m_spotLightNum]->Orientation;
		DirectX::SimpleMath::Vector3 euler = rotate.ToEuler()/3.1415926f*180.0f;
		oss[3] << L" Rot" << L" : " << std::fixed << std::setprecision(2) << euler.x << L"," << euler.y << L"," << euler.z;;
		debugFont->AddString(oss[3].str().c_str(), SimpleMath::Vector2(0, debugFont->GetFontHeight() * (3 + 3)), m_uiColor[3]);

		if (kbTracker.pressed.Delete)
		{
			if (m_spotLightNum < m_CubeCol.size()) {
				m_CubeCol[m_spotLightNum].reset(); // ユニークポインタをリセットして、メモリを解放する
				m_CubeCol.erase(m_CubeCol.begin() + m_spotLightNum); // リセットした後に、要素をvectorから削除する
				m_spotLightNum = -1;
				SPOT_LIGHT_MAX_NUM--;
			}
		}
	}
	oss[0] << L" SPOT_LIGHT_MAX_NUM" << L" : " << std::fixed << std::setprecision(2) << SPOT_LIGHT_MAX_NUM;
	debugFont->AddString(oss[0].str().c_str(), SimpleMath::Vector2(0, debugFont->GetFontHeight() * (0 + 3)), m_uiColor[0]);

	if (kb.LeftControl)
	{
		if (kbTracker.pressed.S)
		{
			m_selectProject = SelectProject::FILE;
			m_cursor = 100;
		}
	}

}

void ModelSampleScene::FileSaveUpdate(float elapsedTime)
{	
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	auto kb = KeyboardSingleton::GetInstance()->GetKeyboardState();
	auto debugFont = SingletonDebugFont::GetInstance();
	auto mouseTracker = KeyboardTracker::GetInstance()->GetMouseTracker();
	auto mouseState = KeyboardSingleton::GetInstance()->GetMouseState();
	auto device = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();

	if (kb.LeftControl)
	{
		if (kbTracker.pressed.S)
			SaveGunData();
	}
	// uiセレクト
	const int nnnun = 3;
	for (int i = 0; i < nnnun; i++)
	{
		m_uiColor[i] = Colors::White;
		if (mouseTracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
			m_cursor = 100;

		if (m_uiCol[i]->CheckHitPoint(mouseState.x, mouseState.y))
		{
			m_uiColor[i] = DirectX::SimpleMath::Color(1, 0.7f, 0.5f, 1);
			if (mouseTracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
			{
				m_cursor = i;
				break;
			}
		}
	}

	std::wostringstream oss[101];
	oss[m_cursor] << L">";
	if (m_cursor == 0)
		KeyboardName::GetInstance()->SetName(m_JsonColName);
	if (m_cursor == 1)
		KeyboardName::GetInstance()->SetName(m_JsonName);

	if (m_cursor == 2)
		KeyboardName::GetInstance()->SetName(m_ModelName);

	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	std::wstring wide = converter.from_bytes(m_JsonName);

	oss[0] << L" m_J_C_N" << L" : " << m_JsonColName;
	debugFont->AddString(oss[0].str().c_str(), SimpleMath::Vector2(0, debugFont->GetFontHeight() * (0 + 3)), m_uiColor[0]);

	oss[1] << L" m_PasName" << L" : " << wide;
	debugFont->AddString(oss[1].str().c_str(), SimpleMath::Vector2(1, debugFont->GetFontHeight() * (1 + 3)), m_uiColor[1]);
	oss[2] << L" m_ModelName" << L" : " << m_ModelName;
	debugFont->AddString(oss[2].str().c_str(), SimpleMath::Vector2(1, debugFont->GetFontHeight() * (2 + 3)), m_uiColor[2]);

	if (kbTracker.pressed.Tab)
	{
		m_selectProject = SelectProject::EDIT;
		m_cursor = 0;
	}
	if (kbTracker.pressed.Enter)
	{
		EffectFactory fx(device);
		fx.SetDirectory(L"Resources/cmo");

		std::wstring replacedString = m_ModelName;
		replacedString += L".cmo";
		std::unique_ptr<DirectX::Model> createModel;
		try {
			// モデルの作成
			createModel = Model::CreateFromCMO(device, replacedString.c_str(), fx);
		}
		catch (const std::exception& e) {
			// モデルの作成
			createModel = std::move(m_torusMel);
		}
		m_torusMel = std::move(createModel);

	}


}

void ModelSampleScene::Render()
{
	auto debugFont = SingletonDebugFont::GetInstance();
	debugFont->AddString(L"ModelSampleScene", SimpleMath::Vector2(0.0f, debugFont->GetFontHeight()));
	auto context = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = GetUserResources()->GetCommonStates();

	// ------------------------------------------------ //
	// 影になるモデルを描画する
	// ------------------------------------------------ //
	SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	world = SimpleMath::Matrix::CreateTranslation(-DirectX::SimpleMath::Vector3(m_torusMel->meshes[0]->boundingBox.Center.x, m_torusMel->meshes[0]->boundingBox.Extents.y, m_torusMel->meshes[0]->boundingBox.Center.z));
	m_floorModel->Draw(context, *states, world, m_view, m_proj, false);
	world = SimpleMath::Matrix::CreateTranslation(-DirectX::SimpleMath::Vector3(m_torusMel->meshes[0]->boundingBox.Center));
	m_torusMel->Draw(context, *states, world, m_view, m_proj, false, [&]()
		{
			context->RSSetState(states->CullNone());

		}
	);
	

	for (int index = 0; index < SPOT_LIGHT_MAX_NUM; index++)
	{
		if (m_MouseSelectNum == index)
			m_spotLightModel->UpdateEffects([&](IEffect* effect) {
			auto basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
				basicEffect->SetEmissiveColor(Colors::OrangeRed);
				});
		else
			m_spotLightModel->UpdateEffects([&](IEffect* effect)
				{
					auto basicEffect = dynamic_cast<BasicEffect*>(effect);
					if (basicEffect)
						basicEffect->SetEmissiveColor(Colors::Black);
				});
		if (m_spotLightNum == index)
			m_spotLightModel->UpdateEffects([&](IEffect* effect)
				{
					auto basicEffect = dynamic_cast<BasicEffect*>(effect);
					if (basicEffect)
						basicEffect->SetEmissiveColor(Colors::Aqua);
				});

		DirectX::SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(m_CubeCol[index]->Extents);
		world = scale *
			SimpleMath::Matrix::CreateFromQuaternion(m_CubeCol[index]->Orientation) *
			SimpleMath::Matrix::CreateTranslation(m_CubeCol[index]->Center);

		// スポットライトの描画
		m_spotLightModel->Draw(context, *states, world, m_view, m_proj, true);
	}


	DirectX::SimpleMath::Matrix scale = SimpleMath::Matrix::CreateScale(m_RayExtents);
	world = scale * SimpleMath::Matrix::CreateFromQuaternion(m_mouseRayDirRotate) * SimpleMath::Matrix::CreateTranslation(m_RayPostion);

	// スポットライトの描画
	m_spotLightModel->Draw(context, *states, world, m_view, m_proj, false, [&]()
		{
			context->RSSetState(states->CullNone());

		}
	);
	if (m_cursor == 1)
	{
		if (m_spotLightNum != -1)
			m_AdjustmentArrow->Render(m_view, m_proj);
	}
	if (m_cursor == 2)
	{
		if (m_spotLightNum != -1)
			m_AdjustmentArrow->Render(m_view, m_proj);
	}
	if (m_cursor == 3)
	{
		if (m_spotLightNum != -1)
			m_AdjustmentArrow->RotateRender(m_view, m_proj);
	}
}
void ModelSampleScene::Finalize()
{
	//m_gridFloor.reset();
	m_floorModel.reset();
}
void ModelSampleScene::CreateDeviceDependentResources()
{
	auto device = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	auto context = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	// エフェクトファクトリーの作成
	EffectFactory fx(device);
	fx.SetDirectory(L"Resources/cmo");
	// 床のモデルの作成

	std::wstring replacedString = m_ModelName;
	replacedString += L".cmo";

	m_floorModel = Model::CreateFromCMO(device, L"Resources/cmo/MinStoneFloor.cmo", fx);
	m_torusMel = Model::CreateFromCMO(device, replacedString.c_str(), fx);

	m_spotLightModel = Model::CreateFromCMO(device, L"CMO/Cube.cmo", fx);

	// 自己発光するようにエフェクトを設定する
	m_spotLightModel->UpdateEffects([&](IEffect* effect)
		{
			auto basicEffect = dynamic_cast<BasicEffect*>(effect);
			if (basicEffect)
			{
				basicEffect->SetEmissiveColor(Colors::White);
			}
		}
	);

	m_AdjustmentArrow = std::make_unique<AdjustmentArrow>(SingletonDeviceResources::GetInstance()->GetDeviceResources(),GetUserResources()->GetCommonStates());
	m_AdjustmentArrow->Initialize();
}
void ModelSampleScene::CreateWindowSizeDependentResources()
{
	// 射影行列を作成
	RECT rect = SingletonDeviceResources::GetInstance()->GetDeviceResources()->GetOutputSize();
	m_proj = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 2000000.0f
	);
}
void ModelSampleScene::OnDeviceLost()
{
	Finalize();
}

DirectX::SimpleMath::Quaternion ModelSampleScene::Rotate(float x, float y, float z)
{
	return SimpleMath::Quaternion::CreateFromYawPitchRoll(
		XMConvertToRadians(x), XMConvertToRadians(y), XMConvertToRadians(z));
}

void ModelSampleScene::UIUpdate()
{
	auto kbTracker = KeyboardTracker::GetInstance()->GetKeyboardTracker();
	auto kb = KeyboardSingleton::GetInstance()->GetKeyboardState();
	auto mouseTracker = KeyboardTracker::GetInstance()->GetMouseTracker();
	auto mouseState = KeyboardSingleton::GetInstance()->GetMouseState();

	if (m_cursor == 0)
	{
		if (mouseTracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
			m_spotLightNum = m_MouseSelectNum;

		if (kbTracker.pressed.Left)
		{
			SPOT_LIGHT_MAX_NUM -= 1;

			if (m_spotLightNum >= SPOT_LIGHT_MAX_NUM)
				m_spotLightNum--;

			if (SPOT_LIGHT_MAX_NUM <= 0) SPOT_LIGHT_MAX_NUM = 0, m_spotLightNum = -1;

			//最大化時より後が選ばれてたら下げる
		}
		if (kbTracker.pressed.Right)
		{
			SPOT_LIGHT_MAX_NUM += 1;
			m_spotLightNum = SPOT_LIGHT_MAX_NUM - 1;
			if (SPOT_LIGHT_MAX_NUM > 1000) SPOT_LIGHT_MAX_NUM = 1000;
		}
	}

	if (m_cursor == 1)
	{
		if (m_spotLightNum == -1)
			return;
		if (mouseTracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
		{
			float dis = 0;
			//ntnの場合があるから
			m_AdjustmentArrow->SetPositionHitNum(m_AdjustmentArrow->PositionCol(m_debugCamera->GetEyePosition(), m_mouseRayDir));
			if (m_AdjustmentArrow->GetPositionHitNum() == HitOperationModel::NONE_AND_COUNT)
				m_spotLightNum = m_MouseSelectNum;

			if (m_spotLightNum == -1)
				return;

			if (m_spotLightNum != -1)
			{
				m_keeppos = m_CubeCol[m_spotLightNum]->Center;
				m_keepExtents = m_CubeCol[m_spotLightNum]->Extents;
			}
			m_y = mouseState.y;
			m_x = mouseState.x;

		}
		if (mouseTracker.leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			m_AdjustmentArrow->SetPositionHitNum(HitOperationModel::NONE_AND_COUNT);
		}

		float distance = fabs((m_CubeCol[m_spotLightNum]->Center - m_debugCamera->GetEyePosition()).Length());

		float x = m_x - mouseState.x;
		float y = m_y - mouseState.y;

		DirectX::SimpleMath::Vector3 UnitX = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitX, m_mouseRayDirRotate);
		DirectX::SimpleMath::Vector3 UnitY = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitY, m_mouseRayDirRotate);
		DirectX::SimpleMath::Vector3 UnitZ = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ, m_mouseRayDirRotate);
		float posX = UnitX.Dot(DirectX::SimpleMath::Vector3::UnitX) * x - UnitY.Dot(DirectX::SimpleMath::Vector3::UnitX) * y;
		float posY = UnitY.Dot(DirectX::SimpleMath::Vector3::UnitY) * y;
		float posZ = UnitX.Dot(DirectX::SimpleMath::Vector3::UnitZ) * x - UnitY.Dot(DirectX::SimpleMath::Vector3::UnitZ) * y;

		if (m_AdjustmentArrow->GetPositionHitNum() == HitOperationModel::X)
			m_CubeCol[m_spotLightNum]->Center.x = m_keeppos.x - ((posX)*distance * 0.001f);
		if (m_AdjustmentArrow->GetPositionHitNum() == HitOperationModel::Y)
			m_CubeCol[m_spotLightNum]->Center.z = m_keeppos.z - ((posZ)*distance * 0.001f);
		if (m_AdjustmentArrow->GetPositionHitNum() == HitOperationModel::Z)
			m_CubeCol[m_spotLightNum]->Center.y = m_keeppos.y + ((posY)*distance * 0.001f);
		if (m_AdjustmentArrow->GetPositionHitNum() == HitOperationModel::OLL)
		{
			m_CubeCol[m_spotLightNum]->Center.x = m_keeppos.x - ((posX)*distance * 0.001f);
			m_CubeCol[m_spotLightNum]->Center.z = m_keeppos.z - ((posZ)*distance * 0.001f);
			m_CubeCol[m_spotLightNum]->Center.y = m_keeppos.y + ((posY)*distance * 0.001f);

		}
	}
	if (m_cursor == 2)
	{
		if (m_spotLightNum == -1)
			return;
		if (mouseTracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
		{
			float dis = 0;
			//ntnの場合があるから
			m_AdjustmentArrow->SetPositionHitNum(m_AdjustmentArrow->PositionCol(m_debugCamera->GetEyePosition(), m_mouseRayDir));
			if (m_AdjustmentArrow->GetPositionHitNum() == HitOperationModel::NONE_AND_COUNT)
				m_spotLightNum = m_MouseSelectNum;

			if (m_spotLightNum == -1)
				return;

			m_keeppos = m_CubeCol[m_spotLightNum]->Center;
			m_keepExtents = m_CubeCol[m_spotLightNum]->Extents;
			m_y = mouseState.y;
			m_x = mouseState.x;
		}
		if (mouseTracker.leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			m_AdjustmentArrow->SetPositionHitNum(HitOperationModel::NONE_AND_COUNT);
		}

		float x = static_cast<float>(m_x) - mouseState.x;
		float y = static_cast<float>(m_y) - mouseState.y;

		DirectX::SimpleMath::Vector3 UnitX = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitX, m_mouseRayDirRotate);
		DirectX::SimpleMath::Vector3 UnitY = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitY, m_mouseRayDirRotate);
		DirectX::SimpleMath::Vector3 UnitZ = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ, m_mouseRayDirRotate);
		float posX = UnitX.Dot(DirectX::SimpleMath::Vector3::UnitX) * x - UnitY.Dot(DirectX::SimpleMath::Vector3::UnitX) * y;
		float posY = UnitY.Dot(DirectX::SimpleMath::Vector3::UnitY) * y;
		float posZ = UnitX.Dot(DirectX::SimpleMath::Vector3::UnitZ) * x - UnitY.Dot(DirectX::SimpleMath::Vector3::UnitZ) * y;

		if (m_AdjustmentArrow->GetPositionHitNum() == HitOperationModel::X)
			m_CubeCol[m_spotLightNum]->Extents.x = m_keepExtents.x - ((posX)*m_eyeToObjectDistance * 0.002f);
		if (m_AdjustmentArrow->GetPositionHitNum() == HitOperationModel::Y)
			m_CubeCol[m_spotLightNum]->Extents.z = m_keepExtents.z + ((posZ)*m_eyeToObjectDistance * 0.002f);
		if (m_AdjustmentArrow->GetPositionHitNum() == HitOperationModel::Z)
			m_CubeCol[m_spotLightNum]->Extents.y = m_keepExtents.y + ((posY)*m_eyeToObjectDistance * 0.002f);
		if (m_AdjustmentArrow->GetPositionHitNum() == HitOperationModel::OLL)
		{
			m_CubeCol[m_spotLightNum]->Extents.x = m_keepExtents.x - ((posX)*m_eyeToObjectDistance * 0.002f);
			m_CubeCol[m_spotLightNum]->Extents.z = m_keepExtents.z + ((posZ)*m_eyeToObjectDistance * 0.002f);
			m_CubeCol[m_spotLightNum]->Extents.y = m_keepExtents.y + ((posY)*m_eyeToObjectDistance * 0.002f);

		}

	}
	if (m_cursor == 3)
	{
		if (m_spotLightNum == -1)
			return;

		if (kbTracker.pressed.Space)
		{
			m_keepRotate = DirectX::SimpleMath::Quaternion::Identity;
			m_CubeCol[m_spotLightNum]->Orientation = DirectX::SimpleMath::Quaternion::Identity;
		}
		if (mouseTracker.leftButton == Mouse::ButtonStateTracker::PRESSED)
		{
			float dis = 0;
			//ntnの場合があるから
			m_AdjustmentArrow->SetRotateHitNum(m_AdjustmentArrow->RotateCol(m_debugCamera->GetEyePosition(), m_mouseRayDir));
			if (m_AdjustmentArrow->GetRotateHitNum() == HitOperationModel::NONE_AND_COUNT)
				m_spotLightNum = m_MouseSelectNum;

			if (m_spotLightNum == -1)
				return;

			m_keeppos = m_CubeCol[m_spotLightNum]->Center;
			m_keepExtents = m_CubeCol[m_spotLightNum]->Extents;
			m_keepRotate = m_CubeCol[m_spotLightNum]->Orientation;
			m_y = mouseState.y;
			m_x = mouseState.x;

		}
		if (mouseTracker.leftButton == Mouse::ButtonStateTracker::RELEASED)
		{
			m_AdjustmentArrow->SetRotateHitNum(HitOperationModel::NONE_AND_COUNT);
		}

		float x = static_cast<float>(m_x) - mouseState.x;
		float y = static_cast<float>(m_y) - mouseState.y;

		float posX = 0;
		float posY = 0;
		float posZ = 0;

		if (m_AdjustmentArrow->GetRotateHitNum() == HitOperationModel::X)
			posX = -x* 0.004f;
		if (m_AdjustmentArrow->GetRotateHitNum() == HitOperationModel::Y)
			posY = y* 0.004f;
		if (m_AdjustmentArrow->GetRotateHitNum() == HitOperationModel::Z)
			posZ = -y * 0.004f;
		if (m_AdjustmentArrow->GetRotateHitNum() == HitOperationModel::OLL)
		{
			DirectX::SimpleMath::Vector3 UnitY = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitY, m_mouseRayDirRotate);
			DirectX::SimpleMath::Vector3 UnitZ = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ, m_mouseRayDirRotate);
			DirectX::SimpleMath::Vector2 unitx2 = DirectX::SimpleMath::Vector2(UnitY.x, UnitY.z);
			unitx2.Normalize();
			DirectX::SimpleMath::Vector2 unitz2 = DirectX::SimpleMath::Vector2(UnitZ.x, UnitZ.z);
			unitz2.Normalize();
			posY = -unitx2.Dot(DirectX::SimpleMath::Vector2(0, 1)) * x + unitz2.Dot(DirectX::SimpleMath::Vector2(1, 0)) * y;
			posZ = -unitz2.Dot(DirectX::SimpleMath::Vector2(0,1)) * y -unitx2.Dot(DirectX::SimpleMath::Vector2(1, 0)) * x;
			posY*=0.008f;
			posZ*=0.008f;

		}
		SimpleMath::Quaternion q = SimpleMath::Quaternion::CreateFromYawPitchRoll(posX, posZ, posY);

		if (m_AdjustmentArrow->GetRotateHitNum() != HitOperationModel::NONE_AND_COUNT)
			m_CubeCol[m_spotLightNum]->Orientation = m_keepRotate * q;
	}
}

void ModelSampleScene::CollJson()
{
	// 当たり判定を確認したいときに使えるよ
// std::wstring
	std::wstring wide_str = L"Hello, こんにちは";

	// Convert to std::string
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::string narrow_str = "Resources/ColliderDate/"+ converter.to_bytes(m_ModelName) + ".txt";

	std::ofstream outputfile(narrow_str);

	//当たり判定を作る
	std::ostringstream oss;
	for (int i = 0; i < SPOT_LIGHT_MAX_NUM; i++)
	{
		oss << "GetCollider()->AddCollider(Collider::MultipleHitDeterminationFactory::CreateOBBCollider(" << std::endl;
		oss << "GetPosition()," << std::endl << "GetRotate()," << std::endl << "DirectX::SimpleMath::Vector3(" << m_CubeCol[i]->Center.x;
		if (m_CubeCol[i]->Center.x == static_cast<int>(m_CubeCol[i]->Center.x)) oss << ".0";
		oss << "f, " << m_CubeCol[i]->Center.y;
		if (m_CubeCol[i]->Center.y == static_cast<int>(m_CubeCol[i]->Center.y)) oss << ".0";
		oss << "f, " << m_CubeCol[i]->Center.z;
		if (m_CubeCol[i]->Center.z == static_cast<int>(m_CubeCol[i]->Center.z)) oss << ".0";
		oss << "f), " << std::endl;
		oss << "DirectX::SimpleMath::Quaternion(" << m_CubeCol[i]->Orientation.x;
		if (m_CubeCol[i]->Orientation.x == static_cast<int>(m_CubeCol[i]->Orientation.x)) oss << ".0";
		oss << "f," << m_CubeCol[i]->Orientation.y;
		if (m_CubeCol[i]->Orientation.y == static_cast<int>(m_CubeCol[i]->Orientation.y)) oss << ".0";
		oss << "f," << m_CubeCol[i]->Orientation.z;
		if (m_CubeCol[i]->Orientation.z == static_cast<int>(m_CubeCol[i]->Orientation.z)) oss << ".0";
		oss << "f," << m_CubeCol[i]->Orientation.w;
		if (m_CubeCol[i]->Orientation.w == static_cast<int>(m_CubeCol[i]->Orientation.w)) oss << ".0";
		oss << "f)," << std::endl << "DirectX::SimpleMath::Vector3(" << m_CubeCol[i]->Extents.x;

		if (m_CubeCol[i]->Extents.x == static_cast<int>(m_CubeCol[i]->Extents.x)) oss << ".0";
		oss << "f," << m_CubeCol[i]->Extents.y;
		if (m_CubeCol[i]->Extents.y == static_cast<int>(m_CubeCol[i]->Extents.y)) oss << ".0";
		oss << "f," << m_CubeCol[i]->Extents.z;
		if (m_CubeCol[i]->Extents.z == static_cast<int>(m_CubeCol[i]->Extents.z)) oss << ".0";
		oss << "f)));" << std::endl;
	}
	outputfile << oss.str() << std::endl << std::endl;
	outputfile.close(); // ファイルを閉じる

}//ゲームの更新を行う関数
void ModelSampleScene::SaveGunData()
{

	// JSONファイルのパス
	std::string filePath = m_JsonName;

	// 既存のJSONファイルを読み込む
	std::ifstream inputFile(filePath);
	Json::Value root;

	if (inputFile.is_open()) {
		Json::CharReaderBuilder readerBuilder;
		Json::parseFromStream(readerBuilder, inputFile, &root, nullptr);
		inputFile.close();
	}

	Json::Value& colliderDateArray = root["ColliderDate"];

	Json::Value& house0301Array = colliderDateArray[0][wstring_to_string(m_JsonColName)][0]["Obb"];
	{
		// SPOT_LIGHT_MAX_NUM より大きいインデックスの要素を削除
		while (house0301Array.size() > SPOT_LIGHT_MAX_NUM) {
			house0301Array.removeIndex(SPOT_LIGHT_MAX_NUM, nullptr);
		}

		for (int i = 0; i < SPOT_LIGHT_MAX_NUM; i++)
		{
			// 最初の要素の "position" と "rotate" を変更
			house0301Array[i]["position"][0] = m_CubeCol[i]->Center.x;
			house0301Array[i]["position"][1] = m_CubeCol[i]->Center.y;
			house0301Array[i]["position"][2] = m_CubeCol[i]->Center.z;
			house0301Array[i]["rotate"][0] = m_CubeCol[i]->Orientation.x;
			house0301Array[i]["rotate"][1] = m_CubeCol[i]->Orientation.y;
			house0301Array[i]["rotate"][2] = m_CubeCol[i]->Orientation.z;
			house0301Array[i]["rotate"][3] = m_CubeCol[i]->Orientation.w;
			house0301Array[i]["extents"][0] = m_CubeCol[i]->Extents.x;
			house0301Array[i]["extents"][1] = m_CubeCol[i]->Extents.y;
			house0301Array[i]["extents"][2] = m_CubeCol[i]->Extents.z;
		}
	}

	

	// JSONデータを文字列に変換
	Json::StreamWriterBuilder writer;
	std::string jsonString = Json::writeString(writer, root);

	// JSONデータをファイルに書き出し
	std::ofstream outputFile(filePath);
	if (!outputFile.is_open()) {
		std::cerr << "Failed to open output file." << std::endl;
		return;
	}

	outputFile << jsonString;
	outputFile.close();
}