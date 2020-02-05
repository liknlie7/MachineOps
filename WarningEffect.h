#pragma once

#include <vector>
#include <SimpleMath.h>
#include <WICTextureLoader.h>

#include "DeviceResources.h"
#include "GameContext.h"
#include "File.h"



// 警告ライン
class WarningEffect
{
private: // 定数

	// ピクセルシェーダーに渡す定数バッファの構造体
	struct cbChangesEveryFrame
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 dummy;
	};

public: // 基本

	// コンストラクタ
	WarningEffect();
	// デストラクタ
	~WarningEffect() {};

public: // 関数

	// 初期化
	void Initialize();
	// 更新
	void Update();
	
public: // 変数

	static const std::vector<D3D11_INPUT_ELEMENT_DESC>		INPUT_LAYOUT;

	Microsoft::WRL::ComPtr<ID3D11Buffer>					m_cBuffer;

	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader>				m_pixelShader;

private: // 変数

	// レンダーターゲットビュー
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;

	// シェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;

	// 定数バッファ
	cbChangesEveryFrame m_cbChangesEveryFrame;

	// 2Dテクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	// オープン又はクローズするまでの時間
	float m_interval;

	// 割合(0～1):0の場合閉じている
	float m_rate;

	// オープンフラグ（trueの場合オープン）
	bool m_open;

	// マスクの色
	DirectX::SimpleMath::Color m_color;
};

