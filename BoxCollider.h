#pragma once

#include "Collider.h"

// �{�b�N�X
class BoxCollider : public Collider
{
public: // ��{

	// �R���X�g���N�^
	BoxCollider(GameObject* _owner, const DirectX::SimpleMath::Vector3& _size = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
	// �f�X�g���N�^
	~BoxCollider() = default;

public: // �A�N�Z�T

	// �T�C�Y�擾
	const DirectX::SimpleMath::Vector3& GetSize() const
	{
		return m_size;
	}

	// �T�C�Y�ݒ�
	void SetSize(const DirectX::SimpleMath::Vector3& _size)
	{
		m_size = _size;
	}

public: // �֐�

	bool IsCollided(const Collider*       _collider) const override;
	bool IsCollided(const SphereCollider* _collider) const override;
	//bool IsCollided(const BoxCollider*    _collider) const override;

private: // �ϐ�

	// �T�C�Y
	DirectX::SimpleMath::Vector3 m_size;

};
