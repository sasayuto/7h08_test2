#pragma once
#include <DirectXCollision.h>

#include "DeviceResources.h"

enum HitOperationModel
{
	X,
	Y,
	Z,
	OLL,
	NONE_AND_COUNT,
};
/// <summary>
/// オブジェクトのクラスを定義する
/// </summary>
class AdjustmentArrow
{
	
public:
	//位置のセッター、ゲッター
	DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	//位置のセッター、ゲッター
	void SetRotateJson(const DirectX::SimpleMath::Vector3& rotate) {
		m_rotate = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
			DirectX::XMConvertToRadians(rotate.x),
			DirectX::XMConvertToRadians(rotate.y),
			DirectX::XMConvertToRadians(rotate.z)
		);
	}

	//回転クオータニオンのゲッターセッター
	DirectX::SimpleMath::Quaternion GetRotate() const { return m_rotate; }
	void SetRotate(const DirectX::SimpleMath::Quaternion& rotate) { m_rotate = rotate; }

	//回転クオータニオンのゲッターセッター
	bool GetArrowRightTouchFlag() const { return m_ArrowRightTouchFlag; }
	void SetArrowRightTouchFlag(const bool& editorSelectFlag) { m_ArrowRightTouchFlag = editorSelectFlag; }

	//回転クオータニオンのゲッターセッター
	bool GetArrowLeftTouchFlag() const { return m_ArrowLeftTouchFlag; }
	void SetArrowLeftTouchFlag(const bool& editorSelectFlag) { m_ArrowLeftTouchFlag = editorSelectFlag; }

	//回転クオータニオンのゲッターセッター
	bool GetArrowUpTouchFlag() const { return m_ArrowUpTouchFlag; }
	void SetArrowUpTouchFlag(const bool& editorSelectFlag) { m_ArrowUpTouchFlag = editorSelectFlag; }


	void SetRotateHitNum(HitOperationModel rotateHitNum) { m_rotateHitNum = rotateHitNum; }
	HitOperationModel GetRotateHitNum() { return m_rotateHitNum; }
	HitOperationModel RotateCol(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 dir);

	void SetPositionHitNum(HitOperationModel rotateHitNum) { m_PositionHitNum = rotateHitNum; }
	HitOperationModel GetPositionHitNum() { return m_PositionHitNum; }
	HitOperationModel PositionCol(DirectX::SimpleMath::Vector3 eye, DirectX::SimpleMath::Vector3 dir);
private:
	//位置
	DirectX::SimpleMath::Vector3 m_position;
	//回転クオータニオン
	DirectX::SimpleMath::Quaternion m_rotate;
	
	// 共通ステート
	DirectX::CommonStates* m_states;

	//モデルのポインタ
	std::unique_ptr < DirectX::Model> m_AdjustmentArrowModel[NONE_AND_COUNT];

	//モデルのポインタ
	std::unique_ptr < DirectX::Model> m_Cube;

	//モデルのポインタ
	std::unique_ptr < DirectX::Model> m_rotateModel;

	//モデルのポインタ
	std::unique_ptr < DirectX::Model> m_rotateModels[NONE_AND_COUNT];

	// 深度ステンシルステート（影）
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState_Shadow;

	//当たり判定のポインタ
	std::unique_ptr<DirectX::BoundingOrientedBox> m_AdjustmentArrowCollider[3];

	//当たり判定のポインタ
	std::unique_ptr<DirectX::BoundingOrientedBox> m_RotateBoxCol[3];
	std::unique_ptr<DirectX::BoundingSphere> m_RotateSphereCol;
	std::unique_ptr<DirectX::BoundingSphere> m_RotateOll;

	bool m_ArrowRightTouchFlag;
	bool m_ArrowLeftTouchFlag;
	bool m_ArrowUpTouchFlag;
	HitOperationModel m_rotateHitNum;
	HitOperationModel m_PositionHitNum;
	DX::DeviceResources* m_deviceResources;

	float m_size;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	AdjustmentArrow(DX::DeviceResources* deviceResources, DirectX::CommonStates* states);

	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~AdjustmentArrow();

	/// <summary>
	/// 初期化する
	/// </summary>
	virtual void Initialize();

	/// <summary>
	/// 更新する
	/// </summary>
	virtual void Update(const DirectX::SimpleMath::Vector3& position,const DirectX::SimpleMath::Quaternion& ratate,float size);

	/// <summary>
	/// 描画する
	/// </summary>
	virtual void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	/// <summary>
	/// 描画する
	/// </summary>
	virtual void RotateRender(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj);

	/// <summary>
	/// 敵をランダムに生成
	/// </summary>
	/// <param name="min">最小</param>
	/// <param name="max">最大</param>
	void SetpositionRandam(const float& min, const float& max);

};
