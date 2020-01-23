#include "pch.h"

#include "SphereCollider.h"
#include "GameObject.h"
#include "CollisionManager.h"


// コンストラクタ
SphereCollider::SphereCollider(GameObject* _owner, float _radius)
	: Collider(_owner)
	, m_radius(_radius)
{

}

bool SphereCollider::IsCollided(const Collider* _collider) const
{
	return _collider->IsCollided(this);
}


bool SphereCollider::IsCollided(const SphereCollider* _collider) const
{
	return CollisionManager::IsCollided(this, _collider);
}


bool SphereCollider::IsCollided(const BoxCollider* _collider) const
{
	return CollisionManager::IsCollided(this, _collider);
}