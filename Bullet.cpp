#include "pch.h"

#include "Bullet.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

// �e�X�s�[�h���`
const Vector3 Bullet::SPEED(0.0f, 0.0f, 0.3f);

// �R���X�g���N�^
Bullet::Bullet(Vector3 _pos, float _angle)
	: GameObject("Bullet")
	, m_hitFlag(false)
{
	m_pos = _pos;
	m_vel = SPEED;
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

	m_mat = Matrix::CreateTranslation(Vector3(m_pos));
}

// �`��
void Bullet::Render(const Matrix& _view)
{
	Projection* proj = GameContext<Projection>().Get();
	m_bullet->Draw(m_mat, _view, proj->GetMatrix(), Colors::Yellow);
}

// �㏈��
void Bullet::Finalize()
{
}

// �Փ˂�����
void Bullet::OnCollision(GameObject* object)
{
	Destroy(this);
}