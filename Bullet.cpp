#include "pch.h"

#include "Bullet.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

// 弾スピードを定義する
const Vector3 Bullet::SPEED(0.0f, 0.0f, 0.3f);

// コンストラクタ
Bullet::Bullet(Vector3 _pos, float _angle)
	:m_vel(SPEED)
	, m_pos(_pos)
	, m_hitFlag(false)
{
	Matrix rotate = Matrix::CreateRotationY(_angle);
	m_vel = Vector3::Transform(m_vel, rotate);

}

// 初期化
void Bullet::Initialize(GeometricPrimitive* _type)
{
	m_bullet = _type;
}

// 更新
void Bullet::Update(float _angle)
{
	// 移動する
	m_pos += m_vel;

	m_matrix = Matrix::CreateTranslation(Vector3(m_pos));
}

// 描画
void Bullet::Render(Matrix _view)
{
	Projection* proj = GameContext<Projection>().Get();
	m_bullet->Draw(m_matrix, _view, proj->GetMatrix(), Colors::Yellow);
}

// 後処理
void Bullet::Finalize()
{
}