#include "pch.h"

#include <CommonStates.h>

#include "Floor.h"
#include "DeviceResources.h"
#include "Projection.h"
#include "GameContext.h"
#include "ResourceManager.h"

// 横幅
const float Floor::AREA_WIDTH = 50.0f;
// 縦幅
const float Floor::AREA_HEIGHT = 50.0f;

// 初期化
void Floor::Initialize()
{
	// モデルをshared_ptrで受け取る
	m_pModel = std::weak_ptr<DirectX::Model>(ResourceManager::GetInstance()->GetModel(L"Resources/Models/Floor.cmo"));

	// 頂点ベクトル
	 m_vector[0] = DirectX::SimpleMath::Vector3(-AREA_WIDTH, 0.0f, -AREA_HEIGHT);  // 左上
	 m_vector[1] = DirectX::SimpleMath::Vector3(-AREA_WIDTH, 0.0f, AREA_HEIGHT);   // 左下
	 m_vector[2] = DirectX::SimpleMath::Vector3(AREA_WIDTH, 0.0f, AREA_HEIGHT);    // 右下
	 m_vector[3] = DirectX::SimpleMath::Vector3(AREA_WIDTH, 0.0f, -AREA_HEIGHT);   // 右上
}

// 描画
void Floor::Render(const DirectX::SimpleMath::Matrix& _view)
{
	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();
	DirectX::SimpleMath::Matrix proj = GameContext::Get<Projection>()->GetMatrix();

	// 行列作成
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	// モデル描画
	if (std::shared_ptr<DirectX::Model> sptr = m_pModel.lock())
	{
		sptr->Draw(context, *state, world, _view, proj);
	}
}