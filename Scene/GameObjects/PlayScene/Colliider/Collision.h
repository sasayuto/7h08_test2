#pragma once
/// <summary>
/// 当たり判定のクラスを定義する
/// </summary>
namespace Collider
{
	/// <summary>
	/// 四角形の当たり判定の当たり判定
	/// </summary>
	class Box
	{
	public:
		//位置のセッター
		void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
		DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }

		//範囲のセッター
		void SetExtents(const DirectX::SimpleMath::Vector3& extents) { m_extents = extents; }
		DirectX::SimpleMath::Vector3 GetExtents() const { return m_extents; }

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		Box() :m_extents(), m_position() {};

		/// <summary>
		/// デストラクタ
		/// </summary>
		~Box() {};

		/// <summary>
		///  ボックスとボックスの当たり判定
		/// </summary>
		/// <param name="collider">ボックスの情報</param>
		/// <returns>当たり判定</returns>
		bool CheckHitBox(Box* collider);

	private:
		// 位置
		DirectX::SimpleMath::Vector3 m_position;

		// 範囲
		DirectX::SimpleMath::Vector3 m_extents;
	};
	/// <summary>
	/// 四角形の当たり判定の当たり判定
	/// </summary>
	class Box2D
	{
	public:
		//位置のセッター
		void SetPosition(const DirectX::SimpleMath::Vector2& position) { m_position = position; }
		DirectX::SimpleMath::Vector2 GetPosition() const { return m_position; }

		//範囲のセッター
		void SetExtents(const DirectX::SimpleMath::Vector2& extents) { m_extents = extents; }
		DirectX::SimpleMath::Vector2 GetExtents() const { return m_extents; }

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		Box2D() :m_extents(), m_position() {};

		/// <summary>
		/// デストラクタ
		/// </summary>
		~Box2D() {};
		void Initialize(const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& Extents)
		{
			m_extents = Extents;
			m_position = position;
		}

		void Update(const DirectX::SimpleMath::Vector2& position) { m_position = position; }

		/// <summary>
		///  ボックスとボックスの当たり判定
		/// </summary>
		/// <param name="collider">ボックスの情報</param>
		/// <returns>当たり判定</returns>
		bool CheckHitBox(Box2D* collider);
		bool CheckHitPoint(int mouse_x, int mouse_y);

	private:
		// 位置
		DirectX::SimpleMath::Vector2 m_position;

		// 範囲
		DirectX::SimpleMath::Vector2 m_extents;
	};

	/// <summary>
	/// 球体の当たり判定のクラスを定義する
	/// </summary>
	class Sphere
	{
	public:
		//半径のセッター
		void SetRadius(const float& Radius) { m_radius = Radius; }
		float GetRadius() const { return m_radius; }

		//位置のセッター
		void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
		DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		Sphere() :m_position(), m_radius() {};

		/// <summary>
		/// デストラクタ
		/// </summary>
		~Sphere() {};

		/// <summary>
		///  ボックスと球の当たり判定
		/// </summary>
		/// <param name="collider">ボックスの情報</param>
		/// <returns>当たり判定</returns>
		bool CheckHitSphereBox(Box* collider);

		/// <summary>
		///  球と球の当たり判定
		/// </summary>
		/// <param name="collider">球の情報</param>
		/// <returns>当たり判定</returns>
		bool CheckHitSphere(Sphere* collider);

	private:
		// 半径
		float m_radius;

		// 位置
		DirectX::SimpleMath::Vector3 m_position;
	};


	class OBB
	{
	public:
		DirectX::SimpleMath::Vector3 GetDirect(int elem) const { return m_NormaDirect[elem]; };   // 指定軸番号の方向ベクトルを取得
		DirectX::SimpleMath::Vector3 GetExtents() const { return m_extents; };          // 指定軸方向の長さを取得
		DirectX::SimpleMath::Vector3 GetPosition()const { return m_position; };             // 位置を取得

	public:
		/// <summary>
		/// コンストラクタ
		/// </summary>
		OBB() :
			m_extents(),
			m_position(),
			m_rotate() {}

		/// <summary>
		/// デストラクタ
		/// </summary>
		~OBB() {}

		void Initialize(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate, const DirectX::SimpleMath::Vector3& Extents)
		{
			m_extents = Extents;
			m_position = position;
			m_rotate = rotate;

			m_NormaDirect[0] = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitX, m_rotate);
			m_NormaDirect[1] = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitY, m_rotate);
			m_NormaDirect[2] = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ, m_rotate);
		}

		void Update(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate)
		{
			m_position = position;
			m_NormaDirect[0] = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitX, rotate);
			m_NormaDirect[1] = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitY, rotate);
			m_NormaDirect[2] = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ, rotate);
		}

		bool CheckHitSphere(Sphere* box);

		bool CheckHitOBB(OBB* box);

		bool CheckHitOBBBox(Box* box);

		DirectX::SimpleMath::Vector3 CheckHitreflectionVector(OBB* box);
		DirectX::SimpleMath::Vector3 CheckHitreflectionVector(OBB* box,const DirectX::SimpleMath::Vector3& move);

	private:
		DirectX::SimpleMath::Vector3 m_position;              // 位置
		DirectX::SimpleMath::Quaternion m_rotate;             // 位置
		DirectX::SimpleMath::Vector3 m_NormaDirect[3];		  // 方向ベクトル
		DirectX::SimpleMath::Vector3 m_extents;               // 各軸方向の長さ

		bool GetSeparatingPlane(const DirectX::SimpleMath::Vector3& RPosition, const DirectX::SimpleMath::Vector3& Plane, const OBB& box)
		{
			return (fabs(RPosition.Dot(Plane)) >
				(fabs((box.GetDirect(0) * box.GetExtents().x).Dot(Plane)) +
					fabs((box.GetDirect(1) * box.GetExtents().y).Dot(Plane)) +
					fabs((box.GetDirect(2) * box.GetExtents().z).Dot(Plane)) +
					fabs((GetDirect(0) * GetExtents().x).Dot(Plane)) +
					fabs((GetDirect(1) * GetExtents().y).Dot(Plane)) +
					fabs((GetDirect(2) * GetExtents().z).Dot(Plane))));

		}
		bool GetSeparatingPlane(DirectX::SimpleMath::Vector3 e, const DirectX::SimpleMath::Vector3& RPosition, const DirectX::SimpleMath::Vector3& Plane, const OBB& box);

		bool GetOBBHit(DirectX::SimpleMath::Vector3 e, const DirectX::SimpleMath::Vector3& RPosition, OBB* obb);


		bool GetSeparatingPlane(const DirectX::SimpleMath::Vector3& RPosition, const DirectX::SimpleMath::Vector3& Plane, const Box& box)
		{
			return (fabs(RPosition.Dot(Plane)) >
				(fabs((DirectX::SimpleMath::Vector3::UnitX * box.GetExtents().x).Dot(Plane)) +
					fabs((DirectX::SimpleMath::Vector3::UnitY * box.GetExtents().y).Dot(Plane)) +
					fabs((DirectX::SimpleMath::Vector3::UnitZ * box.GetExtents().z).Dot(Plane)) +
					fabs((GetDirect(0) * GetExtents().x).Dot(Plane)) +
					fabs((GetDirect(1) * GetExtents().y).Dot(Plane)) +
					fabs((GetDirect(2) * GetExtents().z).Dot(Plane))));

		}
	};
};