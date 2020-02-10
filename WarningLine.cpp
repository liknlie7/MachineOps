#include "pch.h"
#include "WarningLine.h"

// エフェクト表示時間
const float WarningLine::DISPLAY_TIME = 1.0f;

// テクスチャ回転率
const float WarningLine::ROTATION = 0.0f;

// テクスチャ拡大率
const DirectX::SimpleMath::Vector2 WarningLine::MAGNIFICATION = DirectX::SimpleMath::Vector2(0.8f, 0.8f);

// 速度
const float WarningLine::SPEED = 2.0f;

// コンストラクタ
WarningLine::WarningLine()
	: m_timer(0.0f)
	, m_pos(0.0f, 0.0f)
{
}

// 初期化
void WarningLine::Initialize(DirectX::SimpleMath::Vector2 _pos, bool _dir)
{
	m_timer = DISPLAY_TIME;
	m_pos = _pos;
	m_dir = _dir;
}

// 更新
void WarningLine::Update(float _elapsedTime)
{
	//// 時間になったらタスクは消える
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

// 描画
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