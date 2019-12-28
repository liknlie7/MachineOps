#include "pch.h"

#include "Floor.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float Floor::AREA_WIDTH = 50.0f;
const float Floor::AREA_HEIGHT = 50.0f;

void Floor::Initialize()
{
	// �G�t�F�N�g�t�@�N�g���̍쐬
	EffectFactory* factory = new EffectFactory(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());

	// �e�N�X�`���̓ǂݍ��݃p�X�w��
	factory->SetDirectory(L"Resources/Models");

	// �t�@�C�����w�肵�ă��f���f�[�^�ǂݍ���
	m_pModel = Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources/Models/floor.cmo", *factory);

	delete factory;

	// ���_�x�N�g��
	 m_vector[0] = Vector3(-AREA_WIDTH, 0.0f, -AREA_HEIGHT);  // ����
	 m_vector[1] = Vector3(-AREA_WIDTH, 0.0f, AREA_HEIGHT);   // ����
	 m_vector[2] = Vector3(AREA_WIDTH, 0.0f, AREA_HEIGHT);    // �E��
	 m_vector[3] = Vector3(AREA_WIDTH, 0.0f, -AREA_HEIGHT);   // �E��
}

void Floor::Render(DirectX::SimpleMath::Matrix _view)
{
	Matrix world = Matrix::Identity;

	// ���f���`��
	m_pModel->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), *GameContext::Get<CommonStates>(), world, _view, GameContext::Get<Projection>()->GetMatrix());
}