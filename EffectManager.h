#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"
#include <SimpleMath.h>
#include <SpriteBatch.h>
#include "MyEffect.h"
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
	//void Create(const wchar_t* _name, int _count);
	//void Initialize(float _life, DirectX::SimpleMath::Vector3 _pos);
	//void InitializeNormal(float _life, DirectX::SimpleMath::Vector3 _pos);
	//void InitializeCorn(float _life, DirectX::SimpleMath::Vector3 _pos, DirectX::SimpleMath::Vector3 _dir);
	//void Update(DX::StepTimer _timer);
	//void Render();
	//void Lost();

	//void SetRenderState(DirectX::SimpleMath::Vector3 _camera, DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Matrix _proj);
	//void Draw(DirectX::SimpleMath::Matrix _world, DirectX::SimpleMath::Matrix _view, DirectX::SimpleMath::Matrix _proj);

	//void RenderModel();

//private:
//	//MyEffect*					m_myEffect[10];
//	std::list<MyEffect*>		m_effectList;
//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;
//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture2;
//
//
//	DX::StepTimer                           m_timer;
//
//
	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_cBuffer;
//	std::unique_ptr<DirectX::CommonStates> m_states;
//
	// 頂点シェーダ
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// ピクセルシェーダ
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;
	// ジオメトリシェーダ
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
//
//	// プリミティブバッチ
//	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>> m_batch;
//	// 入力レイアウト
//	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
//	std::vector<DirectX::VertexPositionColorTexture>  m_vertex;
//
//	DirectX::SimpleMath::Vector3 m_centerPosition;
//
//	DirectX::SimpleMath::Matrix m_billboardTranslation;
//	DirectX::SimpleMath::Matrix m_view;
//	DirectX::SimpleMath::Matrix m_proj;
//
//	std::unique_ptr<DirectX::EffectFactory> m_fxFactory;
//	std::unique_ptr<DirectX::Model> m_model;
//
//
//	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_capture;
//	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_rtv;
//	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_srv;
//
//
	// TODO: クラス分け
	//フェード-----------------------------------------------------------------------------------------------
public:
	// 初期化
	void InitializeMask(float _interval);
	// 更新
	void UpdateEffectMask(float _elapsedTime);
	// 描画
	void DrawEffectMask();

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