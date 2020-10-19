#include "../../pch.h"

#include "EffectMask.h"
#include "../Common/GameContext.h"

// コンストラクタ
EffectMask::EffectMask()
	: m_interval(0.0f)
	, m_rate(1.0f)
	, m_open(true)
	, m_color(DirectX::Colors::White)
{

}

// 初期化
void EffectMask::Initialize(float _interval)
{
	DX::DeviceResources*   deviceResources = GameContext::Get<DX::DeviceResources>();
	ID3D11Device*          device = deviceResources->GetD3DDevice();
	ID3D11DeviceContext*   deviceContext = deviceResources->GetD3DDeviceContext();

	m_interval = _interval;

	// ピクセルシェーダーの読み込みと作成
	File* ps = new File(L"Resources\\Shaders\\MaskShader.cso");
	device->CreatePixelShader((void*)ps->m_data, ps->m_length, NULL, m_pixelShader.GetAddressOf());
	delete ps;

	// 定数バッファの定義
	D3D11_BUFFER_DESC cBufferDesc;
	cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cBufferDesc.MiscFlags = 0;

	// 定数バッファの作成
	cBufferDesc.ByteWidth = sizeof(cbChangesEveryFrame);
	device->CreateBuffer(&cBufferDesc, NULL, m_CBuffer.GetAddressOf());

	// レンダリングターゲット用のテクスチャを作成
	D3D11_TEXTURE2D_DESC texDesc;
	memset(&texDesc, 0, sizeof(texDesc));
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	texDesc.Width = deviceResources->GetOutputSize().right;
	texDesc.Height = deviceResources->GetOutputSize().bottom;
	texDesc.CPUAccessFlags = 0;
	texDesc.MipLevels = 1;
	texDesc.ArraySize = 1;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	device->CreateTexture2D(&texDesc,NULL, m_texture2D.GetAddressOf());

	// レンダーターゲットビューの生成
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	device->CreateRenderTargetView(m_texture2D.Get(), &rtvDesc, m_renderTargetView.GetAddressOf());

	// シェーダーリソースビューの生成
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(srvDesc));
	srvDesc.Format = rtvDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	device->CreateShaderResourceView(m_texture2D.Get(), &srvDesc, m_shaderResourceView.GetAddressOf());
}


// 更新
void EffectMask::Update(float _elapsedTime)
{
	if (m_open)
	{
		// オープン
		m_rate += _elapsedTime / m_interval;
		if (m_rate > 1.0f) m_rate = 1.0f;
	}
	else
	{
		// クローズ
		m_rate -= _elapsedTime / m_interval;
		if (m_rate < 0.0f) m_rate = 0.0f;
	}
}

// 描画
void EffectMask::Render()
{
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();
	DX::DeviceResources*   deviceResources = GameContext::Get<DX::DeviceResources>();
	ID3D11Device*          device = deviceResources->GetD3DDevice();
	ID3D11DeviceContext*   deviceContext = deviceResources->GetD3DDeviceContext();

	RECT rect;
	int w, h;
	w = deviceResources->GetOutputSize().right;
	h = deviceResources->GetOutputSize().bottom;

	// 開いている場合は描画はしない
	if (m_rate == 1.0f) return;

	// 画面サイズの矩形を設定する
	rect.left = 0;
	rect.top = 0;
	rect.right = w;
	rect.bottom = h;

	// 定数バッファの値を設定
	m_cbChangesEveryFrame.radius = m_rate;
	m_cbChangesEveryFrame.aspectRatio = w / (float)h;

	GameContext::Get<DirectX::SpriteBatch>()->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, [&]()
	{
		// 定数バッファへの書き込み
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		deviceContext->Map(m_CBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		CopyMemory(mappedResource.pData, &m_cbChangesEveryFrame, sizeof(cbChangesEveryFrame));
		deviceContext->Unmap(m_CBuffer.Get(), 0);

		// ピクセルシェーダーに定数バッファを設定
		ID3D11Buffer* buffers[] = { m_CBuffer.Get() };
		deviceContext->PSSetConstantBuffers(0, 1, buffers);

		// ピクセルシェーダーを設定
		deviceContext->PSSetShader(m_pixelShader.Get(), nullptr, 0);
	});

	// マスクの描画
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_shaderResourceView.Get(), rect, m_color);

	GameContext::Get<DirectX::SpriteBatch>()->End();

}

// オープン
void EffectMask::Open()
{
	m_open = true;
}

// クローズ
void EffectMask::Close()
{
	m_open = false;
}

// オープン中か
bool EffectMask::IsOpen()
{
	if (m_open && m_rate == 1.0f) return true;
	return false;
}

// クローズ中か
bool EffectMask::IsClose()
{
	if (!m_open && m_rate <= 0.0f) return true;
	return false;
}
