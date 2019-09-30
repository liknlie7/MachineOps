#pragma once


#include <SimpleMath.h>

#include "GameObject.h"
#include "Collider.h"

class GameObject;
class SphereCollider;
class BoxCollider;


class Collider
{
public: // ��{

	// �R���X�g���N�^
	Collider(GameObject* owner);
	// �f�X�g���N�^
	virtual ~Collider() = default;

public: // �A�N�Z�T

	// ���W�擾
	const DirectX::SimpleMath::Vector3 Collider::GetPosition() const
	{
		return m_owner->GetPosition() + m_offset;
	}

	// �␳�l�̎擾
	const DirectX::SimpleMath::Vector3 Collider::GetOffset() const
	{
		return m_offset;
	}

	// �␳�l�̐ݒ�
	void Collider::SetOffset(const DirectX::SimpleMath::Vector3 & offset)
	{
		m_offset = offset;
	}

public: // �֐�

	virtual bool IsCollided(const Collider*       collider) const = 0;
	virtual bool IsCollided(const SphereCollider* collider) const;
	virtual bool IsCollided(const BoxCollider*    collider) const;

	void OnCollision(const Collider* object) const;

protected: // �ϐ�

	// ������
	GameObject*                  m_owner;
	// �␳�l
	DirectX::SimpleMath::Vector3 m_offset;

};