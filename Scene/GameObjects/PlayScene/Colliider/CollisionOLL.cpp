#include"pch.h"
#include "CollisionOLL.h"

using namespace DirectX;


bool Collider::MultipleHitDetermination::CheckAllHit(Box* box)
{
	for (auto& collider : m_collider)
		if (!collider->CheckHit(box))
			return false;
	return true;
}

bool Collider::MultipleHitDetermination::CheckAllHit(OBB* box)
{
	for (auto& collider : m_collider)
		if (!collider->CheckHit(box))
			return false;
	return true;
}

bool Collider::MultipleHitDetermination::CheckAllHit(Sphere* box)
{
	for (auto& collider : m_collider)
		if (!collider->CheckHit(box))
			return false;
	return true;
}

bool Collider::MultipleHitDetermination::CheckHitOneOrMore(Box* box)
{
	for (auto& collider : m_collider)
		if (collider->CheckHit(box))
			return true;
	return false;
}

bool Collider::MultipleHitDetermination::CheckHitOneOrMore(OBB* box)
{
	for (auto& collider : m_collider)
		if (collider->CheckHit(box))
			return true;
	return false;
}

bool Collider::MultipleHitDetermination::CheckHitOneOrMore(Sphere* box)
{
	for (auto& collider : m_collider)
		if (collider->CheckHit(box))
			return true;
	return false;
}

bool Collider::MultipleHitDetermination::CheckHitOneOrMore(MultipleHitDetermination* oll)
{
	for (auto& nowCollider : m_collider)
		for (auto& collider : oll->m_collider)
			if (nowCollider->CheckHit(collider.get()))
				return true;
	return false;
}

DirectX::SimpleMath::Vector3 Collider::MultipleHitDetermination::CheckHitreflectionVector(OBB* obb, const DirectX::SimpleMath::Vector3& move)
{
	for (auto& collider : m_collider)
	{
		DirectX::SimpleMath::Vector3 reflectionVector = collider->CheckHitreflectionVector(obb, move);
		if (reflectionVector != DirectX::SimpleMath::Vector3::Zero)
			return reflectionVector;
	}
	return DirectX::SimpleMath::Vector3::Zero;
}

bool Collider::MultipleHitDetermination::CheckAllHit(MultipleHitDetermination* oll)
{
	for (auto& nowCollider : m_collider)
		for (auto& collider : oll->m_collider)
			if (!nowCollider->CheckHit(collider.get()))
				return false;
	return true;
}

bool Collider::MultipleHitDetermination::OneOrMoreAndAllHit(MultipleHitDetermination* oll)
{
	bool flog=false;
	for (auto& nowCollider : m_collider)
	{
		flog = true;
		for (auto& collider : oll->m_collider)
			if (!nowCollider->CheckHit(collider.get()))
				flog = false;

		if (flog)
			return true;
	}
	return false;
}

bool Collider::MultipleHitDetermination::AllHitAndOneOrMore(MultipleHitDetermination* oll)
{
	bool flog = false;
	for (auto& collider : oll->m_collider)
	{
		flog = true;
		for (auto& nowCollider : m_collider)
			if (!nowCollider->CheckHit(collider.get()))
				flog = false;

		if (flog)
			return true;
	}
	return false;
}

void Collider::MultipleHitDetermination::AllUpdate(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate)
{
	for (auto& collider : m_collider)
	{
		switch (collider->GetNowColl())
		{
		case Collider::ColliderKinds::BOX:
			collider->BoxUpdate(position);
			break;
		case Collider::ColliderKinds::OBBCol:
			collider->OBBUpdate(position, rotate);
			break;
		case Collider::ColliderKinds::SPHERE:
			collider->SphereUpdate(position);
			break;

		}
	}

}

void Collider::MultipleHitDetermination::Render(const DirectX::SimpleMath::Quaternion& rotate)
{
	for (auto& collider : m_collider)
	{
		switch (collider->GetNowColl())
		{
		case Collider::ColliderKinds::BOX:
			Draw::GetInstance()->TestCubeModel(collider->GetExtents(), collider->GetPosition());
			break;
		case Collider::ColliderKinds::OBBCol:
			Draw::GetInstance()->TestCubeModel(collider->GetExtents(), collider->GetPosition(), collider->GetRotate());
			break;
		case Collider::ColliderKinds::SPHERE:
			Draw::GetInstance()->TestSphereModel(collider->GetRadius(), collider->GetPosition());
			break;

		}
	}

}

Collider::OLL::OLL() : 
	m_extents(), 
	m_position(), 
	m_rotate(),
	m_radius(),
	m_Collder(),
	m_initialPosition(),
	m_initialRotate()
{
}

Collider::OLL::~OLL()
{
}

void Collider::OLL::OBBInitialize(const DirectX::SimpleMath::Vector3& ModelPosition, const DirectX::SimpleMath::Quaternion& ModelRotate, const DirectX::SimpleMath::Vector3& colliderCenter, const DirectX::SimpleMath::Quaternion& colliderRotate, const DirectX::SimpleMath::Vector3& Extents, const float& radius, const ColliderKinds& col)
{
	m_obbCol = std::make_unique<Collider::OBB>();
	m_Collder = col;
	m_radius = radius;
	m_extents = Extents;
	m_initialPosition = colliderCenter;
	m_initialRotate = colliderRotate;
	m_rotate = m_initialRotate * ModelRotate;
	m_position = ModelPosition + DirectX::SimpleMath::Vector3::Transform(m_initialPosition, ModelRotate);

	m_obbCol->Initialize(m_position, m_rotate, m_extents);

}

void Collider::OLL::BoxInitialize(const DirectX::SimpleMath::Vector3& ModelPosition, const DirectX::SimpleMath::Vector3& colliderCenter, const DirectX::SimpleMath::Vector3& Extents, const ColliderKinds& col)
{
	m_boxCol = std::make_unique < Collider::Box >();
	m_Collder = col;
	m_initialPosition = colliderCenter;
	m_position = ModelPosition + m_initialPosition;
	m_extents = Extents;

	m_boxCol->SetPosition(m_position);
	m_boxCol->SetExtents(m_extents);
}

void Collider::OLL::SphereInitialize(const DirectX::SimpleMath::Vector3& ModelPosition, const DirectX::SimpleMath::Vector3& colliderCenter, const float& radius, const ColliderKinds& col)
{
	m_sphereCol = std::make_unique < Collider::Sphere >();
	m_Collder = col;
	m_initialPosition = colliderCenter;
	m_position = ModelPosition + m_initialPosition;
	m_radius = radius;

	m_sphereCol->SetPosition(m_position);
	m_sphereCol->SetRadius(m_radius);
}

void Collider::OLL::OBBUpdate(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotate)
{
	m_rotate = m_initialRotate * rotate;
	m_position = position + DirectX::SimpleMath::Vector3::Transform(m_initialPosition, rotate);
	m_obbCol->Update(m_position, m_rotate);
}

void Collider::OLL::SphereUpdate(const DirectX::SimpleMath::Vector3& position)
{
	m_position = m_initialPosition + position;
	m_sphereCol->SetPosition(m_position);

}
void Collider::OLL::BoxUpdate(const DirectX::SimpleMath::Vector3& position)
{
	m_position = m_initialPosition + position;
	m_boxCol->SetPosition(m_position);

}

bool Collider::OLL::CheckHit(OBB* obb)
{
	if (m_Collder == Collider::ColliderKinds::BOX)
	{
		return obb->CheckHitOBBBox(m_boxCol.get());
	}
	if (m_Collder == Collider::ColliderKinds::SPHERE)
	{
		return obb->CheckHitSphere(m_sphereCol.get());
	}
	if (m_Collder == Collider::ColliderKinds::OBBCol)
	{
		return m_obbCol->CheckHitOBB(obb);
	}
	return false;
}

DirectX::SimpleMath::Vector3 Collider::OLL::CheckHitreflectionVector(OBB* box ,const DirectX::SimpleMath::Vector3& move)
{
	if (m_Collder == Collider::ColliderKinds::OBBCol)
	{
		return m_obbCol->CheckHitreflectionVector(box, move);
	}
	if (m_Collder == Collider::ColliderKinds::BOX)
	{
		if(box->CheckHitOBBBox(m_boxCol.get()))
			return box->GetDirect(2) * -1;
	}
	if (m_Collder == Collider::ColliderKinds::SPHERE)
	{
		if (box->CheckHitSphere(m_sphereCol.get()))
			return box->GetDirect(2) * -1;
	}
	return DirectX::SimpleMath::Vector3::Zero;
}

bool Collider::OLL::CheckHit(Box* box)
{
	if (m_Collder == Collider::ColliderKinds::BOX)
	{
		return m_boxCol->CheckHitBox(box);
	}
	if (m_Collder == Collider::ColliderKinds::SPHERE)
	{
		return m_sphereCol->CheckHitSphereBox(box);
	}
	if (m_Collder == Collider::ColliderKinds::OBBCol)
	{
		return m_obbCol->CheckHitOBBBox(box);
	}
	return false;
}

bool Collider::OLL::CheckHit(Sphere* sphere)
{
	if (m_Collder == Collider::ColliderKinds::BOX)
	{
		return sphere->CheckHitSphereBox(m_boxCol.get());
	}
	if (m_Collder == Collider::ColliderKinds::SPHERE)
	{
		return sphere->CheckHitSphere(m_sphereCol.get());
	}
	if (m_Collder == Collider::ColliderKinds::OBBCol)
	{
		return m_obbCol->CheckHitSphere(sphere);
	}
	return false;
}

bool Collider::OLL::CheckHit(OLL* oll)
{
	if (m_Collder == Collider::ColliderKinds::BOX)
	{
		if (oll->m_Collder == Collider::ColliderKinds::BOX)
		{
			return oll->m_boxCol->CheckHitBox(m_boxCol.get());
		}
		if (oll->m_Collder == Collider::ColliderKinds::SPHERE)
		{
			return oll->m_sphereCol->CheckHitSphereBox(m_boxCol.get());
		}
		if (oll->m_Collder == Collider::ColliderKinds::OBBCol)
		{
			return oll->m_obbCol->CheckHitOBBBox(m_boxCol.get());
		}
	}
	if (m_Collder == Collider::ColliderKinds::SPHERE)
	{
		if (oll->m_Collder == Collider::ColliderKinds::BOX)
		{
			return m_sphereCol->CheckHitSphereBox(oll->m_boxCol.get());
		}
		if (oll->m_Collder == Collider::ColliderKinds::SPHERE)
		{
			return oll->m_sphereCol->CheckHitSphere(m_sphereCol.get());
		}
		if (oll->m_Collder == Collider::ColliderKinds::OBBCol)
		{
			return oll->m_obbCol->CheckHitSphere(m_sphereCol.get());
		}
	}
	if (m_Collder == Collider::ColliderKinds::OBBCol)
	{
		if (oll->m_Collder == Collider::ColliderKinds::BOX)
		{
			return m_obbCol->CheckHitOBBBox(oll->m_boxCol.get());
		}
		if (oll->m_Collder == Collider::ColliderKinds::SPHERE)
		{
			return m_obbCol->CheckHitSphere(oll->m_sphereCol.get());
		}
		if (oll->m_Collder == Collider::ColliderKinds::OBBCol)
		{
			return m_obbCol->CheckHitOBB(oll->m_obbCol.get());
		}
	}
	return false;

}

