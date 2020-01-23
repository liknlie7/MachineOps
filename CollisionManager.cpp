#include "pch.h"

#include "CollisionManager.h"

#include "GameObject.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Utilities.h"

// コンストラクタ
CollisionManager::CollisionManager()
	: m_colliderGroups()
	, m_collisionGroups()
{

}

// デストラクタ
CollisionManager::~CollisionManager()
{
}


void CollisionManager::DetectCollision()
{
	for (const CollisionGroup& collisionGroup : m_collisionGroups)
	{
		if (collisionGroup.second.empty())
		{
			ColliderList& colliders = m_colliderGroups[collisionGroup.first];

			DetectCollision(colliders);
		}
		else
		{
			ColliderList& colliders1 = m_colliderGroups[collisionGroup.first];
			ColliderList& colliders2 = m_colliderGroups[collisionGroup.second];

			DetectCollision(colliders1, colliders2);
		}
	}

	m_colliderGroups.clear();
}


void CollisionManager::DetectCollision(const ColliderList& _colliders)
{
	int numObjects = _colliders.size();

	for (int i = 0; i < numObjects - 1; i++)
	{
		for (int j = i + 1; j < numObjects; j++)
		{
			if (_colliders[i]->IsCollided(_colliders[j]))
			{
				_colliders[i]->OnCollision(_colliders[j]);
				_colliders[j]->OnCollision(_colliders[i]);
			}
		}
	}
}


void CollisionManager::DetectCollision(const ColliderList& _colliders1, const ColliderList& _colliders2)
{
	for (const Collider* collider1 : _colliders1)
	{
		for (const Collider* collider2 : _colliders2)
		{
			if (collider1->IsCollided(collider2))
			{
				collider1->OnCollision(collider2);
				collider2->OnCollision(collider1);
			}
		}
	}
}


void CollisionManager::Add(const std::string& _groupName, Collider* _collider)
{
	m_colliderGroups[_groupName].push_back(_collider);
}

void CollisionManager::Add(const std::string& _groupName, SphereCollider* _sphereCollider)
{
	m_colliderGroups[_groupName].push_back(_sphereCollider);
}


void CollisionManager::AllowCollision(const std::string& _groupName1, const std::string& _groupName2)
{
	if (_groupName1 == _groupName2)
	{
		m_collisionGroups.push_back(std::make_pair(_groupName1, ""));
	}
	else
	{
		m_collisionGroups.push_back(std::make_pair(_groupName1, _groupName2));
	}
}


// 球同士の衝突判定
bool CollisionManager::IsCollided(const SphereCollider* _collider1, const SphereCollider* _collider2)
{
	// 球の中心の差
	DirectX::SimpleMath::Vector3 sub = _collider1->GetPosition() - _collider2->GetPosition();

	float distance = sub.Length();

	if (distance > _collider1->GetRadius() + _collider2->GetRadius())
	{
		return false;
	}
	return true;
}



//bool CollisionManager::IsCollided(const BoxCollider* _collider1, const BoxCollider* _collider2)
//{
//	return false;
//}



bool CollisionManager::IsCollided(const SphereCollider* collider1, const BoxCollider* collider2)
{
	float sqDist = SqDistPointBox(collider1->GetPosition(), collider2);
	return sqDist <= collider1->GetRadius() * collider1->GetRadius();
}

//bool CollisionManager::IsCollided(const BoxCollider* collider1, const SphereCollider* collider2)
//{
//	return IsCollided(collider2, collider1);
//}

// 点とボックスの間の最短距離の平方を計算する関数
float CollisionManager::SqDistPointBox(const DirectX::SimpleMath::Vector3& _point, const BoxCollider* _box)
{
	DirectX::SimpleMath::Vector3 boxPos,boxSize;
	boxPos = _box->GetPosition();
	boxSize = _box->GetSize();
	
	float point[3] = { _point.x, _point.y, _point.z };
	float min[3] = { boxPos.x - boxSize.x, boxPos.y - boxSize.y, boxPos.z - boxSize.z, };
	float max[3] = { boxPos.x + boxSize.x, boxPos.y + boxSize.y, boxPos.z + boxSize.z, };

	float sqDist = 0.0f;
	for (int i = 0; i < 3; i++)
	{
		float v = point[i];
		if (v < min[i]) sqDist += (min[i] - v) * (min[i] - v);
		if (v > max[i]) sqDist += (v - max[i]) * (v - max[i]);
	}
	return sqDist;
}
