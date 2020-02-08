#include "pch.h"
#include "WarningLine.h"

// エフェクト表示時間
const float WarningLine::DISPLAY_TIME = 1.0f;

WarningLine::WarningLine()
	: m_timer(0.0f)
{
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\WarningLine.png", nullptr, m_texture.GetAddressOf());
}

void WarningLine::Initialize()
{
	m_timer = DISPLAY_TIME;
}

void WarningLine::Update(float _elapsedTime)
{
	//// 時間になったらタスクは消える
	//m_timer -= elapsedTime;
	//if (m_timer <= 0.0f)
	//{

	//}

}

void WarningLine::Render()
{
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_texture.Get(), DirectX::SimpleMath::Vector2(0, 300), nullptr, DirectX::Colors::White,
		0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.0f, 1.0f));
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_texture.Get(), DirectX::SimpleMath::Vector2(0, 450), nullptr, DirectX::Colors::White,
		0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.0f, 1.0f));
}