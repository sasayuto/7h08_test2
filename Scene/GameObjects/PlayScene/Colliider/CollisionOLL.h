#pragma once
#include"Scene/GameObjects/Models/Draw.h"
#include"Collision.h"

/// <summary>
/// �����蔻��̃N���X���`����
/// </summary>
namespace Collider
{
	// OLL�N���X�̑O���錾
	class OLL;

	/// <summary>
	/// �����̓����蔻��̃R���C�_�[
	/// </summary>
	class MultipleHitDetermination
	{
	public:
		//�R���C�_�[�����i������������̎��ɌĂяo���B�t�@�N�g���[�ł����j
		void AddCollider(std::unique_ptr<OLL> collider) { m_collider.push_back(std::move(collider)); }

		/// <summary>
		/// �S�ẴR���C�_�[�̃A�b�v�f�[�g
		/// </summary>
		/// <param name="position">�ʒu</param>
		/// <param name="rotate">��]</param>
		void AllUpdate(
			const DirectX::SimpleMath::Vector3& position,
			const DirectX::SimpleMath::Quaternion& rotate
		);

		//------------------------------------------------------------------
		//�P�ȏ�R���C�_�[������������
		//------------------------------------------------------------------
		/// <summary>
		/// �P�ȏ�R���C�_�[������������
		/// </summary>
		/// <param name="box">�l�p�̃A�h���X</param>
		/// <returns>Hit��true</returns>
		bool CheckHitOneOrMore(Box* box);
		/// <param name="box">OBB�̃A�h���X</param>
		bool CheckHitOneOrMore(OBB* box);
		/// <param name="box">���̃A�h���X</param>
		bool CheckHitOneOrMore(Sphere* box);
		/// <param name="box">�����̃R���C�_�[�̃A�h���X</param>
		bool CheckHitOneOrMore(MultipleHitDetermination* oll);


		//------------------------------------------------------------------
		// �S�ẴR���C�_�[������������
		//------------------------------------------------------------------
		/// <summary>
		/// �S�ẴR���C�_�[������������
		/// </summary>
		/// <param name="box">�l�p�̃A�h���X</param>
		/// <returns>Hit��true</returns>
		bool CheckAllHit(Box* box);
		/// <param name="box">OBB�̃A�h���X</param>
		bool CheckAllHit(OBB* box);
		/// <param name="box">���̃A�h���X</param>
		bool CheckAllHit(Sphere* box);
		/// <param name="box">�����̃R���C�_�[�̃A�h���X</param>
		bool CheckAllHit(MultipleHitDetermination* oll);


		//------------------------------------------------------------------
		// ����
		//------------------------------------------------------------------
		/// <summary>
		/// �����̑S�ẴR���C�_�[�������������Ƒ���̃R���C�_�[���P�ł��������Ă���
		/// </summary>
		/// <param name="oll"></param>
		/// <returns></returns>
		bool AllHitAndOneOrMore(MultipleHitDetermination* oll);

		/// <summary>
		/// ����̑S�ẴR���C�_�[�������������Ǝ����̃R���C�_�[���P�ł��������Ă���
		/// </summary>
		/// <param name="oll"></param>
		/// <returns></returns>
		bool OneOrMoreAndAllHit(MultipleHitDetermination* oll);

		/// <summary>
		/// obb�ƕ����̃R���C�_�[�̓����蔻�肩�甽�˃x�N�g�������߂�
		/// </summary>
		/// <param name="obb">obb�̃R���C�_�[</param>
		/// <returns>���˃x�N�g��</returns>
		DirectX::SimpleMath::Vector3 CheckHitreflectionVector(OBB* obb,const DirectX::SimpleMath::Vector3& move);
	
	public:
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		MultipleHitDetermination():m_collider(){}

		/// <summary>
		/// �f�X�g���N�^
		/// </summary>
		~MultipleHitDetermination() {};

		/// <summary>
		/// �����蔻��̕`��
		/// </summary>
		/// <param name="rotate">�Ӗ��͂Ȃ��i�����߂�ǂ��j</param>
		void Render(const DirectX::SimpleMath::Quaternion& rotate);

	private:
		//OLL�R���C�_�[�̔z��
		std::vector<std::unique_ptr<OLL>> m_collider;
	};
	enum class ColliderKinds { BOX, SPHERE, OBBCol, COUNT };			//�R���C�_�[�̎��

	/// <summary>
	/// �����̔���̃N���X���g�����̃N���X�i���Ȃ��Ă��ǂ��j
	/// </summary>
	class OLL
	{
	public:

		DirectX::SimpleMath::Vector3 GetExtents() const { return m_extents; };
		DirectX::SimpleMath::Vector3 GetPosition()const { return m_position; };             // �ʒu���擾
		DirectX::SimpleMath::Quaternion GetRotate()const { return m_rotate; };             // �ʒu���擾

		float GetRadius() const { return m_radius; }		//���a�̃Z�b�^�[

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
		DirectX::SimpleMath::Vector3 m_initialPosition;              // �ʒu
		DirectX::SimpleMath::Quaternion m_initialRotate;              // kaitenn
		DirectX::SimpleMath::Vector3 m_position;              // �ʒu
		DirectX::SimpleMath::Quaternion m_rotate;              // kaitenn
		DirectX::SimpleMath::Vector3 m_extents;             // �e�������̒���

		std::unique_ptr<Collider::OBB> m_obbCol;
		std::unique_ptr<Collider::Sphere> m_sphereCol;
		std::unique_ptr<Collider::Box> m_boxCol;
		float m_radius;		// ���a
		ColliderKinds m_Collder;
	};

	/// <summary>
	/// MultipleHitDeterminationFactory�̃N���X���`����
	/// </summary>
	class MultipleHitDeterminationFactory
	{
	public:
		/// <summary>
		///  Box�̃R���C�_�[�̂𐶐�
		/// </summary>
		/// <param name="ModelPosition">���f���̈ʒu</param>
		/// <param name="colliderCenter">�R���C�_�[�̐^�񒆂̈ʒu</param>
		/// <param name="Extents">�傫��</param>
		/// <returns>OLL�̃R���C�_�[�̃|�C���^</returns>
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
		///  ���̃R���C�_�[�̂𐶐�
		/// </summary>
		/// <param name="ModelPosition">���f���̈ʒu</param>
		/// <param name="colliderCenter">�R���C�_�[�̐^�񒆂̈ʒu</param>
		/// <param name="Extents">���a</param>
		/// <returns>OLL�̃R���C�_�[�̃|�C���^</returns>
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
		///  OBB�̃R���C�_�[�𐶐�
		/// </summary>
		/// <param name="ModelPosition">���f���̈ʒu</param>
		/// <param name="ModelRotate">���f���̉�]</param>
		/// <param name="colliderCenter">�R���C�_�[�̐^�񒆂̈ʒu</param>
		/// <param name="colliderRotate">�R���C�_�[�̉�]</param>
		/// <param name="Extents">�傫��</param>
		/// <returns>OLL�̃R���C�_�[�̃|�C���^</returns>
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
