#include "pch.h"
#include "EffectManager.h"
#include <WICTextureLoader.h>
#include "BinaryFile.h"
#include "d3d11.h"
#include <Effects.h>
#include <Model.h>

using namespace DirectX::SimpleMath;
using namespace DirectX;

//const std::vector<D3D11_INPUT_ELEMENT_DESC> EffectManager::INPUT_LAYOUT =
//{
//	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(Vector3) + sizeof(Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 },
//};

EffectManager::EffectManager()
	: m_interval(0.0f)
	, m_rate(0.0f)
	, m_open(false)
	, m_color(DirectX::Colors::White)

{
}

void EffectManager::InitializeMask(float _interval)
{
	DX::DeviceResources*   deviceResources = GameContext::Get<DX::DeviceResources>();
	ID3D11Device*          device = deviceResources->GetD3DDevice();
	ID3D11DeviceContext*   deviceContext = deviceResources->GetD3DDeviceContext();

	m_interval = _interval;

	// ピクセルシェーダーの読み込みと作成
	File* ps = new File(L"Resources\\Shaders\\MaskShader.cso");
	device->CreatePixelShader((void*)ps->data, ps->length, NULL, m_pixelShader.GetAddressOf());
	delete ps;

	// 定数バッファの定義
	D3D11_BUFFER_DESC cBufferDesc;
	cBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	cBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cBufferDesc.MiscFlags = 0;

	// 定数バッファの作成
	cBufferDesc.ByteWidth = sizeof(cbChangesEveryFrame);
	device->CreateBuffer(&cBufferDesc, NULL, m_cBuffer.GetAddressOf());

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
	device->CreateTexture2D(&texDesc, NULL, m_texture2D.GetAddressOf());

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

//void EffectManager::Create(const wchar_t* _name,int _count)
//{
//	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();
//	auto device = deviceResources->GetD3DDevice();
//	auto context = deviceResources->GetD3DDeviceContext();
//
//	//const wchar_t* name = L"Resources\\Textures\\image01.png";
//	DirectX::CreateWICTextureFromFile(device, _name , nullptr, m_texture.GetAddressOf());
//	DirectX::CreateWICTextureFromFile(device, L"Resources\\Textures\\floor.png", nullptr, m_texture2.GetAddressOf());
//
//	// コンパイルされたシェーダファイルを読み込み
//	BinaryFile VSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleVS.cso");
//	BinaryFile GSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticleGS.cso");
//	BinaryFile PSData = BinaryFile::LoadFile(L"Resources/Shaders/ParticlePS.cso");
//
//	device->CreateInputLayout(&INPUT_LAYOUT[0],
//		INPUT_LAYOUT.size(),
//		VSData.GetData(), VSData.GetSize(),
//		m_inputLayout.GetAddressOf());
//	// 頂点シェーダ作成
//	if (FAILED(device->CreateVertexShader(VSData.GetData(), VSData.GetSize(), NULL, m_vertexShader.ReleaseAndGetAddressOf())))
//	{// エラー
//		MessageBox(0, L"CreateVertexShader Failed.", NULL, MB_OK);
//		return;
//	}
//	// ジオメトリシェーダ作成
//	if (FAILED(device->CreateGeometryShader(GSData.GetData(), GSData.GetSize(), NULL, m_geometryShader.ReleaseAndGetAddressOf())))
//	{// エラー
//		MessageBox(0, L"CreateGeometryShader Failed.", NULL, MB_OK);
//		return;
//	}
//	// ピクセルシェーダ作成
//	if (FAILED(device->CreatePixelShader(PSData.GetData(), PSData.GetSize(), NULL, m_pixelShader.ReleaseAndGetAddressOf())))
//	{// エラー
//		MessageBox(0, L"CreatePixelShader Failed.", NULL, MB_OK);
//		return;
//	}
//	// プリミティブバッチの作成
//	m_batch = std::make_unique<PrimitiveBatch<VertexPositionColorTexture>>(context);
//
//	m_states = std::make_unique<CommonStates>(device);
//
//
//
//	D3D11_BUFFER_DESC bd;
//	ZeroMemory(&bd, sizeof(bd));
//	bd.Usage = D3D11_USAGE_DEFAULT;
//	bd.ByteWidth = sizeof(ConstBuffer);
//	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
//	bd.CPUAccessFlags = 0;
//	device->CreateBuffer(&bd, nullptr, &m_cBuffer);
//	m_fxFactory = std::make_unique<EffectFactory>(device);
//	m_fxFactory->SetDirectory(L"Resources");
//
//	m_model = Model::CreateFromCMO(device, L"Resources/cup.cmo", *m_fxFactory);
//
//	for (int i = 0; i < _count; i++) {
//		MyEffect* effect = new MyEffect();
//		m_effectList.push_back(effect);
//	}
//}
//void EffectManager::Lost() {
//	for (std::list<MyEffect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
//	{
//		delete (*itr);
//	}
//}
//void EffectManager::Initialize(float life, DirectX::SimpleMath::Vector3 pos)
//{
//	int range = 100;
//	for (std::list<MyEffect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
//	{
//		Vector3 vel = Vector3(((rand() % (range * 2)) - range)*0.1f / range, ((rand() % (range * 2)) - range)*0.1f / range, 0);
//		while (vel.Length() < 0.0001f) 
//		{
//			vel = Vector3(((rand() % (range * 2)) - range)*0.1f / range, ((rand() % (range * 2)) - range)*0.1f / range, 0);
//		}
//		(*itr)->Initialize(life,pos,vel);
//	}
//	m_centerPosition = pos;
//}
//void EffectManager::InitializeNormal(float life, DirectX::SimpleMath::Vector3 pos)
//{
//	int range = 1000;
//	for (std::list<MyEffect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
//	{
//		Vector3 vel = Vector3(((rand() % (range * 2)) - range)*0.1f / range, ((rand() % (range * 2)) - range)*0.1f / range, 0);
//		vel.Normalize();
//		vel *= 0.1f;
//		(*itr)->Initialize(life, pos, vel);
//	}
//	m_centerPosition = pos;
//}
//void EffectManager::InitializeCorn(float life, DirectX::SimpleMath::Vector3 pos, DirectX::SimpleMath::Vector3 dir)
//{
//	Vector3 vel = Vector3::Zero;
//	for (std::list<MyEffect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
//	{
//		vel.x += XMConvertToRadians(90);
//		(*itr)->Initialize(life, pos, vel);
//	}
//	m_centerPosition = pos;
//}
//void EffectManager::Update(DX::StepTimer timer)
//{
//	m_timer = timer;
//	for(std::list<MyEffect*>::iterator itr = m_effectList.begin(); itr != m_effectList.end();itr++)
//	{
//		(*itr)->Update(timer);
//	}
//}

void EffectManager::UpdateEffectMask(float _elapsedTime)
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

//void EffectManager::Render()
//{
//	auto context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
//
//	m_vertex.clear();
//	//マネージャで管理しているエフェクト分イテレータを回す
//	for (auto itr = m_effectList.begin(); itr != m_effectList.end(); itr++)
//	{
//		//エフェクトの頂点の座標と速度を取得する
//		Vector3 pos = (*itr)->GetPosition();
//		Vector3 vel = (*itr)->GetVelocity();
//
//		{
//			//取得した座標を登録する
//			VertexPositionColorTexture vertex;
//			//vertex = VertexPositionColorTexture(pos, Vector4(vel.x,vel.y,vel.z,1), Vector2(0.0f,3.0f));
//			vertex = VertexPositionColorTexture(pos, Vector4::Zero, Vector2::Zero);
//			m_vertex.push_back(vertex);
//		}
//	}
//
//	//全画面エフェクト
//
//	Matrix  mat = Matrix::Identity;
//	Draw(mat, mat, mat);
//
//	//板ポリゴンエフェクト
//
//	//Draw(m_billboardTranslation,m_view, m_proj);
//
//}

void EffectManager::DrawEffectMask()
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
		deviceContext->Map(m_cBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		CopyMemory(mappedResource.pData, &m_cbChangesEveryFrame, sizeof(cbChangesEveryFrame));
		deviceContext->Unmap(m_cBuffer.Get(), 0);

		// ピクセルシェーダーに定数バッファを設定
		ID3D11Buffer* buffers[] = { m_cBuffer.Get() };
		deviceContext->PSSetConstantBuffers(0, 1, buffers);

		// ピクセルシェーダーを設定
		deviceContext->PSSetShader(m_pixelShader.Get(), nullptr, 0);
	});

	// マスクの描画
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_shaderResourceView.Get(), rect, m_color);

	GameContext::Get<DirectX::SpriteBatch>()->End();

}

//void EffectManager::SetRenderState(DirectX::SimpleMath::Vector3 camera, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
//{
//	m_view = view;
//	m_proj = proj;
//
//	m_billboardTranslation = Matrix::CreateBillboard(m_centerPosition, camera, Vector3::UnitY);
//
//	//ビルボードの計算で裏返るので補正
//	//Y軸で180度回転する行列
//	Matrix rev = Matrix::Identity;
//	rev._11 = -1;
//	rev._33 = -1;
//
//	//補正行列を先にかけて他に影響がないようにする
//	m_billboardTranslation =rev * m_billboardTranslation;
//
//}
//
//void EffectManager::Draw(DirectX::SimpleMath::Matrix world, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix proj)
//{
//	auto context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
//
//	//定数バッファで渡す値の設定
//	ConstBuffer cbuff;
//	cbuff.matView = view.Transpose();
//	cbuff.matProj = proj.Transpose();
//	cbuff.matWorld = world.Transpose();
//	//Time		x:経過時間(トータル秒)	y:1Fの経過時間(秒）	z:反復（サインカーブ） w:未使用（暫定で１）
//	cbuff.Time = Vector4(m_timer.GetTotalSeconds(), m_timer.GetElapsedSeconds(), sinf(m_timer.GetTotalSeconds()), 1);
//
//	//定数バッファの内容更新
//	context->UpdateSubresource(m_cBuffer.Get(), 0, NULL, &cbuff, 0, 0);
//
//	ID3D11BlendState* blendstate = m_states->NonPremultiplied();
//	// 透明判定処理
//	context->OMSetBlendState(blendstate, nullptr, 0xFFFFFFFF);
//	// 深度バッファは参照のみ
//	context->OMSetDepthStencilState(m_states->DepthRead(), 0);
//	// カリングは反時計回り
//	context->RSSetState(m_states->CullCounterClockwise());
//
//	//定数バッファをシェーダに渡す（とりあえずPSは要らないのでコメントアウト）
//	ID3D11Buffer* cb[1] = { m_cBuffer.Get() };
//	//context->VSSetConstantBuffers(0, 1, cb);
//	context->GSSetConstantBuffers(0, 1, cb);
//	context->PSSetConstantBuffers(0, 1, cb);
//
//
//	//サンプラー、シェーダ、画像をそれぞれ登録
//	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
//	context->PSSetSamplers(0, 1, sampler);
//	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
//	context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
//	context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
//	context->PSSetShaderResources(0, 1, m_texture.GetAddressOf());
//	context->PSSetShaderResources(1, 1, m_texture2.GetAddressOf());
//
//	//入力レイアウトを反映
//	context->IASetInputLayout(m_inputLayout.Get());
//
//	//バッチに頂点情報を渡す
//	m_batch->Begin();
//	//m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
//	m_batch->Draw(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST, &m_vertex[0], m_vertex.size());
//	m_batch->End();
//
//
//	//他のモデルに影響が出る可能性があるので使い終わったらシェーダを外す
//	context->VSSetShader(nullptr, nullptr, 0);
//	context->GSSetShader(nullptr, nullptr, 0);
//	context->PSSetShader(nullptr, nullptr, 0);
//	
//
//
//}

////モデル等をテクスチャ(m_srv)に描画する処理
//void EffectManager::RenderModel() 
//{
//	auto deviceResources = GameContext::Get<DX::DeviceResources>();
//	auto context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
//
//	D3D11_TEXTURE2D_DESC texDesc;
//	deviceResources->GetRenderTarget()->GetDesc(&texDesc);
//	texDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
//	texDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
//	deviceResources->GetD3DDevice()->CreateTexture2D(&texDesc, NULL, m_capture.ReleaseAndGetAddressOf());
//
//	// レンダーターゲットビューの設定
//	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
//	memset(&rtvDesc, 0, sizeof(rtvDesc));
//	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
//	// レンダーターゲットビューの生成
//	deviceResources->GetD3DDevice()->CreateRenderTargetView(m_capture.Get(), &rtvDesc, &m_rtv);
//
//	//シェーダリソースビューの設定
//	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
//	ZeroMemory(&srvDesc, sizeof(srvDesc));
//	srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//	srvDesc.Texture2D.MostDetailedMip = 0;
//	srvDesc.Texture2D.MipLevels = texDesc.MipLevels;
//
//	//レンダーターゲットビュー,深度ビューを取得（後で元に戻すため）
//	ID3D11RenderTargetView* defaultRTV = deviceResources->GetRenderTargetView();
//	ID3D11DepthStencilView* pDSV = deviceResources->GetDepthStencilView();
//
//	//背景色の設定（アルファを０にするとオブジェクトのみ表示）
//	float clearColor[4] = { 1.0f, 1.0f, 1.0f, 0.0f };
//
//	//レンダーターゲットビューをセットし、初期化する
//	context->OMSetRenderTargets(1, m_rtv.GetAddressOf(), pDSV);
//	context->ClearRenderTargetView(m_rtv.Get(), clearColor);
//	context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
//
//	//----------------------------------------------------------------------------
//	//とりあえずの動きのために回転
//	static float rot = 0.0f;
//	rot += 0.1f;
//
//	//モデルを描画
//	m_model->Draw(deviceResources->GetD3DDeviceContext(), *m_states, Matrix::CreateRotationZ(rot), m_view, m_proj);
//
//	//描画した画面をm_srvに保存
//	auto hr = deviceResources->GetD3DDevice()->CreateShaderResourceView(
//		m_capture.Get(), &srvDesc, m_srv.ReleaseAndGetAddressOf());
//
//	//------------------------------------------------------------------
//	//設定をもとに戻す
//	clearColor[0] = 0.3f;
//	clearColor[1] = 0.3f;
//	context->OMSetRenderTargets(1, &defaultRTV, pDSV);
//	context->ClearRenderTargetView(defaultRTV, clearColor);
//	context->ClearDepthStencilView(pDSV, D3D11_CLEAR_DEPTH, 1.0f, 0);
//
//
//}

void EffectManager::Open()
{
	m_open = true;
}

void EffectManager::Close()
{
	m_open = false;
}

bool EffectManager::IsOpen()
{
	if (m_open && m_rate == 1.0f) return true;
	return false;
}

bool EffectManager::IsClose()
{
	if (!m_open && m_rate == 0.0f) return true;
	return false;
}
