#include "pch.h"
#include "HPGauge.h"

const float HPGauge::DEFAULT_GAUGE_SCALE_X = 1.0f;

HPGauge::HPGauge()
	: m_currentGaugeScaleX(0.0f)
	, m_prevGaugeScaleX(0.0f)
	, m_lightGreenGaugeRate(0.0f)
	, m_totalTime(0.0f)
	, m_gaugeFlag(false)
{
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\GreenHP.png", nullptr, m_greenHpBarTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\RedHP.png", nullptr, m_redHpBarTexture.GetAddressOf());
}

void HPGauge::Update()
{
	//// エネミーの体力の比率計算
	//float greenGaugeRate = m_pEnemy->GetLife() / m_pEnemy->GetMaxLife();
	//// 現在のゲージサイズ
	//m_currentGaugeScaleX = m_defaultGaugeScaleX * greenGaugeRate;

}

//// 経過時間
//m_totalTime += (float)_timer.GetElapsedSeconds();
//if (m_totalTime < DAMAGE_TIME)
//{
//	float time = m_totalTime / DAMAGE_TIME;
//	m_lightGreenGaugeRate = Lerp(m_prevGaugeScaleX, m_currentGaugeScaleX, time);
//	m_gaugeFlag = false;
//
//}
//else
//{
//	m_totalTime = 0;
//	m_gaugeFlag = true;
//}
//if (m_gaugeFlag)
//{
//	m_prevGaugeScaleX = m_currentGaugeScaleX;
//}


//GameContext::Get<SpriteBatch>()->Begin(SpriteSortMode_Deferred, GameContext::Get<CommonStates>()->NonPremultiplied());
//// 赤ゲージ表示
//GameContext::Get<DirectX::SpriteBatch>()->Draw(m_redHpBarTexture.Get(), DirectX::SimpleMath::Vector2(350, 596), nullptr, Colors::White,
//	0.0f, Vector2::Zero, Vector2(1.0f, 0.2f));
//// 薄緑ゲージ表示
//GameContext::Get<DirectX::SpriteBatch>()->Draw(m_greenHpBarTexture.Get(), DirectX::SimpleMath::Vector2(350, 600), nullptr, Vector4(1.0f, 1.0f, 1.0f, 0.5f),
//	0.0f, Vector2::Zero, Vector2(m_lightGreenGaugeRate, 0.2f));
//// 緑ゲージ表示
//GameContext::Get<DirectX::SpriteBatch>()->Draw(m_greenHpBarTexture.Get(), DirectX::SimpleMath::Vector2(350, 600), nullptr, Colors::White,
//	0.0f, Vector2::Zero, Vector2(m_currentGaugeScaleX, 0.2f));
//
//GameContext::Get<SpriteBatch>()->End();


HPGauge::~HPGauge()
{
}

void HPGauge::Render()
{
}

// 線形補間
//float HPGauge::Lerp(float _start, float _end, float _time)
//{
//	return _start + (_end - _start) * _time;
//}
