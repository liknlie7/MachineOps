#include "pch.h"

#include "Bullet.h"

// コンストラクタ
Bullet::Bullet()
	: m_isValid(true)
	, m_life(300.0f)
	, m_isUsed(false)
	, m_rotate(DirectX::SimpleMath::Matrix::Identity)
{

}

// 初期化
void Bullet::Initialize()
{

}

// 更新
void Bullet::Update()
{
	if (m_isUsed)
	{
		// 飛行時間を減らす
		m_life--;

		// 飛行時間がなくなったら
		if (m_life < 0)
		{
			m_isValid = false;
		}

		m_rotate = DirectX::SimpleMath::Matrix::CreateRotationY(m_angle);

		// 移動
		m_position += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ * m_speed, m_rotate);


		// 行列更新
		m_matrix = m_rotate * DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_position));
	}
}

// 更新
//void Bullet::Update(const DirectX::SimpleMath::Vector3& _pos, const DirectX::SimpleMath::Vector3& _vel, const DirectX::SimpleMath::Matrix& _rotate)
//{
//	if (m_isUsed)
//	{
//		// 移動
//		m_position += m_velocity;
//
//		// 飛行時間を減らす
//		m_life--;
//
//		// 飛行時間がなくなったら
//		if (m_life < 0)
//		{
//			m_isValid = false;
//		}
//
//		//m_rotate = DirectX::SimpleMath::Matrix::CreateRotationY(_angle);
//
//		m_velocity = DirectX::SimpleMath::Vector3::Transform(m_velocity, m_rotate);
//
//		// 行列更新
//		m_matrix = m_rotate * DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_position));
//	}
//}

// 描画
void Bullet::Render(const DirectX::SimpleMath::Matrix& _view)
{
	// 弾の描画
	if (m_isUsed)
		m_pBulletGeometry->Draw(m_matrix, _view, GameContext::Get<Projection>()->GetMatrix(), DirectX::Colors::Yellow);
}

// 後処理
void Bullet::Finalize()
{
}