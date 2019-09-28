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

	// à íu
	DirectX::SimpleMath::Vector3 m_pos;

	// ë¨ìx
	DirectX::SimpleMath::Vector3 m_vel;

	// çsóÒ
	DirectX::SimpleMath::Matrix m_mat;
};

