#include "../../pch.h"

#include "../../Common/GameContext.h"
#include "WarningMessage.h"

// エフェクト表示時間
const float WarningMessage::DISPLAY_TIME = 1.0f;

// テクスチャ回転率
const float WarningMessage::ROTATION = 0.0f;

// テクスチャ拡大率
const DirectX::SimpleMath::Vector2 WarningMessage::MAGNIFICATION = DirectX::SimpleMath::Vector2(1.0f, 1.0f);

// フェードスピード
const float WarningMessage::FADE_SPEED = 0.025f;

// コンストラクタ
WarningMessage::WarningMessage()
	: m_timer(0.0f)
	, m_alpha(1.0f)
	, m_fadeType(false)

{
}

// 初期化
void WarningMessage::Initialize()
{
	m_timer = DISPLAY_TIME;
}

// 更新
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

// 描画
void WarningMessage::Render(ID3D11ShaderResourceView * _texture, DirectX::SimpleMath::Vector2 _pos)
{
	GameContext::Get<DirectX::SpriteBatch>()->Draw(_texture, _pos, nullptr, DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, m_alpha),
		ROTATION, DirectX::SimpleMath::Vector2::Zero, MAGNIFICATION);
}
