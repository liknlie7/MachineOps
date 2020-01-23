#include "pch.h"

#include "Collider.h"
#include "GameObject.h"

// �R���X�g���N�^
Collider::Collider(GameObject* _owner)
	: m_owner(_owner)
	, m_offset(DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f))
{
}


bool Collider::IsCollided(const SphereCollider* _collider) const
{
	assert(false && "This collision detection is not implemented.");

	return false;
}


bool Collider::IsCollided(const BoxCollider* _collider) const
{
	assert(false && "This collision detection is not implemented.");

	return false;
}

// �Փ�
void Collider::OnCollision(const Collider* _object) const
{
	m_owner->OnCollision(_object->m_owner);
}