#pragma once

#include "CommonStates.h"
#include "DeviceResources.h"
#include "PrimitiveBatch.h"
#include "Effects.h"
#include "VertexTypes.h"
#include "SimpleMath.h"
#include "GameContext.h"

class GridFloor
{
public:

	GridFloor(float size, int divs);
	~GridFloor();

public:

	// 描画
	void draw(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj, DirectX::GXMVECTOR color = DirectX::Colors::Gray);

private:

	// Device Resources
	DX::DeviceResources* m_pDeviceResources;

	// エフェクト
	std::unique_ptr<DirectX::BasicEffect> m_pBasicEffect;

	// プリミティブバッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_pPrimitiveBatch;

	// インプットレイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;

	// コモンステート
	DirectX::CommonStates* m_pState;

	// 床の一辺のサイズ
	float m_size;

	// 分割数
	int m_divs;
};