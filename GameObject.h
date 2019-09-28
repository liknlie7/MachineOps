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

	// 位置
	DirectX::SimpleMath::Vector3 m_pos;

	// 速度
	DirectX::SimpleMath::Vector3 m_vel;

	// 行列
	DirectX::SimpleMath::Matrix m_mat;
};

