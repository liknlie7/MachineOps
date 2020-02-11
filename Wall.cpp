#include "pch.h"
#include "Wall.h"

// コンストラクタ
Wall::Wall(const std::string & _tag)
	: GameObject(_tag)
{
}

// 初期化
void Wall::Initialize()
{
	// エフェクトファクトリの作成
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());

	// テクスチャの読み込みパス指定
	factory->SetDirectory(L"Resources/Models");

	// ファイルを指定してモデルデータ読み込み
	m_pModel = DirectX::Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources/Models/Wall.cmo", *factory);

	delete factory;

}

// 更新
void Wall::Update()
{
}

// 描画
void Wall::Render(const DirectX::SimpleMath::Matrix & _view)
{
	// 行列作成
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateScale(0.5f, 0.5f, 0.5f);

	// モデル描画
	m_pModel->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), *GameContext::Get<DirectX::CommonStates>(), world, _view, GameContext::Get<Projection>()->GetMatrix());
}
