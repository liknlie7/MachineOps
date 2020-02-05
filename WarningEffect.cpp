#include "pch.h"
#include "WarningEffect.h"

// コンストラクタ
WarningEffect::WarningEffect()
{
}

// 初期化
void WarningEffect::Initialize()
{
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();
	ID3D11Device1* device = deviceResources->GetD3DDevice();

	DirectX::CreateWICTextureFromFile(device, L"Resources\\Textures\\WarningLine.png", nullptr, m_texture.GetAddressOf());

	// ピクセルシェーダーの読み込みと作成
	File* ps = new File(L"Resources\\Shaders\\MaskShader.cso");
	device->CreatePixelShader((void*)ps->data, ps->length, NULL, m_pixelShader.GetAddressOf());
	delete ps;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(cbChangesEveryFrame);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;	
	bd.CPUAccessFlags = 0;
	device->CreateBuffer(&bd, nullptr, &m_cBuffer);
}

// 更新
void WarningEffect::Update()
{
}
