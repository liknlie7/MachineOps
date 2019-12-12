#include "pch.h"

#include "Floor.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void Floor::Initialize()
{
	// エフェクトファクトリの作成
	EffectFactory* factory = new EffectFactory(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());

	// テクスチャの読み込みパス指定
	factory->SetDirectory(L"Resources/Models");

	// ファイルを指定してモデルデータ読み込み
	m_pModel = Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources/Models/Floor.cmo", *factory);

	delete factory;
}

void Floor::Render(DirectX::SimpleMath::Matrix _view)
{
	Matrix world = Matrix::Identity;

	// モデル描画
	m_pModel->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), *GameContext::Get<CommonStates>(), world, _view, GameContext::Get<Projection>()->GetMatrix());
}