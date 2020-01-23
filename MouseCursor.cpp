#include "pch.h"

#include "MouseCursor.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// コンストラクタ
MouseCursor::MouseCursor(const std::string& _tag)
	: GameObject(_tag)
	, m_pos(Vector3(0, 0, 0))
{
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Reticle.png", nullptr, m_reticle.GetAddressOf());

}

// 更新
void MouseCursor::Update()
{
	Mouse::State mouseState = Mouse::Get().GetState();
	m_state = Vector3(mouseState.x, mouseState.y, 0);

	// Rayの作成
	m_pos = Vector3::Transform(Vector3((float)m_state.x, (float)m_state.y, 0), GameContext::Get<FollowCamera>()->GetViewPort().Invert());
	Vector3 pointNear = Vector3(m_pos.x, m_pos.y, 0.0f);
	Vector3 pointFar = Vector3(m_pos.x, m_pos.y, 1.0f);
	Matrix inverseviewproj = (GameContext::Get<FollowCamera>()->GetViewMatrix() *  GameContext::Get<Projection>()->GetMatrix()).Invert();
	m_rayNear = Vector3::Transform(pointNear, inverseviewproj);
	m_rayFar = Vector3::Transform(pointFar, inverseviewproj);
	//Vector3 raySubtraction = rayFar - rayNear;
	//Vector3 rayDirection = raySubtraction;
	//// 正規化
	//rayDirection.Normalize();

}

void MouseCursor::Render(const DirectX::SimpleMath::Matrix& _view)
{
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_reticle.Get(), Vector3(m_state.x, m_state.y, 0), nullptr, Colors::LightYellow,
		0.0f, Vector2(64, 64), Vector2(0.3f, 0.3f));
}
