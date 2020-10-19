#include "pch.h"

#include <CommonStates.h>

#include "Floor.h"
#include "DeviceResources.h"
#include "Projection.h"
#include "GameContext.h"
#include "ResourceManager.h"

// ����
const float Floor::AREA_WIDTH = 50.0f;
// �c��
const float Floor::AREA_HEIGHT = 50.0f;

// ������
void Floor::Initialize()
{
	// ���f����shared_ptr�Ŏ󂯎��
	m_pModel = std::weak_ptr<DirectX::Model>(ResourceManager::GetInstance()->GetModel(L"Resources/Models/Floor.cmo"));

	// ���_�x�N�g��
	 m_vector[0] = DirectX::SimpleMath::Vector3(-AREA_WIDTH, 0.0f, -AREA_HEIGHT);  // ����
	 m_vector[1] = DirectX::SimpleMath::Vector3(-AREA_WIDTH, 0.0f, AREA_HEIGHT);   // ����
	 m_vector[2] = DirectX::SimpleMath::Vector3(AREA_WIDTH, 0.0f, AREA_HEIGHT);    // �E��
	 m_vector[3] = DirectX::SimpleMath::Vector3(AREA_WIDTH, 0.0f, -AREA_HEIGHT);   // �E��
}

// �`��
void Floor::Render(const DirectX::SimpleMath::Matrix& _view)
{
	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();
	DirectX::SimpleMath::Matrix proj = GameContext::Get<Projection>()->GetMatrix();

	// �s��쐬
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	// ���f���`��
	if (std::shared_ptr<DirectX::Model> sptr = m_pModel.lock())
	{
		sptr->Draw(context, *state, world, _view, proj);
	}
}