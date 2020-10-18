#include "pch.h"

#include "Bullet.h"

// �R���X�g���N�^
Bullet::Bullet()
	: m_isValid(true)
	, m_life(300.0f)
	, m_isUsed(false)
	, m_rotate(DirectX::SimpleMath::Matrix::Identity)
{

}

// ������
void Bullet::Initialize()
{

}

// �X�V
void Bullet::Update()
{
	if (m_isUsed)
	{
		// ��s���Ԃ����炷
		m_life--;

		// ��s���Ԃ��Ȃ��Ȃ�����
		if (m_life < 0)
		{
			m_isValid = false;
		}

		m_rotate = DirectX::SimpleMath::Matrix::CreateRotationY(m_angle);

		// �ړ�
		m_position += DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3::UnitZ * m_speed, m_rotate);


		// �s��X�V
		m_matrix = m_rotate * DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_position));
	}
}

// �X�V
//void Bullet::Update(const DirectX::SimpleMath::Vector3& _pos, const DirectX::SimpleMath::Vector3& _vel, const DirectX::SimpleMath::Matrix& _rotate)
//{
//	if (m_isUsed)
//	{
//		// �ړ�
//		m_position += m_velocity;
//
//		// ��s���Ԃ����炷
//		m_life--;
//
//		// ��s���Ԃ��Ȃ��Ȃ�����
//		if (m_life < 0)
//		{
//			m_isValid = false;
//		}
//
//		//m_rotate = DirectX::SimpleMath::Matrix::CreateRotationY(_angle);
//
//		m_velocity = DirectX::SimpleMath::Vector3::Transform(m_velocity, m_rotate);
//
//		// �s��X�V
//		m_matrix = m_rotate * DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3(m_position));
//	}
//}

// �`��
void Bullet::Render(const DirectX::SimpleMath::Matrix& _view)
{
	// �e�̕`��
	if (m_isUsed)
		m_pBulletGeometry->Draw(m_matrix, _view, GameContext::Get<Projection>()->GetMatrix(), DirectX::Colors::Yellow);
}

// �㏈��
void Bullet::Finalize()
{
}