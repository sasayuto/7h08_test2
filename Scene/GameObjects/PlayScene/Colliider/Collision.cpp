#include"pch.h"
#include "Collision.h"

using namespace DirectX;

bool Collider::Sphere::CheckHitSphereBox(Box* collider)
{
	// AABBの『各軸の最大値、最小値』を求める
	SimpleMath::Vector3 min = collider->GetPosition() - collider->GetExtents();
	SimpleMath::Vector3 max = collider->GetPosition() + collider->GetExtents();

	// 各軸の『球の中心とAABBとの距離』を求める
	min = min - SimpleMath::Vector3::Min(m_position, min);
	max = SimpleMath::Vector3::Max(m_position, max) - max;

	// 『球の中心とAABBの距離の２乗』を内積を使ってもとめる
	float distSq = min.Dot(min) + max.Dot(max);

	// 『球の中心とAABBの距離の２乗』と『球の半径の２乗』を比較する
	return distSq <= m_radius * m_radius;
}

bool Collider::Sphere::CheckHitSphere(Sphere* collider)
{
	// 2つの球の中心の間の距離の平方を計算
	SimpleMath::Vector3 d = m_position - collider->m_position;

	// 平方した距離が平方した半径の合計よりも小さい場合に球は交差している
	float radiusSum = m_radius + collider->m_radius;
	return d.LengthSquared() <= radiusSum * radiusSum;
}

bool Collider::Box::CheckHitBox(Box* collider)
{
	if (fabsf(m_position.x - collider->GetPosition().x) > (m_extents.x + collider->GetExtents().x)) return false;
	if (fabsf(m_position.y - collider->GetPosition().y) > (m_extents.y + collider->GetExtents().y)) return false;
	if (fabsf(m_position.z - collider->GetPosition().z) > (m_extents.z + collider->GetExtents().z)) return false;
	return true;
}

bool Collider::OBB::CheckHitOBB(OBB* box)
{
	DirectX::SimpleMath::Vector3 RPosition;
	RPosition = m_position - box->GetPosition();

	if (GetSeparatingPlane(RPosition, GetDirect(0), *box))							return false;
	if (GetSeparatingPlane(RPosition, GetDirect(1), *box))							return false;
	if (GetSeparatingPlane(RPosition, GetDirect(2), *box))							return false;
	if (GetSeparatingPlane(RPosition, box->GetDirect(0), *box)) 					return false;
	if (GetSeparatingPlane(RPosition, box->GetDirect(1), *box))						return false;
	if (GetSeparatingPlane(RPosition, box->GetDirect(2), *box))						return false;
	if (GetSeparatingPlane(RPosition, box->GetDirect(0).Cross(GetDirect(0)), *box)) return false;
	if (GetSeparatingPlane(RPosition, box->GetDirect(0).Cross(GetDirect(1)), *box)) return false;
	if (GetSeparatingPlane(RPosition, box->GetDirect(0).Cross(GetDirect(2)), *box)) return false;
	if (GetSeparatingPlane(RPosition, box->GetDirect(1).Cross(GetDirect(0)), *box)) return false;
	if (GetSeparatingPlane(RPosition, box->GetDirect(1).Cross(GetDirect(1)), *box)) return false;
	if (GetSeparatingPlane(RPosition, box->GetDirect(1).Cross(GetDirect(2)), *box)) return false;
	if (GetSeparatingPlane(RPosition, box->GetDirect(2).Cross(GetDirect(0)), *box)) return false;
	if (GetSeparatingPlane(RPosition, box->GetDirect(2).Cross(GetDirect(1)), *box)) return false;
	if (GetSeparatingPlane(RPosition, box->GetDirect(2).Cross(GetDirect(2)), *box)) return false;
	return true;
}

bool Collider::OBB::CheckHitOBBBox(Box* box)
{
	DirectX::SimpleMath::Vector3 UnitX = DirectX::SimpleMath::Vector3::UnitX;
	DirectX::SimpleMath::Vector3 UnitY = DirectX::SimpleMath::Vector3::UnitY;
	DirectX::SimpleMath::Vector3 UnitZ = DirectX::SimpleMath::Vector3::UnitZ;

	DirectX::SimpleMath::Vector3 RPosition;
	RPosition = GetPosition() - box->GetPosition();
	if (GetSeparatingPlane(RPosition, UnitX, *box))						return false;
	if (GetSeparatingPlane(RPosition, UnitY, *box))						return false;
	if (GetSeparatingPlane(RPosition, UnitZ, *box))						return false;
	if (GetSeparatingPlane(RPosition, GetDirect(0), *box))				return false;
	if (GetSeparatingPlane(RPosition, GetDirect(1), *box))				return false;
	if (GetSeparatingPlane(RPosition, GetDirect(2), *box))				return false;
	if (GetSeparatingPlane(RPosition, UnitX.Cross(GetDirect(0)), *box)) return false;
	if (GetSeparatingPlane(RPosition, UnitX.Cross(GetDirect(1)), *box)) return false;
	if (GetSeparatingPlane(RPosition, UnitX.Cross(GetDirect(2)), *box)) return false;
	if (GetSeparatingPlane(RPosition, UnitY.Cross(GetDirect(0)), *box)) return false;
	if (GetSeparatingPlane(RPosition, UnitY.Cross(GetDirect(1)), *box)) return false;
	if (GetSeparatingPlane(RPosition, UnitY.Cross(GetDirect(2)), *box)) return false;
	if (GetSeparatingPlane(RPosition, UnitZ.Cross(GetDirect(0)), *box)) return false;
	if (GetSeparatingPlane(RPosition, UnitZ.Cross(GetDirect(1)), *box)) return false;
	if (GetSeparatingPlane(RPosition, UnitZ.Cross(GetDirect(2)), *box)) return false;
	return true;
}

DirectX::SimpleMath::Vector3 Collider::OBB::CheckHitreflectionVector(OBB* box)
{
	DirectX::SimpleMath::Vector3 RPosition;
	RPosition = m_position - box->GetPosition();

	if (GetSeparatingPlane(RPosition, GetDirect(0), *box))							return DirectX::SimpleMath::Vector3::Zero;
	if (GetSeparatingPlane(RPosition, GetDirect(1), *box))							return DirectX::SimpleMath::Vector3::Zero;
	if (GetSeparatingPlane(RPosition, GetDirect(2), *box))							return DirectX::SimpleMath::Vector3::Zero;
	if (GetSeparatingPlane(RPosition, box->GetDirect(0), *box))						return DirectX::SimpleMath::Vector3::Zero;
	if (GetSeparatingPlane(RPosition, box->GetDirect(1), *box))						return DirectX::SimpleMath::Vector3::Zero;
	if (GetSeparatingPlane(RPosition, box->GetDirect(2), *box))						return DirectX::SimpleMath::Vector3::Zero;
	if (GetSeparatingPlane(RPosition, box->GetDirect(0).Cross(GetDirect(0)), *box)) return DirectX::SimpleMath::Vector3::Zero;
	if (GetSeparatingPlane(RPosition, box->GetDirect(0).Cross(GetDirect(1)), *box)) return DirectX::SimpleMath::Vector3::Zero;
	if (GetSeparatingPlane(RPosition, box->GetDirect(0).Cross(GetDirect(2)), *box)) return DirectX::SimpleMath::Vector3::Zero;
	if (GetSeparatingPlane(RPosition, box->GetDirect(1).Cross(GetDirect(0)), *box)) return DirectX::SimpleMath::Vector3::Zero;
	if (GetSeparatingPlane(RPosition, box->GetDirect(1).Cross(GetDirect(1)), *box)) return DirectX::SimpleMath::Vector3::Zero;
	if (GetSeparatingPlane(RPosition, box->GetDirect(1).Cross(GetDirect(2)), *box)) return DirectX::SimpleMath::Vector3::Zero;
	if (GetSeparatingPlane(RPosition, box->GetDirect(2).Cross(GetDirect(0)), *box)) return DirectX::SimpleMath::Vector3::Zero;
	if (GetSeparatingPlane(RPosition, box->GetDirect(2).Cross(GetDirect(1)), *box)) return DirectX::SimpleMath::Vector3::Zero;
	if (GetSeparatingPlane(RPosition, box->GetDirect(2).Cross(GetDirect(2)), *box)) return DirectX::SimpleMath::Vector3::Zero;

	//ｘが上、真ん中がｙ、ｚが下
	float sss = fabs(RPosition.Dot(GetDirect(0))) / (fabs((box->GetDirect(0)).Dot(GetDirect(0))) + fabs((box->GetDirect(1)).Dot(GetDirect(0))) +
		fabs((box->GetDirect(2)).Dot(GetDirect(0))) + GetDirect(0).LengthSquared());
	float ss = fabs(RPosition.Dot(GetDirect(1))) / (fabs((box->GetDirect(0)).Dot(GetDirect(1))) + fabs((box->GetDirect(1)).Dot(GetDirect(1))) +
		fabs((box->GetDirect(2)).Dot(GetDirect(1))) + GetDirect(0).LengthSquared());
	float s = fabs(RPosition.Dot(GetDirect(2))) / (fabs((box->GetDirect(0)).Dot(GetDirect(2))) + fabs((box->GetDirect(1)).Dot(GetDirect(2))) +
		fabs((box->GetDirect(2)).Dot(GetDirect(2))) + GetDirect(0).LengthSquared());

	//壁刷り
	//float aaaaa = (box->GetDirect(2)).Dot(GetDirect(0));
	//float baaaaa = (box->GetDirect(2)).Dot(GetDirect(1));
	//float acaaaa = (box->GetDirect(2)).Dot(GetDirect(2));

	//反射方向ベクトル
	SimpleMath::Vector3 sr;
	if (sss > ss && sss > s)
		sr = box->GetDirect(2) - 2 * box->GetDirect(2).Dot(GetDirect(0)) * GetDirect(0);
	if (ss > sss && ss > s)
		sr = box->GetDirect(2) - 2 * box->GetDirect(2).Dot(GetDirect(1)) * GetDirect(1);
	if (s > ss && s > sss)
		sr = box->GetDirect(2) - 2 * box->GetDirect(2).Dot(GetDirect(2)) * GetDirect(2);

	return sr;
}


bool Collider::OBB::CheckHitSphere(Sphere* box)
{
	SimpleMath::Vector3 retvec = m_position;
	SimpleMath::Vector3 d = box->GetPosition() - m_position;

	float dist = d.Dot(m_NormaDirect[0]);
	if (dist > m_extents.x) dist = m_extents.x;
	if (dist < -m_extents.x) dist = -m_extents.x;

	retvec += dist * m_NormaDirect[0];

	dist = d.Dot(m_NormaDirect[1]);
	if (dist > m_extents.y) dist = m_extents.y;
	if (dist < -m_extents.y) dist = -m_extents.y;

	retvec += dist * m_NormaDirect[1];

	dist = d.Dot(m_NormaDirect[2]);
	if (dist > m_extents.z) dist = m_extents.z;
	if (dist < -m_extents.z) dist = -m_extents.z;

	retvec += dist * m_NormaDirect[2];

	SimpleMath::Vector3 v = retvec - box->GetPosition();

	return v.Dot(v) <= box->GetRadius() * box->GetRadius();
}

bool Collider::Box2D::CheckHitBox(Box2D* collider)
{
	if (fabsf(m_position.x - collider->GetPosition().x) > (m_extents.x + collider->GetExtents().x)) return false;
	if (fabsf(m_position.y - collider->GetPosition().y) > (m_extents.y + collider->GetExtents().y)) return false;
	return true;
}

bool Collider::Box2D::CheckHitPoint(int mouse_x, int mouse_y)
{
	if (fabsf(m_position.x - mouse_x) > m_extents.x) return false;
	if (fabsf(m_position.y - mouse_y) > m_extents.y) return false;
	return true;
}
DirectX::SimpleMath::Vector3 Collider::OBB::CheckHitreflectionVector(OBB* obb, const DirectX::SimpleMath::Vector3& move)
{
	//OBBの判定
	DirectX::SimpleMath::Vector3 RPosition;
	RPosition = m_position - obb->GetPosition();
	if (!GetOBBHit(m_extents, RPosition, obb)) return DirectX::SimpleMath::Vector3::Zero;

	//調整中なので強制的に終了
	return DirectX::SimpleMath::Vector3::One;

	//家の短いほう
	RPosition = (m_position - DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(m_extents.x, 0, 0), m_rotate)) - obb->GetPosition();
	DirectX::SimpleMath::Vector3 e = m_extents;
	e.x = 0;

	DirectX::SimpleMath::Vector3 Direction;
		if (GetOBBHit(e, RPosition, obb))
		{
			Direction = move - (2 * move.Dot(m_NormaDirect[0]) * m_NormaDirect[0]);
			Direction.Normalize();
			return Direction;

		}
	RPosition = (m_position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(m_extents.x, 0, 0), m_rotate)) - obb->GetPosition();
		if (GetOBBHit(e, RPosition, obb))
		{
			Direction = move - (2 * move.Dot(m_NormaDirect[0]) * m_NormaDirect[0]);
			Direction.Normalize();
			return Direction;
		}

	//家の長いほう
	RPosition = (m_position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, 0, m_extents.z), m_rotate)) - obb->GetPosition();
	e = m_extents;
	e.z = 0;
		if (GetOBBHit(e, RPosition, obb))
		{
			Direction = move - (2 * move.Dot(m_NormaDirect[2]) * m_NormaDirect[2]);
			Direction.Normalize();
			return Direction;

		}
	RPosition = (m_position - DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, 0, m_extents.z), m_rotate)) - obb->GetPosition();
		if (GetOBBHit(e, RPosition, obb))
		{
			Direction = move - (2 * move.Dot(m_NormaDirect[2]) * m_NormaDirect[2]);
			Direction.Normalize();
			return Direction;

		}

	//ｙ座標
	RPosition = (m_position + DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, m_extents.y, 0), m_rotate)) - obb->GetPosition();
	e = m_extents;
	e.y = 0;
		if (GetOBBHit(e, RPosition, obb))
		{
			Direction = move - (2 * move.Dot(m_NormaDirect[1]) * m_NormaDirect[1]);
			Direction.Normalize();
			return Direction;

		}
	RPosition = (m_position - DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3(0, m_extents.y, 0), m_rotate)) - obb->GetPosition();
		if (GetOBBHit(e, RPosition, obb))
		{
			Direction = move - (2 * move.Dot(m_NormaDirect[1]) * m_NormaDirect[1]);
			Direction.Normalize();
			return Direction;

		}

	return DirectX::SimpleMath::Vector3::Zero;
}


bool Collider::OBB::GetSeparatingPlane(DirectX::SimpleMath::Vector3 e, const DirectX::SimpleMath::Vector3& RPosition, const DirectX::SimpleMath::Vector3& Plane, const OBB& box)
{
	return (fabs(RPosition.Dot(Plane)) >
		(fabs((box.GetDirect(0) * box.GetExtents().x).Dot(Plane)) +
			fabs((box.GetDirect(1) * box.GetExtents().y).Dot(Plane)) +
			fabs((box.GetDirect(2) * box.GetExtents().z).Dot(Plane)) +
			fabs((GetDirect(0) * e.x).Dot(Plane)) +
			fabs((GetDirect(1) * e.y).Dot(Plane)) +
			fabs((GetDirect(2) * e.z).Dot(Plane))));
}

bool Collider::OBB::GetOBBHit(DirectX::SimpleMath::Vector3 e, const DirectX::SimpleMath::Vector3& RPosition, OBB* obb)
{
	if (GetSeparatingPlane(e, RPosition, GetDirect(0), *obb))					        return false;
	if (GetSeparatingPlane(e, RPosition, GetDirect(1), *obb))					        return false;
	if (GetSeparatingPlane(e, RPosition, GetDirect(2), *obb))					        return false;
	if (GetSeparatingPlane(e, RPosition, obb->GetDirect(0), *obb)) 			        return false;
	if (GetSeparatingPlane(e, RPosition, obb->GetDirect(1), *obb))				        return false;
	if (GetSeparatingPlane(e, RPosition, obb->GetDirect(2), *obb))				        return false;
	if (GetSeparatingPlane(e, RPosition, obb->GetDirect(0).Cross(GetDirect(0)), *obb)) return false;
	if (GetSeparatingPlane(e, RPosition, obb->GetDirect(0).Cross(GetDirect(1)), *obb)) return false;
	if (GetSeparatingPlane(e, RPosition, obb->GetDirect(0).Cross(GetDirect(2)), *obb)) return false;
	if (GetSeparatingPlane(e, RPosition, obb->GetDirect(1).Cross(GetDirect(0)), *obb)) return false;
	if (GetSeparatingPlane(e, RPosition, obb->GetDirect(1).Cross(GetDirect(1)), *obb)) return false;
	if (GetSeparatingPlane(e, RPosition, obb->GetDirect(1).Cross(GetDirect(2)), *obb)) return false;
	if (GetSeparatingPlane(e, RPosition, obb->GetDirect(2).Cross(GetDirect(0)), *obb)) return false;
	if (GetSeparatingPlane(e, RPosition, obb->GetDirect(2).Cross(GetDirect(1)), *obb)) return false;
	if (GetSeparatingPlane(e, RPosition, obb->GetDirect(2).Cross(GetDirect(2)), *obb)) return false;
	return true;
}
