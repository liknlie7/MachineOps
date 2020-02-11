#include "pch.h"
#include "Wall.h"

// �R���X�g���N�^
Wall::Wall(const std::string & _tag)
	: GameObject(_tag)
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

}

// �X�V
void Wall::Update()
{
}

// �`��
void Wall::Render(const DirectX::SimpleMath::Matrix & _view)
{
	// �s��쐬
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateScale(0.5f, 0.5f, 0.5f);

	// ���f���`��
	m_pModel->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), *GameContext::Get<DirectX::CommonStates>(), world, _view, GameContext::Get<Projection>()->GetMatrix());
}
