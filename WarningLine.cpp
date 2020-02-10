#include "pch.h"
#include "WarningLine.h"

// �G�t�F�N�g�\������
const float WarningLine::DISPLAY_TIME = 1.0f;

// �e�N�X�`����]��
const float WarningLine::ROTATION = 0.0f;

// �e�N�X�`���g�嗦
const DirectX::SimpleMath::Vector2 WarningLine::MAGNIFICATION = DirectX::SimpleMath::Vector2(0.8f, 0.8f);

// ���x
const float WarningLine::SPEED = 2.0f;

// �R���X�g���N�^
WarningLine::WarningLine()
	: m_timer(0.0f)
	, m_pos(0.0f, 0.0f)
{
}

// ������
void WarningLine::Initialize(DirectX::SimpleMath::Vector2 _pos, bool _dir)
{
	m_timer = DISPLAY_TIME;
	m_pos = _pos;
	m_dir = _dir;
}

// �X�V
void WarningLine::Update(float _elapsedTime)
{
	//// ���ԂɂȂ�����^�X�N�͏�����
	//m_timer -= elapsedTime;
	//if (m_timer <= 0.0f)
	//{

	//}

	if (m_dir)
	{
		m_pos.x += SPEED;
	}
	else
	{
		m_pos.x -= SPEED;
	}

}

// �`��
void WarningLine::Render(ID3D11ShaderResourceView* _texture)
{
	GameContext::Get<DirectX::SpriteBatch>()->Draw(_texture, m_pos, nullptr, DirectX::Colors::White,
		ROTATION, DirectX::SimpleMath::Vector2::Zero, MAGNIFICATION);

	if (m_dir)
		GameContext::Get<DirectX::SpriteBatch>()->Draw(_texture, m_pos, nullptr, DirectX::Colors::White,
			ROTATION, DirectX::SimpleMath::Vector2(2050, 0), MAGNIFICATION);
	else
		GameContext::Get<DirectX::SpriteBatch>()->Draw(_texture, m_pos, nullptr, DirectX::Colors::White,
			ROTATION, DirectX::SimpleMath::Vector2(-2050, 0), MAGNIFICATION);


}