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

// ������
void Wall::Initialize()
{
	// ���f����shared_ptr�Ŏ󂯎��
	m_pModel = std::weak_ptr<DirectX::Model>(ResourceManager::GetInstance()->GetModel(L"Resources/Models/Wall.cmo"));

	// CSV�ǂݍ���
	CreateWall ();
}

// �`��
void Wall::Render(const DirectX::SimpleMath::Matrix & _view)
{
	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();
	DirectX::SimpleMath::Matrix proj = GameContext::Get<Projection>()->GetMatrix();

	// �s��쐬
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateScale(0.3f, 0.3f, 0.3f);

	// ���f���`��
	if (std::shared_ptr<DirectX::Model> sptr = m_pModel.lock())
	{
		sptr->Draw(context, *state, world, _view, proj);
	}
}

// �ǂ̍쐬
void Wall::CreateWall()
{
	// �t�@�C���ǂݍ���
	std::ifstream ifs("Resources\\csv\\WallData.csv");

	std::string lineBuf;

	std::vector<std::vector<std::string>> csvData;

	// ��ǂݍ���
	while (std::getline(ifs, lineBuf))
	{
		csvData.push_back(std::vector<std::string>());

		std::stringstream stream(lineBuf);

		std::string indexBuf;

		// �s�ǂݍ���
		while (std::getline(stream, indexBuf, ','))
		{
			(*(csvData.end() - 1)).push_back(indexBuf);
		}
	}

	// �ǂ̐���ݒ�
	int wallNum = 8;

	// �f�[�^��ϊ����Ă��ꂼ��i�[
	for (int i = 1; i < wallNum; i++)
	{
		m_collider[stoi(csvData[i][0])].center = DirectX::SimpleMath::Vector3(stof(csvData[i][1]), stof(csvData[i][2]), stof(csvData[i][3]));
		m_collider[stoi(csvData[i][0])].radius = DirectX::SimpleMath::Vector3(stof(csvData[i][4]), stof(csvData[i][5]), stof(csvData[i][6]));
	}
}
