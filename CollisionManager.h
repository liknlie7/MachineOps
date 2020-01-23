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
class BoxCollider;

// 衝突判定
class CollisionManager final
{
	// using宣言
	using ColliderList = std::vector<Collider*>;
	using ColliderGroupList = std::unordered_map<std::string, ColliderList>;
	using CollisionGroup = std::pair<std::string, std::string>;
	using CollisionGroupList = std::list<CollisionGroup>;

public: // 基本

	// コンストラクタ
	CollisionManager();
	// デストラクタ
	~CollisionManager();

public: // 関数

	// 追加
	void Add(const std::string& _groupName, Collider* _collider);
	void Add(const std::string& _groupName, SphereCollider* _sphereCollider);

	// 衝突探知
	void AllowCollision(const std::string& _groupName1, const std::string& _groupName2);

	// 衝突検出
	void DetectCollision();
	void DetectCollision(const ColliderList& _colliders);
	void DetectCollision(const ColliderList& _colliders1, const ColliderList& _colliders2);

	// 球同士の衝突判定
	static bool IsCollided(const SphereCollider* _collider1, const SphereCollider* _collider2);

	// ボックス同士の衝突判定
	//static bool IsCollided(const BoxCollider*    _collider1, const BoxCollider*    _collider2);
	
	// ボックスと球の衝突判定
	static bool IsCollided(const SphereCollider* _collider1, const BoxCollider*    _collider2);
	//static bool IsCollided(const BoxCollider*    _collider1, const SphereCollider* _collider2);

private: // サブ関数

	// 点とボックスの間の最短距離の平方を計算する関数
	static float SqDistPointBox(const DirectX::SimpleMath::Vector3& _point, const BoxCollider* _box);


private: // 変数

	// 形状用
	ColliderGroupList  m_colliderGroups;
	// 衝突用
	CollisionGroupList m_collisionGroups;
};
