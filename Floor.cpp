#include "pch.h"

#include "Floor.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

void Floor::Initialize()
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();

	// �G�t�F�N�g�t�@�N�g���̍쐬
	EffectFactory* factory = new EffectFactory(deviceResources->GetD3DDevice());

	// �e�N�X�`���̓ǂݍ��݃p�X�w��
	factory->SetDirectory(L"Resources/Models");

	// �t�@�C�����w�肵�ă��f���f�[�^�ǂݍ���
	m_pModel = Model::CreateFromCMO(deviceResources->GetD3DDevice(), L"Resources/Models/Floor.cmo", *factory);

	delete factory;
}

void Floor::Render(DirectX::SimpleMath::Matrix _view)
{
	DX::DeviceResources* deviceResources = GameContext<DX::DeviceResources>().Get();
	Projection* proj = GameContext<Projection>().Get();
	CommonStates* state = GameContext<CommonStates>().Get();

	Matrix world = Matrix::Identity;

	// ���f���`��
	m_pModel->Draw(deviceResources->GetD3DDeviceContext(), *state, world, _view, proj->GetMatrix());
}