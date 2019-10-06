#include "pch.h"

#include "GameObject.h"



GameObject::GameObject()
	: m_pos(0.0f, 0.0f, 0.0f)
	, m_rot(0.0f, 0.0f, 0.0f)
	, m_scale(1.0f, 1.0f, 1.0f)
	, m_vel(0.0f, 0.0f, 0.0f)
{
}


GameObject::~GameObject()
{
}