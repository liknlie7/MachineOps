#include "../../pch.h"

#include "Bullet.h"
#include "../Common/DeviceResources.h"
#include "../Common/Projection.h"
#include "../Common/GameContext.h"

// �e�̐�������
const float Bullet::BULLET_LIFE = 300.0f;

// �R���X�g���N�^
Bullet::Bullet()
	: m_life(BULLET_LIFE)
	, m_isUsed(false)
	, m_rotate(DirectX::SimpleMath::Matrix::Identity)
{

}
// �X�V
void Bullet::Update()
{
	// �e���g�p���Ȃ�
	if (m_isUsed)
	{
		// Y���ŉ�]������
		m_rotate = DirectX::SimpleMath::Matrix::CreateRotationY(m_angle);

		// �ړ�
		m_position += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ * m_speed, m_rotate);

		// �s��X�V
		m_matrix = m_rotate * DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_position));
	}
}


// �`��
void Bullet::Render(const DirectX::SimpleMath::Matrix& _view)
{
	// �e�̕`��
	if (m_isUsed)
	{
		m_pBulletGeometry->Draw(m_matrix, _view, GameContext::Get<Projection>()->GetMatrix(), DirectX::Colors::Yellow);
	}
}