#include "pch.h"

#include "Floor.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float Floor::AREA_WIDTH = 50.0f;
const float Floor::AREA_HEIGHT = 50.0f;

void Floor::Initialize()
{
	// エフェクトファクトリの作成
	EffectFactory* factory = new EffectFactory(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());

	// テクスチャの読み込みパス指定
	factory->SetDirectory(L"Resources/Models");

	// ファイルを指定してモデルデータ読み込み
	m_pModel = Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources/Models/floor.cmo", *factory);

	delete factory;

	// 頂点ベクトル
	 m_vector[0] = Vector3(-AREA_WIDTH, 0.0f, -AREA_HEIGHT);  // 左上
	 m_vector[1] = Vector3(-AREA_WIDTH, 0.0f, AREA_HEIGHT);   // 左下
	 m_vector[2] = Vector3(AREA_WIDTH, 0.0f, AREA_HEIGHT);    // 右下
	 m_vector[3] = Vector3(AREA_WIDTH, 0.0f, -AREA_HEIGHT);   // 右上
}

void Floor::Render(DirectX::SimpleMath::Matrix _view)
{
	Matrix world = Matrix::Identity;

	// モデル描画
	m_pModel->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), *GameContext::Get<CommonStates>(), world, _view, GameContext::Get<Projection>()->GetMatrix());
}