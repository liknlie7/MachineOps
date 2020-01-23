#pragma once

#include <SimpleMath.h>
#include <string>
#include <functional>

// �Q�[���I�u�W�F�N�g
class GameObject
{
public: // ��{

	// �R���X�g���N�^
	GameObject(const std::string& _tag = "GameObject");
	// �f�X�g���N�^
	virtual ~GameObject();

public: // �֐�

	// �X�V
	virtual void Update() = 0;
	// �`��
	virtual void Render(const DirectX::SimpleMath::Matrix& _view) = 0;
	// �Փ�
	virtual void OnCollision(GameObject* _object);

	// ������
	void Invalidate();
	// �L��
	bool IsValid() const;
	// ����
	bool IsInvalid() const;

	// �^�O�擾
	const std::string& GetTag() const;
	// ���W�擾
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	// ��]�擾
	const DirectX::SimpleMath::Vector3& GetRotation() const;
	// �傫���擾
	const DirectX::SimpleMath::Vector3& GetScale() const;

	// �^�O�ݒ�
	void SetTag(const std::string& _tag);
	// ���W�ݒ�
	void SetPosition(const DirectX::SimpleMath::Vector3& _position);
	// ��]�ݒ�
	void SetRotation(const DirectX::SimpleMath::Vector3& _rotation);
	// �傫���ݒ�
	void SetScale(const DirectX::SimpleMath::Vector3& _scale);

	// ����
	static void Destroy(GameObject* _object);

private: // �ϐ�

	// �L����
	bool m_isValid;
	// �^�O
	std::string m_tag;

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

// �^�O�擾
inline const std::string& GameObject::GetTag() const
{
	return m_tag;
}

// ���W�擾
inline const DirectX::SimpleMath::Vector3& GameObject::GetPosition() const
{
	return m_position;
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

// �^�O�ݒ�
inline void GameObject::SetTag(const std::string& _tag)
{
	m_tag = _tag;
}

// ���W�ݒ�
inline void GameObject::SetPosition(const DirectX::SimpleMath::Vector3& _position)
{
	m_position = _position;
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