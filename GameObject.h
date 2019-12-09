#pragma once


#include <SimpleMath.h>
#include <string>
#include <functional>

#include "StepTimer.h"

class GameObject
{
private:
	bool m_isValid;

protected:
	DirectX::SimpleMath::Vector3 m_pos;
	DirectX::SimpleMath::Vector3 m_rot;
	DirectX::SimpleMath::Vector3 m_scale;
	DirectX::SimpleMath::Vector3 m_vel;
	DirectX::SimpleMath::Matrix m_mat;

public:
	GameObject();
	virtual ~GameObject();


public:
	virtual void Update(DX::StepTimer const& timer) = 0;
	virtual void Render(const DirectX::SimpleMath::Matrix& _view) = 0;

public:

	void Invalidate();
	bool IsValid() const;
	bool IsInvalid() const;

	const DirectX::SimpleMath::Vector3& GetPosition() const;
	const DirectX::SimpleMath::Vector3& GetRotation() const;
	const DirectX::SimpleMath::Vector3& GetScale() const;

	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation);
	void SetScale(const DirectX::SimpleMath::Vector3& scale);

public:
	static void Destroy(GameObject* object);

};


inline bool GameObject::IsValid() const
{
	return m_isValid;
}


inline bool GameObject::IsInvalid() const
{
	return !m_isValid;
}


inline const DirectX::SimpleMath::Vector3& GameObject::GetPosition() const
{
	return m_pos;
}


inline const DirectX::SimpleMath::Vector3 & GameObject::GetRotation() const
{
	return m_rot;
}


inline const DirectX::SimpleMath::Vector3 & GameObject::GetScale() const
{
	return m_scale;
}


inline void GameObject::SetPosition(const DirectX::SimpleMath::Vector3& position)
{
	m_pos = position;
}


inline void GameObject::SetRotation(const DirectX::SimpleMath::Vector3& rotation)
{
	m_rot = rotation;
}


inline void GameObject::SetScale(const DirectX::SimpleMath::Vector3& scale)
{
	m_scale = scale;
}


inline void GameObject::Destroy(GameObject * object)
{
	object->Invalidate();
}