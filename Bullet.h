#pragma once

#include <SimpleMath.h>
#include <GeometricPrimitive.h>

#include "Projection.h"
#include "GameContext.h"
#include "GameObject.h"

// �e
class Bullet :public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Bullet(const DirectX::SimpleMath::Vector3& _pos, const float& _angle, const DirectX::SimpleMath::Vector3& _speed, const std::string& tag);
	// �f�X�g���N�^
	~Bullet() {}

public: // �A�N�Z�T

	// ���W�擾
	DirectX::SimpleMath::Vector3 GetPos() const
	{
		return m_position;
	}
	// ���W�ݒ�
	void SetPos(const DirectX::SimpleMath::Vector3& _pos)
	{
		m_position = _pos;
	}

	// �t���O�擾
	bool GetIsValid() const
	{
		return m_isValid;
	}
	// �t���O�ݒ�
	void SetIsValid(const bool& _flag)
	{
		m_isValid = _flag;
	}

	// ��s���Ԃ̎擾
	float GetLife() const
	{
		return m_life;
	}

public: // �֐�

	// ������
	void Initialize(DirectX::GeometricPrimitive* _type);
	// �X�V
	void Update() override;
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// �㏈��
	void Finalize();

private: // �ϐ�

	// �e�̌`��
	DirectX::GeometricPrimitive*	m_bullet;

	// ��]
	DirectX::SimpleMath::Matrix		m_rotate;

	// �t���O
	bool m_isValid;

	// ��s����
	float m_life;
};