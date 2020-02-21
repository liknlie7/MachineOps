#include "pch.h"

#include "Bullet.h"

// �R���X�g���N�^
Bullet::Bullet(const DirectX::SimpleMath::Vector3& _pos, const float& _angle, const DirectX::SimpleMath::Vector3& _speed, const std::string& _tag)
	: GameObject(_tag)
	, m_isValid(true)
	, m_life(300.0f)
{
	m_position = _pos;
	m_velocity = _speed;
	m_rotate = DirectX::SimpleMath::Matrix::CreateRotationY(_angle);
	m_velocity = DirectX::SimpleMath::Vector3::Transform(m_velocity, m_rotate);
}

// ������
void Bullet::Initialize(DirectX::GeometricPrimitive* _type)
{
	m_bullet = _type;
}

// �X�V
void Bullet::Update()
{
	// �ړ�
	m_position += m_velocity;

	// ��s���Ԃ����炷
	m_life--;

	// ��s���Ԃ��Ȃ��Ȃ�����
	if (m_life < 0)
	{
		m_isValid = false;
	}

	// �s��X�V
	m_matrix = m_rotate * DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_position));
}

// �`��
void Bullet::Render(const DirectX::SimpleMath::Matrix& _view)
{
	// �e�̕`��
	if (m_isValid)
		m_bullet->Draw(m_matrix, _view, GameContext::Get<Projection>()->GetMatrix(), DirectX::Colors::Yellow);
}

// �㏈��
void Bullet::Finalize()
{
}