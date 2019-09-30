#include "pch.h"

#include "Collider.h"
#include "GameObject.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Collider::Collider(GameObject* owner)
	: m_owner(owner)
	, m_offset(Vector3(0.0f, 0.0f, 0.0f))
{
}


bool Collider::IsCollided(const SphereCollider* collider) const
{
	assert(false && "This collision detection is not implemented.");

	return false;
}


bool Collider::IsCollided(const BoxCollider* collider) const
{
	assert(false && "This collision detection is not implemented.");

	return false;
}


void Collider::OnCollision(const Collider* object) const
{
	m_owner->OnCollision(object->m_owner);
}


const Vector3 Collider::GetPosition() const
{
	return m_owner->GetPosition() + m_offset;
}


const Vector3 Collider::GetOffset() const
{
	return m_offset;
}


void Collider::SetOffset(const Vector3 & offset)
{
	m_offset = offset;
}