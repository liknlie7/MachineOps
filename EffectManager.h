#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "Model.h"
#include "GameContext.h"
#include "File.h"
#include <list>

class EffectManager
{
public: // 基本

	EffectManager();
	~EffectManager() {};

public:
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Time;
	};

	static const std::vector<D3D11_INPUT_ELEMENT_DESC> INPUT_LAYOUT;

	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cBuffer;

	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;

	// TODO: クラス分け
	//フェード-----------------------------------------------------------------------------------------------
public:
	// 初期化
	void Initialize(float _interval);
	// 更新
	void Update(float _elapsedTime);
	// 描画
	void Render();

	// オープンする関数
	void Open();

	// クローズする関数
	void Close();

	// オープン中かチェックする関数
	bool IsOpen();

	// クローズ中かチェックする関数
	bool IsClose();

	// マスクの色の設定関数
	void SetColor(DirectX::FXMVECTOR color) { m_color = color; }

	// オープン具合を返す関数(0～1)
	float GetOpenRate() { return m_rate; }

private:
	// オープン又はクローズするまでの時間
	float m_interval;

	// 割合(0～1):0の場合閉じている
	float m_rate;

	// オープンフラグ（trueの場合オープン）
	bool m_open;

	// マスクの色
	DirectX::SimpleMath::Color m_color;

	// 2Dテクスチャ
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture2D;

	// ピクセルシェーダーに渡す定数バッファの構造体
	struct cbChangesEveryFrame
	{
		FLOAT radius;
		FLOAT aspectRatio;
		DirectX::XMFLOAT2 dummy;
	};

	// 定数バッファ
	cbChangesEveryFrame m_cbChangesEveryFrame;

	// レンダーターゲットビュー
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;

	// シェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_shaderResourceView;

};