#include "pch.h"

#include "BoxCollider.h"
#include "GameObject.h"
#include "CollisionManager.h"

// コンストラクタ
BoxCollider::BoxCollider(GameObject* _owner, const DirectX::SimpleMath::Vector3& _size)
	: Collider(_owner)
	, m_size(_size)
{

}


bool BoxCollider::IsCollided(const Collider* _collider) const
{
	return _collider->IsCollided(this);
}


bool BoxCollider::IsCollided(const SphereCollider* _collider) const
{
	return CollisionManager::IsCollided(_collider , this);
}


//bool BoxCollider::IsCollided(const BoxCollider* _collider) const
//{
//	return CollisionManager::IsCollided(this, _collider);
//}