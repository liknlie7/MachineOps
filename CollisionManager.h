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
	// �G�C���A�X�錾
	using ColliderList = std::vector<Collider*>;
	using ColliderGroupList = std::unordered_map<std::string, ColliderList>;
	using CollisionGroup = std::pair<std::string, std::string>;
	using CollisionGroupList = std::list<CollisionGroup>;

public: // ��{

	CollisionManager();
	~CollisionManager();

public: // �֐�

	void Add(const std::string& groupName, Collider* collider);
	void AllowCollision(const std::string& groupName1, const std::string& groupName2);
	void DetectCollision();
	void DetectCollision(const ColliderList& colliders);
	void DetectCollision(const ColliderList& colliders1, const ColliderList& colliders2);

	// ���Ƌ��̓����蔻��
	static bool HitCheckSphereToSphere(const SphereCollider* collider1, const SphereCollider* collider2);

private: // �ϐ�

	ColliderGroupList  m_colliderGroups;
	CollisionGroupList m_collisionGroups;
};
