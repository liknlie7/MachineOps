#pragma once

#include "Collider.h"

// ��
class SphereCollider : public Collider
{

public: // ��{

	// �R���X�g���N�^
	SphereCollider(GameObject* _owner, float _radius = 1.0f);
	// �f�X�g���N�^
	~SphereCollider() = default;

public: // �A�N�Z�T

	// ���a�擾
	float GetRadius() const
	{
		return m_radius;
	}

	// ���a�ݒ�
	void  SetRadius(float _radius)
	{
		m_radius = _radius;
	}

public: // �֐�

	bool IsCollided(const Collider*       _collider) const override;
	bool IsCollided(const SphereCollider* _collider) const override;
	bool IsCollided(const BoxCollider*    _collider) const override;

private: // �ϐ�

	// ���a
	float m_radius;
};