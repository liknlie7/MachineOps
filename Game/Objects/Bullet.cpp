#include "../../pch.h"

#include "Bullet.h"
#include "../Common/DeviceResources.h"
#include "../Common/Projection.h"
#include "../Common/GameContext.h"

// ’e‚Ì¶‘¶ŽžŠÔ
const float Bullet::BULLET_LIFE = 300.0f;

// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
Bullet::Bullet()
	: m_life(BULLET_LIFE)
	, m_isUsed(false)
	, m_rotate(DirectX::SimpleMath::Matrix::Identity)
{

}
// XV
void Bullet::Update()
{
	// ’e‚ªŽg—p’†‚È‚ç
	if (m_isUsed)
	{
		// YŽ²‚Å‰ñ“]‚³‚¹‚é
		m_rotate = DirectX::SimpleMath::Matrix::CreateRotationY(m_angle);

		// ˆÚ“®
		m_position += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ * m_speed, m_rotate);

		// s—ñXV
		m_matrix = m_rotate * DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_position));
	}
}


// •`‰æ
void Bullet::Render(const DirectX::SimpleMath::Matrix& _view)
{
	// ’e‚Ì•`‰æ
	if (m_isUsed)
	{
		m_pBulletGeometry->Draw(m_matrix, _view, GameContext::Get<Projection>()->GetMatrix(), DirectX::Colors::Yellow);
	}
}