#include "pch.h"
#include "WarningEffect.h"

// コンストラクタ
WarningEffect::WarningEffect()
	: m_maskColor(DirectX::SimpleMath::Vector4(0.54f, 0.0f, 0.0f, 0.3f))
	, m_time(1.0f)
	, m_interval(2.5f)
{
	for (int i = 0; i < 2; i++)
		m_pLine[i] = std::make_unique<WarningLine>();
	m_pMessage = std::make_unique<WarningMessage>();

	// テクスチャの読み込み
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\WarningLine.png", nullptr, m_lineTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\WarningMessage.png", nullptr, m_messageTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\WarningIcon.png", nullptr, m_iconTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Mask.png", nullptr, m_maskTexture.GetAddressOf());
}

// 初期化
void WarningEffect::Initialize()
{
	m_pLine[0]->Initialize(DirectX::SimpleMath::Vector2(0, 450), true);
	m_pLine[1]->Initialize(DirectX::SimpleMath::Vector2(0, 150), false);
	m_pMessage->Initialize();
}

// 更新
void WarningEffect::Update(float _elapsedTime)
{
	for (int i = 0; i < 2; i++)
		m_pLine[i]->Update(_elapsedTime);
	m_pMessage->Update(_elapsedTime);

	m_time -= _elapsedTime / m_interval;

	if (m_time < 0.0f)
		m_time = 0.0f;
}

// 描画
void WarningEffect::Render()
{
	if (m_time != 0)
	{
		for (int i = 0; i < 2; i++)
			m_pLine[i]->Render(m_lineTexture.Get());
		m_pMessage->Render(m_messageTexture.Get(), DirectX::SimpleMath::Vector2(280, 235));
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_iconTexture.Get(), DirectX::SimpleMath::Vector2(150, 250), nullptr, DirectX::Colors::White,
			0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.0f, 1.0f));
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_iconTexture.Get(), DirectX::SimpleMath::Vector2(1000, 250), nullptr, DirectX::Colors::White,
			0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.0f, 1.0f));
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_maskTexture.Get(), DirectX::SimpleMath::Vector2(0, 0), nullptr, m_maskColor,
			0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.0f, 1.0f));
	}
}

bool WarningEffect::IsEnd()
{
	if (m_time == 0.0f)
		return true;
	return false;
}
