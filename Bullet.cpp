#include "pch.h"

#include "Bullet.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

// �R���X�g���N�^
Bullet::Bullet(const Vector3& _pos, const float& _angle, const Vector3& _speed, const std::string& _tag)
	: GameObject(_tag)
	, m_isValid(true)
	, m_life(150.0f)
{
	m_position = _pos;
	m_velocity = _speed;
	m_rotate = Matrix::CreateRotationY(_angle);
	m_velocity = Vector3::Transform(m_velocity, m_rotate);
}

// ������
void Bullet::Initialize(GeometricPrimitive* _type)
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
	m_matrix = m_rotate * Matrix::CreateTranslation(Vector3(m_position));
}

// �`��
void Bullet::Render(const Matrix& _view)
{
	// �e�̕`��
	if (m_isValid)
		m_bullet->Draw(m_matrix, _view, GameContext::Get<Projection>()->GetMatrix(), Colors::Yellow);
}

// �㏈��
void Bullet::Finalize()
{
}