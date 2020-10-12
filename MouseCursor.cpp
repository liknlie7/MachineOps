#include "pch.h"

#include "MouseCursor.h"


// コンストラクタ
MouseCursor::MouseCursor()
	: m_pos(DirectX::SimpleMath::Vector3(0, 0, 0))
{
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Reticle.png", nullptr, m_reticle.GetAddressOf());

}

// 更新
void MouseCursor::Update()
{
	DirectX::Mouse::State mouseState = DirectX::Mouse::Get().GetState();
	m_state = DirectX::SimpleMath::Vector3((float)mouseState.x, (float)mouseState.y, 0);

	// Rayの作成
	m_pos = DirectX::SimpleMath::Vector3::Transform(DirectX::SimpleMath::Vector3((float)m_state.x, (float)m_state.y, 0), GameContext::Get<FollowCamera>()->GetViewPort().Invert());
	DirectX::SimpleMath::Vector3 pointNear = DirectX::SimpleMath::Vector3(m_pos.x, m_pos.y, 0.0f);
	DirectX::SimpleMath::Vector3 pointFar = DirectX::SimpleMath::Vector3(m_pos.x, m_pos.y, 1.0f);
	DirectX::SimpleMath::Matrix inverseviewproj = (GameContext::Get<FollowCamera>()->GetViewMatrix() *  GameContext::Get<Projection>()->GetMatrix()).Invert();
	m_rayNear = DirectX::SimpleMath::Vector3::Transform(pointNear, inverseviewproj);
	m_rayFar = DirectX::SimpleMath::Vector3::Transform(pointFar, inverseviewproj);
	//Vector3 raySubtraction = rayFar - rayNear;
	//Vector3 rayDirection = raySubtraction;
	//// 正規化
	//rayDirection.Normalize();

}

void MouseCursor::Render()
{
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_reticle.Get(), DirectX::SimpleMath::Vector3(m_state.x, m_state.y, 0), nullptr, DirectX::Colors::LightYellow,
		0.0f, DirectX::SimpleMath::Vector2(64, 64), DirectX::SimpleMath::Vector2(0.3f, 0.3f));
}
