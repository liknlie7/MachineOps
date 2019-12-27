#include "pch.h"

#include "Bullet.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

// コンストラクタ
Bullet::Bullet(Vector3 _pos, float _angle, Vector3 _speed)
	: m_isValid(true)
	, m_life(150.0f)
{
	m_pos = _pos;
	m_vel = _speed;
	Matrix rotate = Matrix::CreateRotationY(_angle);
	m_vel = Vector3::Transform(m_vel, rotate);
}

// 初期化
void Bullet::Initialize(GeometricPrimitive* _type)
{
	m_bullet = _type;
}

// 更新
void Bullet::Update()
{
	// 移動
	m_pos += m_vel;

	// 飛行時間を減らす
	m_life--;

	// 飛行時間がなくなったら
	if (m_life < 0)
	{
		m_isValid = false;
	}

	// 行列更新
	m_mat = Matrix::CreateTranslation(Vector3(m_pos));
}

// 描画
void Bullet::Render(const Matrix& _view)
{
	// 弾の描画
	if (m_isValid)
		m_bullet->Draw(m_mat, _view, GameContext::Get<Projection>()->GetMatrix(), Colors::Yellow);
}

// 後処理
void Bullet::Finalize()
{
}