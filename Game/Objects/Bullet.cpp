#include "../../pch.h"

#include "Bullet.h"
#include "../Common/DeviceResources.h"
#include "../Common/Projection.h"
#include "../Common/GameContext.h"

// 弾の生存時間
const float Bullet::BULLET_LIFE = 300.0f;

// コンストラクタ
Bullet::Bullet()
	: m_life(BULLET_LIFE)
	, m_isUsed(false)
	, m_rotate(DirectX::SimpleMath::Matrix::Identity)
{

}
// 更新
void Bullet::Update()
{
	// 弾が使用中なら
	if (m_isUsed)
	{
		// Y軸で回転させる
		m_rotate = DirectX::SimpleMath::Matrix::CreateRotationY(m_angle);

		// 移動
		m_position += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ * m_speed, m_rotate);

		// 行列更新
		m_matrix = m_rotate * DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_position));
	}
}


// 描画
void Bullet::Render(const DirectX::SimpleMath::Matrix& _view)
{
	// 弾の描画
	if (m_isUsed)
	{
		m_pBulletGeometry->Draw(m_matrix, _view, GameContext::Get<Projection>()->GetMatrix(), DirectX::Colors::Yellow);
	}
}