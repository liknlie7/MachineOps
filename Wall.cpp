#include "pch.h"
#include "Wall.h"

// �R���X�g���N�^
Wall::Wall()
{
}

// ������
void Wall::Initialize()
{
	// �G�t�F�N�g�t�@�N�g���̍쐬
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());

	// �e�N�X�`���̓ǂݍ��݃p�X�w��
	factory->SetDirectory(L"Resources/Models");

	// �t�@�C�����w�肵�ă��f���f�[�^�ǂݍ���
	m_pModel = DirectX::Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources/Models/Wall.cmo", *factory);

	delete factory;

	m_collider[TOP_RIGHT].center = DirectX::SimpleMath::Vector3(-26.0f, 2.5f, -21.0f);
	m_collider[TOP_RIGHT].radius = DirectX::SimpleMath::Vector3(20.0f, 5.0f, 1.5f);
	m_collider[TOP_LEFT].center = DirectX::SimpleMath::Vector3(26.0f, 2.5f, -21.0f);
	m_collider[TOP_LEFT].radius = DirectX::SimpleMath::Vector3(20.0f, 5.0f, 1.5f);
	m_collider[BOTTOM_RIGHT].center = DirectX::SimpleMath::Vector3(-26.0f, 2.5f, 24.0f);
	m_collider[BOTTOM_RIGHT].radius = DirectX::SimpleMath::Vector3(20.0f, 5.0f, 1.5f);
	m_collider[BOTTOM_LEFT].center = DirectX::SimpleMath::Vector3(26.0f, 2.5f, 24.0f);
	m_collider[BOTTOM_LEFT].radius = DirectX::SimpleMath::Vector3(20.0f, 5.0f, 1.5f);
	m_collider[LEFT_TOP].center = DirectX::SimpleMath::Vector3(-22.0f, 2.5f, -26.0f);
	m_collider[LEFT_TOP].radius = DirectX::SimpleMath::Vector3(1.5f, 5.0f, 20.0f);
	m_collider[LEFT_BOTTOM].center = DirectX::SimpleMath::Vector3(-22.0f, 2.5f, 27.0f);
	m_collider[LEFT_BOTTOM].radius = DirectX::SimpleMath::Vector3(1.5f, 5.0f, 20.0f);
	m_collider[RIGHT_TOP].center = DirectX::SimpleMath::Vector3(22.0f, 2.5f, -26.0f);
	m_collider[RIGHT_TOP].radius = DirectX::SimpleMath::Vector3(1.5f, 5.0f, 20.0f);
	m_collider[RIGHT_BOTTOM].center = DirectX::SimpleMath::Vector3(22.0f, 2.5f, 27.0f);
	m_collider[RIGHT_BOTTOM].radius = DirectX::SimpleMath::Vector3(1.5f, 5.0f, 20.0f);
}

// �`��
void Wall::Render(const DirectX::SimpleMath::Matrix & _view)
{
	// �s��쐬
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateScale(0.3f, 0.3f, 0.3f);

	// ���f���`��
	m_pModel->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), *GameContext::Get<DirectX::CommonStates>(), world, _view, GameContext::Get<Projection>()->GetMatrix());
}
