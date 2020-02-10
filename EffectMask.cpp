#include "pch.h"
#include "EffectMask.h"

using namespace DirectX::SimpleMath;
using namespace DirectX;

EffectMask::EffectMask()
	: m_interval(0.0f)
	, m_rate(1.0f)
	, m_open(true)
	, m_color(DirectX::Colors::White)
{

}

void EffectMask::Initialize(float _interval,DirectX::SimpleMath::Vector4 _color)
{
	DX::DeviceResources*   deviceResources = GameContext::Get<DX::DeviceResources>();
	ID3D11Device*          device = deviceResources->GetD3DDevice();
	ID3D11DeviceContext*   deviceContext = deviceResources->GetD3DDeviceContext();

	m_interval = _interval;
	m_color = _color;

	// �s�N�Z���V�F�[�_�[�̓ǂݍ��݂ƍ쐬
	File* ps = new File(L"Resources\\Shaders\\MaskShader.cso");
	device->CreatePixelShader((void*)ps->m_data, ps->m_length, NULL, m_pixelShader.GetAddressOf());
	delete ps;

	// �萔�o�b�t�@�̒�`
	D3D11_BUFFER_DESC cBufferDesc;
	cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cBufferDesc.MiscFlags = 0;

	// �萔�o�b�t�@�̍쐬
	cBufferDesc.ByteWidth = sizeof(cbChangesEveryFrame);
	device->CreateBuffer(&cBufferDesc, NULL, m_CBuffer.GetAddressOf());

	// �����_�����O�^�[�Q�b�g�p�̃e�N�X�`�����쐬
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

	// �����_�[�^�[�Q�b�g�r���[�̐���
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	device->CreateRenderTargetView(m_texture2D.Get(), &rtvDesc, m_renderTargetView.GetAddressOf());

	// �V�F�[�_�[���\�[�X�r���[�̐���
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(srvDesc));
	srvDesc.Format = rtvDesc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	device->CreateShaderResourceView(m_texture2D.Get(), &srvDesc, m_shaderResourceView.GetAddressOf());
}


void EffectMask::Update(float _elapsedTime)
{
	if (m_open)
	{
		// �I�[�v��
		m_rate += _elapsedTime / m_interval;
		if (m_rate > 1.0f) m_rate = 1.0f;
	}
	else
	{
		// �N���[�Y
		m_rate -= _elapsedTime / m_interval;
		if (m_rate < 0.0f) m_rate = 0.0f;
	}
}


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

	// �J���Ă���ꍇ�͕`��͂��Ȃ�
	if (m_rate == 1.0f) return;

	// ��ʃT�C�Y�̋�`��ݒ肷��
	rect.left = 0;
	rect.top = 0;
	rect.right = w;
	rect.bottom = h;

	// �萔�o�b�t�@�̒l��ݒ�
	m_cbChangesEveryFrame.radius = m_rate;
	m_cbChangesEveryFrame.aspectRatio = w / (float)h;

	GameContext::Get<DirectX::SpriteBatch>()->Begin(DirectX::SpriteSortMode_Deferred, nullptr, nullptr, nullptr, nullptr, [&]()
	{
		// �萔�o�b�t�@�ւ̏�������
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		deviceContext->Map(m_CBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		CopyMemory(mappedResource.pData, &m_cbChangesEveryFrame, sizeof(cbChangesEveryFrame));
		deviceContext->Unmap(m_CBuffer.Get(), 0);

		// �s�N�Z���V�F�[�_�[�ɒ萔�o�b�t�@��ݒ�
		ID3D11Buffer* buffers[] = { m_CBuffer.Get() };
		deviceContext->PSSetConstantBuffers(0, 1, buffers);

		// �s�N�Z���V�F�[�_�[��ݒ�
		deviceContext->PSSetShader(m_pixelShader.Get(), nullptr, 0);
	});

	// �}�X�N�̕`��
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_shaderResourceView.Get(), rect, m_color);

	GameContext::Get<DirectX::SpriteBatch>()->End();

}

void EffectMask::Open()
{
	m_open = true;
}

void EffectMask::Close()
{
	m_open = false;
}

bool EffectMask::IsOpen()
{
	if (m_open && m_rate == 1.0f) return true;
	return false;
}

bool EffectMask::IsClose()
{
	if (!m_open && m_rate <= 0.0f) return true;
	return false;
}
