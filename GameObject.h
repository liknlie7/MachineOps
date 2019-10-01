#pragma once


#include <SimpleMath.h>
#include <string>
#include <functional>

#include "Collider.h"



class GameObject
{
private:
	bool        m_isValid;
	std::string m_tag;


protected:
	DirectX::SimpleMath::Vector3 m_pos;
	DirectX::SimpleMath::Vector3 m_rot;
	DirectX::SimpleMath::Vector3 m_scale;
	DirectX::SimpleMath::Vector3 m_vel;
	DirectX::SimpleMath::Matrix m_mat;

public:
	GameObject(const std::string& tag = "GameObject");

public:
	virtual ~GameObject();


public:
	virtual void Update() = 0;
	virtual void Render(const DirectX::SimpleMath::Matrix& _view) = 0;

	virtual void OnCollision(GameObject* object);


public:
	void Invalidate();
	bool IsValid() const;
	bool IsInvalid() const;

	const std::string& GetTag() const;
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	const DirectX::SimpleMath::Vector3& GetRotation() const;
	const DirectX::SimpleMath::Vector3& GetScale() const;

	void SetTag(const std::string& tag);
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


inline const std::string& GameObject::GetTag() const
{
	return m_tag;
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

inline void GameObject::SetTag(const std::string& tag)
{
	m_tag = tag;
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