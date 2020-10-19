#include "../../pch.h"

#include "../../Manager/ResourceManager.h"
#include "../../Common/DeviceResources.h"
#include "../../Common/GameContext.h"
#include "WarningEffect.h"

// マスク用カラー
const DirectX::SimpleMath::Vector4 WarningEffect::MASK_COLOR = DirectX::SimpleMath::Vector4(0.54f, 0.0f, 0.0f, 0.3f);

// メッセージ位置
const DirectX::SimpleMath::Vector2 WarningEffect::MESSAGE_POS = DirectX::SimpleMath::Vector2(280, 235);

// コンストラクタ
WarningEffect::WarningEffect()
	: m_maskColor(MASK_COLOR)
	, m_time(1.0f)
	, m_interval(2.5f)
{
	for (int i = 0; i < 2; i++)
		m_pLine[i] = std::make_unique<WarningLine>();
	m_pMessage = std::make_unique<WarningMessage>();

	// テクスチャデータを受け取る
	m_pTextures[LINE] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\WarningLine.png");
	m_pTextures[MESSAGE] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\WarningMessage.png");
	m_pTextures[ICON] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\WarningIcon.png");
	m_pTextures[MASK] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\Mask.png");
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
			m_pLine[i]->Render(m_pTextures[LINE].Get());
		m_pMessage->Render(m_pTextures[MESSAGE].Get(), MESSAGE_POS);
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_pTextures[ICON].Get(), DirectX::SimpleMath::Vector2(150, 250), nullptr, DirectX::Colors::White,
			0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.0f, 1.0f));
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_pTextures[ICON].Get(), DirectX::SimpleMath::Vector2(1000, 250), nullptr, DirectX::Colors::White,
			0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.0f, 1.0f));
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_pTextures[MASK].Get(), DirectX::SimpleMath::Vector2(0, 0), nullptr, m_maskColor,
			0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.0f, 1.0f));
	}
}

// エフェクト終わったら
bool WarningEffect::IsEnd()
{
	if (m_time == 0.0f)
		return true;
	return false;
}
