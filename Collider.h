#pragma once

#include <SimpleMath.h>
#include "GameObject.h"

class SphereCollider;
class BoxCollider;

// �`��
class Collider
{
public: // ��{

	// �R���X�g���N�^
	Collider(GameObject* _owner);
	// �f�X�g���N�^
	virtual ~Collider() = default;

public: // �A�N�Z�T

	// ���W�擾
	const DirectX::SimpleMath::Vector3 Collider::GetPosition() const
	{
		return m_owner->GetPosition() + m_offset;
	}

	// �I�t�Z�b�g�擾
	const DirectX::SimpleMath::Vector3 GetOffset() const
	{
		return m_offset;
	}

	// �I�t�Z�b�g�ݒ�
	void  SetOffset(const DirectX::SimpleMath::Vector3& _offset)
	{
		m_offset = _offset;
	}

public: // �֐�

	virtual bool IsCollided(const Collider*       _collider) const = 0;
	virtual bool IsCollided(const SphereCollider* _collider) const;
	virtual bool IsCollided(const BoxCollider*    _collider) const;

	// �Փ�
	void OnCollision(const Collider* _object) const;


protected: // �ϐ�

	// ������
	GameObject*                  m_owner;

	// �I�t�Z�b�g
	DirectX::SimpleMath::Vector3 m_offset;
};
