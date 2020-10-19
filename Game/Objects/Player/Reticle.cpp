#include "../../pch.h"

#include <mouse.h>

#include "Reticle.h"
#include "../../Common/DeviceResources.h"
#include "../../Common/GameContext.h"
#include "../../Common/Projection.h"
#include "../../Objects/FollowCamera.h"

// 照準の大きさ
const DirectX::SimpleMath::Vector2 Reticle::RETICLE_SCALE = DirectX::SimpleMath::Vector2(0.3f, 0.3f);

// コンストラクタ
Reticle::Reticle()
	: m_pos(DirectX::SimpleMath::Vector3::Zero)
{
	// テクスチャ取得
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Reticle.png", nullptr, m_reticle.GetAddressOf());
}

// 更新
void Reticle::Update()
{
	// マウス取得
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();
	m_state = DirectX::SimpleMath::Vector3((float)mouseState.x, (float)mouseState.y, 0);

	// Rayの作成
	m_pos = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3((float)m_state.x, (float)m_state.y, 0), GameContext::Get<FollowCamera>()->GetViewPort().Invert());
	DirectX::SimpleMath::Vector3 pointNear = DirectX::SimpleMath::Vector3(m_pos.x, m_pos.y, 0.0f);
	DirectX::SimpleMath::Vector3 pointFar = DirectX::SimpleMath::Vector3(m_pos.x, m_pos.y, 1.0f);
	DirectX::SimpleMath::Matrix inverseviewproj = (GameContext::Get<FollowCamera>()->GetViewMatrix() *  GameContext::Get<Projection>()->GetMatrix()).Invert();
	m_rayNear = DirectX::SimpleMath::Vector3::Transform(pointNear, inverseviewproj);
	m_rayFar = DirectX::SimpleMath::Vector3::Transform(pointFar, inverseviewproj);
}

void Reticle::Render()
{
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_reticle.Get(), DirectX::SimpleMath::Vector3(m_state.x, m_state.y, 0), nullptr, DirectX::Colors::LightYellow,
		0.0f, DirectX::SimpleMath::Vector2(64, 64), RETICLE_SCALE);
}