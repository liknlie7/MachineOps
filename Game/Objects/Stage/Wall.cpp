#include "../../pch.h"

#include <SimpleMath.h>
#include <sstream>
#include <fstream>

#include "../../Manager/ResourceManager.h"
#include "../../Manager/Collision.h"
#include "../../Common/GameContext.h"
#include "../../Common/DeviceResources.h"
#include "../../Common/Projection.h"
#include "Wall.h"

// 初期化
void Wall::Initialize()
{
	// モデルをshared_ptrで受け取る
	m_pModel = std::weak_ptr<DirectX::Model>(ResourceManager::GetInstance()->GetModel(L"Resources/Models/Wall.cmo"));

	// CSV読み込み
	CreateWall ();
}

// 描画
void Wall::Render(const DirectX::SimpleMath::Matrix & _view)
{
	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();
	DirectX::SimpleMath::Matrix proj = GameContext::Get<Projection>()->GetMatrix();

	// 行列作成
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateScale(0.3f, 0.3f, 0.3f);

	// モデル描画
	if (std::shared_ptr<DirectX::Model> sptr = m_pModel.lock())
	{
		sptr->Draw(context, *state, world, _view, proj);
	}
}

// 壁の作成
void Wall::CreateWall()
{
	// ファイル読み込み
	std::ifstream ifs("Resources\\csv\\WallData.csv");

	std::string lineBuf;

	std::vector<std::vector<std::string>> csvData;

	// 列読み込み
	while (std::getline(ifs, lineBuf))
	{
		csvData.push_back(std::vector<std::string>());

		std::stringstream stream(lineBuf);

		std::string indexBuf;

		// 行読み込み
		while (std::getline(stream, indexBuf, ','))
		{
			(*(csvData.end() - 1)).push_back(indexBuf);
		}
	}

	// 壁の数を設定
	int wallNum = 8;

	// データを変換してそれぞれ格納
	for (int i = 1; i < wallNum; i++)
	{
		m_collider[stoi(csvData[i][0])].center = DirectX::SimpleMath::Vector3(stof(csvData[i][1]), stof(csvData[i][2]), stof(csvData[i][3]));
		m_collider[stoi(csvData[i][0])].radius = DirectX::SimpleMath::Vector3(stof(csvData[i][4]), stof(csvData[i][5]), stof(csvData[i][6]));
	}
}
