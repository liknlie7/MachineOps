#include "pch.h"

#include "Floor.h"

// ����
const float Floor::AREA_WIDTH = 50.0f;
// �c��
const float Floor::AREA_HEIGHT = 50.0f;

// �R���X�g���N�^
Floor::Floor()
{

}

// ������
void Floor::Initialize()
{
	// �G�t�F�N�g�t�@�N�g���̍쐬
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());

	// �e�N�X�`���̓ǂݍ��݃p�X�w��
	factory->SetDirectory(L"Resources/Models");

	// �t�@�C�����w�肵�ă��f���f�[�^�ǂݍ���
	m_pModel = DirectX::Model::CreateFromCMO(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources/Models/floor.cmo", *factory);

	delete factory;

	// ���_�x�N�g��
	 m_vector[0] = DirectX::SimpleMath::Vector3(-AREA_WIDTH, 0.0f, -AREA_HEIGHT);  // ����
	 m_vector[1] = DirectX::SimpleMath::Vector3(-AREA_WIDTH, 0.0f, AREA_HEIGHT);   // ����
	 m_vector[2] = DirectX::SimpleMath::Vector3(AREA_WIDTH, 0.0f, AREA_HEIGHT);    // �E��
	 m_vector[3] = DirectX::SimpleMath::Vector3(AREA_WIDTH, 0.0f, -AREA_HEIGHT);   // �E��
}

// �X�V
void Floor::Update()
{

}

// �`��
void Floor::Render(const DirectX::SimpleMath::Matrix& _view)
{
	// �s��쐬
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	// ���f���`��
	m_pModel->Draw(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext(), *GameContext::Get<DirectX::CommonStates>(), world, _view, GameContext::Get<Projection>()->GetMatrix());
}