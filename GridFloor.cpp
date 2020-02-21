#include "pch.h"

#include "GridFloor.h"

#include <algorithm>

GridFloor::GridFloor(float size, int divs)
	: m_size(size)
	, m_divs(divs)
{

	m_pDeviceResources = GameContext::Get<DX::DeviceResources>();
	m_pState = GameContext::Get<DirectX::CommonStates>();

	// エフェクトの生成
	m_pBasicEffect = std::make_unique<DirectX::BasicEffect>(m_pDeviceResources->GetD3DDevice());

	// 頂点カラー(有効)
	m_pBasicEffect->SetVertexColorEnabled(true);

	// プリミティブオブジェクト生成
	m_pPrimitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(m_pDeviceResources->GetD3DDeviceContext());

	// インプットレイアウト生成
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_pBasicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	m_pDeviceResources->GetD3DDevice()->CreateInputLayout(DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_pInputLayout.GetAddressOf());
}


GridFloor::~GridFloor()
{
	// エフェクトを解放する
	m_pBasicEffect.reset();
	// 入力レイアウトを解放する
	m_pInputLayout.Reset();
}


void GridFloor::draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, DirectX::GXMVECTOR color)
{
	DirectX::SimpleMath::Matrix world;

	m_pDeviceResources->GetD3DDeviceContext()->OMSetBlendState(m_pState->Opaque(), nullptr, 0xFFFFFFFF);
	m_pDeviceResources->GetD3DDeviceContext()->OMSetDepthStencilState(m_pState->DepthDefault(), 0);

	m_pBasicEffect->SetWorld(world);
	m_pBasicEffect->SetView(view);
	m_pBasicEffect->SetProjection(proj);


	m_pBasicEffect->Apply(m_pDeviceResources->GetD3DDeviceContext());
	m_pDeviceResources->GetD3DDeviceContext()->IASetInputLayout(m_pInputLayout.Get());

	m_pPrimitiveBatch->Begin();

	const DirectX::XMVECTORF32 xAxis = { m_size, 0.f, 0.f };
	const DirectX::XMVECTORF32 yAxis = { 0.f, 0.f, m_size };

	size_t divs = std::max<size_t>(1, m_divs);
	DirectX::FXMVECTOR origin = DirectX::g_XMZero;
	for (size_t i = 0; i <= divs; ++i)
	{
		float fPercent = float(i) / float(divs);
		fPercent = (fPercent * 1.0f) - 0.5f;
		DirectX::XMVECTOR vScale = XMVectorScale(xAxis, fPercent);
		vScale = DirectX::XMVectorAdd(vScale, origin);

		DirectX::VertexPositionColor v1(DirectX::XMVectorSubtract(vScale, yAxis * 0.5f), color);
		DirectX::VertexPositionColor v2(DirectX::XMVectorAdd(vScale, yAxis * 0.5f), color);
		m_pPrimitiveBatch->DrawLine(v1, v2);
	}

	for (size_t i = 0; i <= divs; i++)
	{
		FLOAT fPercent = float(i) / float(divs);
		fPercent = (fPercent * 1.0f) - 0.5f;
		DirectX::XMVECTOR vScale = XMVectorScale(yAxis, fPercent);
		vScale = DirectX::XMVectorAdd(vScale, origin);

		DirectX::VertexPositionColor v1(DirectX::XMVectorSubtract(vScale, xAxis * 0.5f), color);
		DirectX::VertexPositionColor v2(DirectX::XMVectorAdd(vScale, xAxis * 0.5f), color);
		m_pPrimitiveBatch->DrawLine(v1, v2);
	}

	m_pPrimitiveBatch->End();
}