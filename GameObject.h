#pragma once


#include <SimpleMath.h>
#include <string>
#include <functional>

class GameObject
{
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
	virtual void Update() = 0;
	virtual void Render(const DirectX::SimpleMath::Matrix& _view) = 0;

public:
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	const DirectX::SimpleMath::Vector3& GetRotation() const;
	const DirectX::SimpleMath::Vector3& GetScale() const;

	void SetPosition(const DirectX::SimpleMath::Vector3& position);
	void SetRotation(const DirectX::SimpleMath::Vector3& rotation);
	void SetScale(const DirectX::SimpleMath::Vector3& scale);
};

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