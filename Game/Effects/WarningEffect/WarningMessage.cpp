#include "../../pch.h"

#include "../../Common/GameContext.h"
#include "WarningMessage.h"

// �G�t�F�N�g�\������
const float WarningMessage::DISPLAY_TIME = 1.0f;

// �e�N�X�`����]��
const float WarningMessage::ROTATION = 0.0f;

// �e�N�X�`���g�嗦
const DirectX::SimpleMath::Vector2 WarningMessage::MAGNIFICATION = DirectX::SimpleMath::Vector2(1.0f, 1.0f);

// �t�F�[�h�X�s�[�h
const float WarningMessage::FADE_SPEED = 0.025f;

// �R���X�g���N�^
WarningMessage::WarningMessage()
	: m_timer(0.0f)
	, m_alpha(1.0f)
	, m_fadeType(false)

{
}

// ������
void WarningMessage::Initialize()
{
	m_timer = DISPLAY_TIME;
}

// �X�V
void WarningMessage::Update(float _elapsedTime)
{
	if (m_fadeType == false)
	{
		m_alpha -= FADE_SPEED;
	}
	else
	{
		m_alpha += FADE_SPEED;
	}

	if (m_alpha >= 1.0f)
	{
		m_fadeType = false;
	}
	else if (m_alpha <= 0.1f)
	{
		m_fadeType = true;
	}
}

// �`��
void WarningMessage::Render(ID3D11ShaderResourceView * _texture, DirectX::SimpleMath::Vector2 _pos)
{
	GameContext::Get<DirectX::SpriteBatch>()->Draw(_texture, _pos, nullptr, DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, m_alpha),
		ROTATION, DirectX::SimpleMath::Vector2::Zero, MAGNIFICATION);
}
