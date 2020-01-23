#include "pch.h"

#include "GameObject.h"


// �R���X�g���N�^
GameObject::GameObject(const std::string& _tag)
	: m_isValid(true)
	, m_tag(_tag)
	, m_position(0.0f, 1.0f, 0.0f)
	, m_rotation(0.0f, 0.0f, 0.0f)
	, m_scale(1.0f, 1.0f, 1.0f)
	, m_velocity(0.0f, 0.0f, 0.0f)
{
}

// �f�X�g���N�^
GameObject::~GameObject()
{
}

void GameObject::OnCollision(GameObject * _object)
{
}

void GameObject::Invalidate()
{
	m_isValid = false;
}