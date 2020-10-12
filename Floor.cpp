#include "pch.h"

#include "Floor.h"

// 横幅
const float Floor::AREA_WIDTH = 50.0f;
// 縦幅
const float Floor::AREA_HEIGHT = 50.0f;

// コンストラクタ
Floor::Floor()
{

}

// 初期化
void Floor::Initialize()
{
	// エフェクトファクトリの作成
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());

	// テクスチャの読み込みパス指定
	factory->SetDirectory(L"Resources/Models");

	// ファイルを指定してモデルデータ読み込み
	m_pModel = DirectX::Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources/Models/floor.cmo", *factory);

	delete factory;

	// 頂点ベクトル
	 m_vector[0] = DirectX::SimpleMath::Vector3(-AREA_WIDTH, 0.0f, -AREA_HEIGHT);  // 左上
	 m_vector[1] = DirectX::SimpleMath::Vector3(-AREA_WIDTH, 0.0f, AREA_HEIGHT);   // 左下
	 m_vector[2] = DirectX::SimpleMath::Vector3(AREA_WIDTH, 0.0f, AREA_HEIGHT);    // 右下
	 m_vector[3] = DirectX::SimpleMath::Vector3(AREA_WIDTH, 0.0f, -AREA_HEIGHT);   // 右上
}

// 更新
void Floor::Update()
{

}

// 描画
void Floor::Render(const DirectX::SimpleMath::Matrix& _view)
{
	// 行列作成
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	// モデル描画
	m_pModel->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), *GameContext::Get<DirectX::CommonStates>(), world, _view, GameContext::Get<Projection>()->GetMatrix());
}