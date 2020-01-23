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

// �Փ˔���
class CollisionManager final
{
	// using�錾
	using ColliderList = std::vector<Collider*>;
	using ColliderGroupList = std::unordered_map<std::string, ColliderList>;
	using CollisionGroup = std::pair<std::string, std::string>;
	using CollisionGroupList = std::list<CollisionGroup>;

public: // ��{

	// �R���X�g���N�^
	CollisionManager();
	// �f�X�g���N�^
	~CollisionManager();

public: // �֐�

	// �ǉ�
	void Add(const std::string& _groupName, Collider* _collider);
	void Add(const std::string& _groupName, SphereCollider* _sphereCollider);

	// �Փ˒T�m
	void AllowCollision(const std::string& _groupName1, const std::string& _groupName2);

	// �Փˌ��o
	void DetectCollision();
	void DetectCollision(const ColliderList& _colliders);
	void DetectCollision(const ColliderList& _colliders1, const ColliderList& _colliders2);

	// �����m�̏Փ˔���
	static bool IsCollided(const SphereCollider* _collider1, const SphereCollider* _collider2);

	// �{�b�N�X���m�̏Փ˔���
	//static bool IsCollided(const BoxCollider*    _collider1, const BoxCollider*    _collider2);
	
	// �{�b�N�X�Ƌ��̏Փ˔���
	static bool IsCollided(const SphereCollider* _collider1, const BoxCollider*    _collider2);
	//static bool IsCollided(const BoxCollider*    _collider1, const SphereCollider* _collider2);

private: // �T�u�֐�

	// �_�ƃ{�b�N�X�̊Ԃ̍ŒZ�����̕������v�Z����֐�
	static float SqDistPointBox(const DirectX::SimpleMath::Vector3& _point, const BoxCollider* _box);


private: // �ϐ�

	// �`��p
	ColliderGroupList  m_colliderGroups;
	// �Փ˗p
	CollisionGroupList m_collisionGroups;
};
