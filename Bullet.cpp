#include "pch.h"

#include "Bullet.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

// コンストラクタ
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

// 初期化
void Bullet::Initialize(GeometricPrimitive* _type)
{
	m_bullet = _type;
}

// 更新
void Bullet::Update()
{
	// 移動
	m_position += m_velocity;

	// 飛行時間を減らす
	m_life--;

	// 飛行時間がなくなったら
	if (m_life < 0)
	{
		m_isValid = false;
	}

	// 行列更新
	m_matrix = m_rotate * Matrix::CreateTranslation(Vector3(m_position));
}

// 描画
void Bullet::Render(const Matrix& _view)
{
	// 弾の描画
	if (m_isValid)
		m_bullet->Draw(m_matrix, _view, GameContext::Get<Projection>()->GetMatrix(), Colors::Yellow);
}

// 後処理
void Bullet::Finalize()
{
}