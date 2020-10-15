#pragma once

#include <SimpleMath.h>
#include <string>
#include <functional>

// �Q�[���I�u�W�F�N�g
class GameObject
{
public: // ��{

	// �R���X�g���N�^
	GameObject();
	// �f�X�g���N�^
	virtual ~GameObject();

public: // �֐�

	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Render(const DirectX::SimpleMath::Matrix& _view) = 0;

	// ������
	void Invalidate();
	// �L��
	bool IsValid() const;
	// ����
	bool IsInvalid() const;

	// ���W�擾
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	// ���x�擾
	const DirectX::SimpleMath::Vector3& GetVelocity() const;
	// ��]�擾
	const DirectX::SimpleMath::Vector3& GetRotation() const;
	// �傫���擾
	const DirectX::SimpleMath::Vector3& GetScale() const;

	// ���W�ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& _position);
	// ���x�ݒ�
	void SetVelocity(const DirectX::SimpleMath::Vector3& _velocity);
	// ��]�ݒ�
	void SetRotation(const DirectX::SimpleMath::Vector3& _rotation);
	// �傫���ݒ�
	void SetScale(const DirectX::SimpleMath::Vector3& _scale);

	// ����
	static void Destroy(GameObject* _object);

private: // �ϐ�

	// �L����
	bool m_isValid;

protected: // �ϐ�

	// ���W
	DirectX::SimpleMath::Vector3 m_position;
	// ��]
	DirectX::SimpleMath::Vector3 m_rotation;
	// �傫��
	DirectX::SimpleMath::Vector3 m_scale;
	// �x�N�g��
	DirectX::SimpleMath::Vector3 m_velocity;
	// �s��
	DirectX::SimpleMath::Matrix m_matrix;


};

// �L��
inline bool GameObject::IsValid() const
{
	return m_isValid;
}

// ����
inline bool GameObject::IsInvalid() const
{
	return !m_isValid;
}

// ���W�擾
inline const DirectX::SimpleMath::Vector3& GameObject::GetPosition() const
{
	return m_position;
}

// ���x�擾
inline const DirectX::SimpleMath::Vector3& GameObject::GetVelocity() const
{
	return m_velocity;
}

// ��]�擾
inline const DirectX::SimpleMath::Vector3 & GameObject::GetRotation() const
{
	return m_rotation;
}

// �傫���擾
inline const DirectX::SimpleMath::Vector3 & GameObject::GetScale() const
{
	return m_scale;
}

// ���W�ݒ�
inline void GameObject::SetPosition(const DirectX::SimpleMath::Vector3& _position)
{
	m_position = _position;
}

// ���x�ݒ�
inline void GameObject::SetVelocity(const DirectX::SimpleMath::Vector3& _velocity)
{
	m_velocity = _velocity;
}

// ��]�ݒ�
inline void GameObject::SetRotation(const DirectX::SimpleMath::Vector3& _rotation)
{
	m_rotation = _rotation;
}

// �傫���ݒ�
inline void GameObject::SetScale(const DirectX::SimpleMath::Vector3& _scale)
{
	m_scale = _scale;
}

// ����
inline void GameObject::Destroy(GameObject * _object)
{
	_object->Invalidate();
}