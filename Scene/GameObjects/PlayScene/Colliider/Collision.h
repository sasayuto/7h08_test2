#pragma once
/// <summary>
/// �����蔻��̃N���X���`����
/// </summary>
namespace Collider
{
	/// <summary>
	/// �l�p�`�̓����蔻��̓����蔻��
	/// </summary>
	class Box
	{
	public:
		//�ʒu�̃Z�b�^�[
		void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
		DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }

		//�͈͂̃Z�b�^�[
		void SetExtents(const DirectX::SimpleMath::Vector3& extents) { m_extents = extents; }
		DirectX::SimpleMath::Vector3 GetExtents() const { return m_extents; }

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Box() :m_extents(), m_position() {};

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~Box() {};

		/// <summary>
		///  �{�b�N�X�ƃ{�b�N�X�̓����蔻��
		/// </summary>
		/// <param name="collider">�{�b�N�X�̏��</param>
		/// <returns>�����蔻��</returns>
		bool CheckHitBox(Box* collider);

	private:
		// �ʒu
		DirectX::SimpleMath::Vector3 m_position;

		// �͈�
		DirectX::SimpleMath::Vector3 m_extents;
	};
	/// <summary>
	/// �l�p�`�̓����蔻��̓����蔻��
	/// </summary>
	class Box2D
	{
	public:
		//�ʒu�̃Z�b�^�[
		void SetPosition(const DirectX::SimpleMath::Vector2& position) { m_position = position; }
		DirectX::SimpleMath::Vector2 GetPosition() const { return m_position; }

		//�͈͂̃Z�b�^�[
		void SetExtents(const DirectX::SimpleMath::Vector2& extents) { m_extents = extents; }
		DirectX::SimpleMath::Vector2 GetExtents() const { return m_extents; }

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Box2D() :m_extents(), m_position() {};

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~Box2D() {};
		void Initialize(const DirectX::SimpleMath::Vector2& position, const DirectX::SimpleMath::Vector2& Extents)
		{
			m_extents = Extents;
			m_position = position;
		}

		void Update(const DirectX::SimpleMath::Vector2& position) { m_position = position; }

		/// <summary>
		///  �{�b�N�X�ƃ{�b�N�X�̓����蔻��
		/// </summary>
		/// <param name="collider">�{�b�N�X�̏��</param>
		/// <returns>�����蔻��</returns>
		bool CheckHitBox(Box2D* collider);
		bool CheckHitPoint(int mouse_x, int mouse_y);

	private:
		// �ʒu
		DirectX::SimpleMath::Vector2 m_position;

		// �͈�
		DirectX::SimpleMath::Vector2 m_extents;
	};

	/// <summary>
	/// ���̂̓����蔻��̃N���X���`����
	/// </summary>
	class Sphere
	{
	public:
		//���a�̃Z�b�^�[
		void SetRadius(const float& Radius) { m_radius = Radius; }
		float GetRadius() const { return m_radius; }

		//�ʒu�̃Z�b�^�[
		void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }
		DirectX::SimpleMath::Vector3 GetPosition() const { return m_position; }

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		Sphere() :m_position(), m_radius() {};

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~Sphere() {};

		/// <summary>
		///  �{�b�N�X�Ƌ��̓����蔻��
		/// </summary>
		/// <param name="collider">�{�b�N�X�̏��</param>
		/// <returns>�����蔻��</returns>
		bool CheckHitSphereBox(Box* collider);

		/// <summary>
		///  ���Ƌ��̓����蔻��
		/// </summary>
		/// <param name="collider">���̏��</param>
		/// <returns>�����蔻��</returns>
		bool CheckHitSphere(Sphere* collider);

	private:
		// ���a
		float m_radius;

		// �ʒu
		DirectX::SimpleMath::Vector3 m_position;
	};


	class OBB
	{
	public:
		DirectX::SimpleMath::Vector3 GetDirect(int elem) const { return m_NormaDirect[elem]; };   // �w�莲�ԍ��̕����x�N�g�����擾
		DirectX::SimpleMath::Vector3 GetExtents() const { return m_extents; };          // �w�莲�����̒������擾
		DirectX::SimpleMath::Vector3 GetPosition()const { return m_position; };             // �ʒu���擾

	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		OBB() :
			m_extents(),
			m_position(),
			m_rotate() {}

		/// <summary>
		/// �f�X�g���N�^
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
		DirectX::SimpleMath::Vector3 m_position;              // �ʒu
		DirectX::SimpleMath::Quaternion m_rotate;             // �ʒu
		DirectX::SimpleMath::Vector3 m_NormaDirect[3];		  // �����x�N�g��
		DirectX::SimpleMath::Vector3 m_extents;               // �e�������̒���

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