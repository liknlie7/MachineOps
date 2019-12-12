#include "pch.h"

#include "Bullet.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

// �R���X�g���N�^
Bullet::Bullet(Vector3 _pos, float _angle, Vector3 _speed)
	: m_isValid(true)
	, m_life(10.0f)
{
	m_pos = _pos;
	m_vel = _speed;
	Matrix rotate = Matrix::CreateRotationY(_angle);
	m_vel = Vector3::Transform(m_vel, rotate);
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
	m_pos += m_vel;

	m_life--;

	m_mat = Matrix::CreateTranslation(Vector3(m_pos));
}

// �`��
void Bullet::Render(const Matrix& _view)
{
	m_bullet->Draw(m_mat, _view, GameContext::Get<Projection>()->GetMatrix(), Colors::Yellow);
}

// �㏈��
void Bullet::Finalize()
{
}

// �Փ˂�����
void Bullet::OnCollision()
{
	
}