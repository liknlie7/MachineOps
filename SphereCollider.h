#pragma once


#include "Collider.h"


// ��
class SphereCollider : public Collider
{
public: // ��{

	// �R���X�g���N�^
	SphereCollider(GameObject* owner, float radius = 1.0f);
	// �f�X�g���N�^
	~SphereCollider() = default;

public: // �֐�

	bool IsCollided(const Collider*       collider) const override;
	bool IsCollided(const SphereCollider* collider) const override;

	// ���a�擾
	float GetRadius() const;
	// ���a�ݒ�
	void  SetRadius(float radius);

private: // �ϐ�

	// ���a
	float m_radius;
};