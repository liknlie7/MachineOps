#pragma once

#include <SimpleMath.h>

class GameObject
{
public:

	GameObject()
		:m_pos(0.0f, 0.0f, 0.0f)
		, m_vel(0.0f, 0.0f, 0.0f) {}

	virtual ~GameObject() {}

public:

	// �ʒu
	DirectX::SimpleMath::Vector3 m_pos;

	// ���x
	DirectX::SimpleMath::Vector3 m_vel;

	// �s��
	DirectX::SimpleMath::Matrix m_mat;
};

