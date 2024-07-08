#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Collision.h"

/// <summary>
/// 当たり判定のクラスを定義する
/// </summary>
namespace Collider
{
	// OLLクラスの前方宣言
	class OLL;

	/// <summary>
	/// 複数の当たり判定のコライダー
	/// </summary>
	class MultipleHitDetermination
	{
	public:
		//コライダーを作る（これを初期化の時に呼び出す。ファクトリーであるよ）
		void AddCollider(std::unique_ptr<OLL> collider) { m_collider.push_back(std::move(collider)); }

		/// <summary>
		/// 全てのコライダーのアップデート
		/// </summary>
		/// <param name="position">位置</param>
		/// <param name="rotate">回転</param>
		void AllUpdate(
			const DirectX::SimpleMath::Vector3& position,
			const DirectX::SimpleMath::Quaternion& rotate
		);

		//------------------------------------------------------------------
		//１つ以上コライダーが当たったか
		//------------------------------------------------------------------
		/// <summary>
		/// １つ以上コライダーが当たったか
		/// </summary>
		/// <param name="box">四角のアドレス</param>
		/// <returns>Hitでtrue</returns>
		bool CheckHitOneOrMore(Box* box);
		/// <param name="box">OBBのアドレス</param>
		bool CheckHitOneOrMore(OBB* box);
		/// <param name="box">球のアドレス</param>
		bool CheckHitOneOrMore(Sphere* box);
		/// <param name="box">複数のコライダーのアドレス</param>
		bool CheckHitOneOrMore(MultipleHitDetermination* oll);


		//------------------------------------------------------------------
		// 全てのコライダーが当たったか
		//------------------------------------------------------------------
		/// <summary>
		/// 全てのコライダーが当たったか
		/// </summary>
		/// <param name="box">四角のアドレス</param>
		/// <returns>Hitでtrue</returns>
		bool CheckAllHit(Box* box);
		/// <param name="box">OBBのアドレス</param>
		bool CheckAllHit(OBB* box);
		/// <param name="box">球のアドレス</param>
		bool CheckAllHit(Sphere* box);
		/// <param name="box">複数のコライダーのアドレス</param>
		bool CheckAllHit(MultipleHitDetermination* oll);


		//------------------------------------------------------------------
		// 特殊
		//------------------------------------------------------------------
		/// <summary>
		/// 自分の全てのコライダーが当たったかと相手のコライダーが１つでもあたってたら
		/// </summary>
		/// <param name="oll"></param>
		/// <returns></returns>
		bool AllHitAndOneOrMore(MultipleHitDetermination* oll);

		/// <summary>
		/// 相手の全てのコライダーが当たったかと自分のコライダーが１つでもあたってたら
		/// </summary>
		/// <param name="oll"></param>
		/// <returns></returns>
		bool OneOrMoreAndAllHit(MultipleHitDetermination* oll);

		/// <summary>
		/// obbと複数のコライダーの当たり判定から反射ベクトルを求める
		/// </summary>
		/// <param name="obb">obbのコライダー</param>
		/// <returns>反射ベクトル</returns>
		DirectX::SimpleMath::Vector3 CheckHitreflectionVector(OBB* obb,const DirectX::SimpleMath::Vector3& move);
	
	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		MultipleHitDetermination():m_collider(){}

		/// <summary>
		/// デストラクタ
		/// </summary>
		~MultipleHitDetermination() {};

		/// <summary>
		/// 当たり判定の描画
		/// </summary>
		/// <param name="rotate">意味はない（消せめんどい）</param>
		void Render(const DirectX::SimpleMath::Quaternion& rotate);

	private:
		//OLLコライダーの配列
		std::vector<std::unique_ptr<OLL>> m_collider;
	};
	enum class ColliderKinds { BOX, SPHERE, OBBCol, COUNT };			//コライダーの種類

	/// <summary>
	/// 複数の判定のクラスを使う時のクラス（見なくても良い）
	/// </summary>
	class OLL
	{
	public:

		DirectX::SimpleMath::Vector3 GetExtents() const { return m_extents; };
		DirectX::SimpleMath::Vector3 GetPosition()const { return m_position; };             // 位置を取得
		DirectX::SimpleMath::Quaternion GetRotate()const { return m_rotate; };             // 位置を取得

		float GetRadius() const { return m_radius; }		//半径のセッター

		ColliderKinds GetNowColl()const { return m_Collder; }

	public:
		OLL();
		~OLL();
		void OBBInitialize(
			const DirectX::SimpleMath::Vector3& ModelPosition,
			const DirectX::SimpleMath::Quaternion& ModelRotate,
			const DirectX::SimpleMath::Vector3& colliderCenter,
			const DirectX::SimpleMath::Quaternion& colliderRotate,
			const DirectX::SimpleMath::Vector3& Extents,
			const float& radius,
			const ColliderKinds& col
		);

		void SphereInitialize(
			const DirectX::SimpleMath::Vector3& ModelPosition,
			const DirectX::SimpleMath::Vector3& colliderCenter,
			const float& radius,
			const ColliderKinds& col
		);
		void BoxInitialize(
			const DirectX::SimpleMath::Vector3& ModelPosition,
			const DirectX::SimpleMath::Vector3& colliderCenter,
			const DirectX::SimpleMath::Vector3& Extents,
			const ColliderKinds& col
		);

		void OBBUpdate(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate);

		void SphereUpdate(const DirectX::SimpleMath::Vector3& position);

		void BoxUpdate(const DirectX::SimpleMath::Vector3& position);


		bool CheckHit(OBB* box);
		DirectX::SimpleMath::Vector3 CheckHitreflectionVector(OBB* box ,const DirectX::SimpleMath::Vector3& move);
		bool CheckHit(Box* box);
		bool CheckHit(Sphere* box);
		bool CheckHit(OLL* oll);

	private:
		DirectX::SimpleMath::Vector3 m_initialPosition;              // 位置
		DirectX::SimpleMath::Quaternion m_initialRotate;              // kaitenn
		DirectX::SimpleMath::Vector3 m_position;              // 位置
		DirectX::SimpleMath::Quaternion m_rotate;              // kaitenn
		DirectX::SimpleMath::Vector3 m_extents;             // 各軸方向の長さ

		std::unique_ptr<Collider::OBB> m_obbCol;
		std::unique_ptr<Collider::Sphere> m_sphereCol;
		std::unique_ptr<Collider::Box> m_boxCol;
		float m_radius;		// 半径
		ColliderKinds m_Collder;
	};

	/// <summary>
	/// MultipleHitDeterminationFactoryのクラスを定義する
	/// </summary>
	class MultipleHitDeterminationFactory
	{
	public:
		/// <summary>
		///  Boxのコライダーのを生成
		/// </summary>
		/// <param name="ModelPosition">モデルの位置</param>
		/// <param name="colliderCenter">コライダーの真ん中の位置</param>
		/// <param name="Extents">大きさ</param>
		/// <returns>OLLのコライダーのポインタ</returns>
		static std::unique_ptr<OLL> CreateBoxCollider(
			const DirectX::SimpleMath::Vector3& ModelPosition,
			const DirectX::SimpleMath::Vector3& colliderCenter,
			const DirectX::SimpleMath::Vector3& Extents
		)
		{
			std::unique_ptr<OLL> createCollider = std::make_unique<OLL>();
			createCollider->BoxInitialize(
				ModelPosition,
				colliderCenter,
				Extents,  ColliderKinds::BOX
			);
			return std::move(createCollider);
		}

		/// <summary>
		///  球のコライダーのを生成
		/// </summary>
		/// <param name="ModelPosition">モデルの位置</param>
		/// <param name="colliderCenter">コライダーの真ん中の位置</param>
		/// <param name="Extents">半径</param>
		/// <returns>OLLのコライダーのポインタ</returns>
		static std::unique_ptr<OLL> CreateSphereCollider(
			const DirectX::SimpleMath::Vector3& ModelPosition,
			const DirectX::SimpleMath::Vector3& colliderCenter,
			const float& radius
		)
		{
			std::unique_ptr<OLL> createCollider = std::make_unique<OLL>();
			createCollider->SphereInitialize(
				ModelPosition,
				colliderCenter,
				radius,
				ColliderKinds::SPHERE
			);
			return std::move(createCollider);
		}

		/// <summary>
		///  OBBのコライダーを生成
		/// </summary>
		/// <param name="ModelPosition">モデルの位置</param>
		/// <param name="ModelRotate">モデルの回転</param>
		/// <param name="colliderCenter">コライダーの真ん中の位置</param>
		/// <param name="colliderRotate">コライダーの回転</param>
		/// <param name="Extents">大きさ</param>
		/// <returns>OLLのコライダーのポインタ</returns>
		static std::unique_ptr<OLL> CreateOBBCollider(
			const DirectX::SimpleMath::Vector3& ModelPosition,
			const DirectX::SimpleMath::Quaternion& ModelRotate,
			const DirectX::SimpleMath::Vector3& colliderCenter,
			const DirectX::SimpleMath::Quaternion& colliderRotate,
			const DirectX::SimpleMath::Vector3& Extents
		)
		{
			std::unique_ptr<OLL> createCollider = std::make_unique<OLL>();
			createCollider->OBBInitialize(
				ModelPosition,
				ModelRotate,
				colliderCenter,
				colliderRotate,
				Extents,
				0.0f,
				ColliderKinds::OBBCol
			);
			return std::move(createCollider);
		}
	};

};
