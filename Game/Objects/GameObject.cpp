#include "../../pch.h"

#include "GameObject.h"


// コンストラクタ
GameObject::GameObject()
	: m_isValid(true)
	, m_position(0.0f, 1.0f, 0.0f)
	, m_rotation(0.0f, 0.0f, 0.0f)
	, m_scale(1.0f, 1.0f, 1.0f)
	, m_velocity(0.0f, 0.0f, 0.0f)
{
}

// デストラクタ
GameObject::~GameObject()
{
}

void GameObject::Invalidate()
{
	m_isValid = false;
}