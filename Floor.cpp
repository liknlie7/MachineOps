#include "pch.h"

#include "Floor.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void Floor::Initialize()
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();

	// エフェクトファクトリの作成
	EffectFactory* factory = new EffectFactory(deviceResources->GetD3DDevice());

	// テクスチャの読み込みパス指定
	factory->SetDirectory(L"Resources/Models");

	// ファイルを指定してモデルデータ読み込み
	m_pModel = Model::CreateFromCMO(deviceResources->GetD3DDevice(), L"Resources/Models/Floor.cmo", *factory);

	delete factory;
}

void Floor::Render(DirectX::SimpleMath::Matrix _view)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();
	Projection* proj = GameContext<Projection>().Get();
	CommonStates* state = GameContext<CommonStates>().Get();

	Matrix world = Matrix::Identity;

	// モデル描画
	m_pModel->Draw(deviceResources->GetD3DDeviceContext(), *state, world, _view, proj->GetMatrix());
}