#pragma once

#include <vector>
#include <memory>
#include <SimpleMath.h>
#include <vector>
#include <functional>
#include <unordered_map>

#include "Collider.h"

class GameObject;
class SphereCollider;


class CollisionManager final
{
	// エイリアス宣言
	using ColliderList = std::vector<Collider*>;
	using ColliderGroupList = std::unordered_map<std::string, ColliderList>;
	using CollisionGroup = std::pair<std::string, std::string>;
	using CollisionGroupList = std::list<CollisionGroup>;

public: // 基本

	CollisionManager();
	~CollisionManager();

public: // 関数

	void Add(const std::string& groupName, Collider* collider);
	void AllowCollision(const std::string& groupName1, const std::string& groupName2);
	void DetectCollision();
	void DetectCollision(const ColliderList& colliders);
	void DetectCollision(const ColliderList& colliders1, const ColliderList& colliders2);

	// 球と球の当たり判定
	static bool HitCheckSphereToSphere(const SphereCollider* collider1, const SphereCollider* collider2);

private: // 変数

	ColliderGroupList  m_colliderGroups;
	CollisionGroupList m_collisionGroups;
};
