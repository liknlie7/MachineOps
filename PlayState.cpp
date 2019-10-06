#include "pch.h"

#include "PlayState.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

PlayState::PlayState()
	: GameState()
	, m_pDebugCamera()
	, m_pGridFloor()
{

}


PlayState::~PlayState()
{
}


void PlayState::Initialize()
{

	m_pDeviceResources = GameContext<DX::DeviceResources>::Get();
	m_pDevice = m_pDeviceResources->GetD3DDevice();
	m_pDeviceContext = m_pDeviceResources->GetD3DDeviceContext();
	m_pProjection = GameContext<Projection>().Get();
	RECT size = m_pDeviceResources->GetOutputSize();

	//float aspectRatio = float(size.right) / float(size.bottom);

	// ��p��ݒ�
	//float fovAngleY = XMConvertToRadians(45.0f);

	//// �ˉe�s����쐬����
	//m_pProjection->SetPerspectiveFieldOfView(fovAngleY, aspectRatio, 0.01f, 1000.f);

	// �f�o�b�O�J�����̍쐬
	m_pDebugCamera = make_unique<DebugCamera>();

	// �f�o�b�O�t���A�̍쐬
	m_pGridFloor = make_unique<GridFloor>(10.0f, 10);

	// �R�����X�e�[�g�̍쐬
	m_pState = GameContext<CommonStates>().Get();

	// �ǔ��J�����̍쐬
	m_pFollowCamera = make_unique<FollowCamera>();
	m_pFollowCamera->Initialize();

	// �t���A������
	m_pFloor = make_unique<Floor>();
	m_pFloor->Initialize();

	// �v���C���[������
	m_pPlayer = make_unique<Player>();
	m_pPlayer->Initialize();

	// �G������
	for (int i = 0; i < 2; i++)
		m_pEnemy1[i] = make_unique<Enemy>();
	m_pEnemy1[0]->InitializeNormal(Vector3(+5.0f, 1.0f, 0.0f));
	m_pEnemy1[1]->InitializeNormal(Vector3(-5.0f, 1.0f, 0.0f));

	for (int i = 0; i < 2; i++)
		m_pEnemy2[i] = make_unique<Enemy>();
	m_pEnemy2[0]->InitializeShield(Vector3(+5.0f, 1.0f, -5.0f));
	m_pEnemy2[1]->InitializeShield(Vector3(-5.0f, 1.0f, -5.0f));

	m_color = Colors::Red;


	m_viewPort =
		Matrix::CreateScale(Vector3(.5f, -.5f, 1.f)) *
		Matrix::CreateTranslation(Vector3(.5f, .5f, 0.f)) *
		Matrix::CreateScale(Vector3(float(size.right), float(size.bottom), 1.f));
}


void PlayState::Update()
{
	Mouse::State mouseState = Mouse::Get().GetState();
	Keyboard::State keyState = Keyboard::Get().GetState();

	if (keyState.IsKeyDown(Keyboard::Space))
	{
		GameStateManager* gameStateManager = GameContext<GameStateManager>().Get();
		gameStateManager->RequestState("Title");
	}

	// �v���C���[�X�V
	m_pPlayer->Update();

	// �G�X�V
	for (int i = 0; i < 2; i++)
	{
		m_pEnemy1[i]->UpdateNormal(m_pPlayer->GetPos());
		m_pEnemy2[i]->UpdateShield(m_pPlayer->GetPos());
	}

	// �f�o�b�O�J�����X�V
	m_pDebugCamera->update();

	// �ǔ��J�����X�V
	m_pFollowCamera->Update(m_pPlayer->GetPos() + FollowCamera::EYE_VEC, m_pPlayer->GetPos());

	m_color = Colors::Red;

	// �}�E�X���W�����[���h���W�֕ϊ�
	// �}�E�XRay�̍쐬
	Vector3 mousePos = Vector3::Transform(Vector3(mouseState.x, mouseState.y, 0), m_viewPort.Invert());
	Vector3 pointNear = Vector3(mousePos.x, mousePos.y, 0.0f);
	Vector3 pointFar = Vector3(mousePos.x, mousePos.y, 1.0f);
	Matrix inverseviewproj = (m_pFollowCamera->getViewMatrix() *  m_pProjection->GetMatrix()).Invert();
	Vector3 rayNear = Vector3::Transform(pointNear, inverseviewproj);
	Vector3 rayFar = Vector3::Transform(pointFar, inverseviewproj);
	Vector3 raySubtraction = rayFar - rayNear;
	Vector3 rayDirection = raySubtraction;
	// ���K��
	rayDirection.Normalize();

	// ���_�x�N�g��
	Vector3 v0 = Vector3(-50.0f, 0.0f, -50.0f);  // ����
	Vector3 v1 = Vector3(-50.0f, 0.0f, 50.0f);   // ����
	Vector3 v2 = Vector3(50.0f, 0.0f, 50.0f);    // �E��
	Vector3 v3 = Vector3(50.0f, 0.0f, -50.0f);   // �E��

	// �����_
	Vector3 hitPos;

	// �O�p�`���쐬
	Collision::Triangle tri1(v0, v2, v1);
	Collision::Triangle tri2(v0, v3, v2);

	// �}�E�XRay�ƎO�p�`�̓����蔻��(�����_���o)
	if (Collision::IntersectSegmentTriangle(rayNear, raySubtraction, tri1, &hitPos) ||
		Collision::IntersectSegmentTriangle(rayNear, raySubtraction, tri2, &hitPos))
	{
		m_pPlayer->SetMousePos(hitPos);
	}

	// �G�A�e�̒��S�Ɣ��a��ݒ�
	Collision::Sphere enemy1[2], enemy2[2];

	for (int i = 0; i < 2; i++)
	{
		enemy1[i].center = m_pEnemy1[i]->GetPos();					enemy1[i].radius = 1.0f;
		enemy2[i].center = m_pEnemy2[i]->GetPos();					enemy2[i].radius = 1.0f;
	}
	vector<Vector3> bullets = m_pPlayer->GetBulletPos();

	vector<Collision::Sphere> colBullet;
	colBullet.resize(bullets.size());

	for (int i = 0; i < bullets.size(); i++)
	{
		colBullet[i].center = bullets[i];
		colBullet[i].radius = 0.15f;
	}
	for (int i = 0; i < colBullet.size(); i++)
	{
		if (Collision::HitCheckSphereToSphere(enemy1[0], colBullet[i]))
		{
			m_pEnemy1[0]->SetHitFlag(true);
			m_pEnemy1[0]->DownLife(-1);
		}
		if (Collision::HitCheckSphereToSphere(enemy1[1], colBullet[i]))
		{
			m_pEnemy1[1]->SetHitFlag(true);
			m_pEnemy1[1]->DownLife(-1);
		}
		if (Collision::HitCheckSphereToSphere(enemy2[0], colBullet[i]))
		{
			m_pEnemy2[0]->SetHitFlag(true);
			m_pEnemy2[0]->DownLife(-1);
		}
		if (Collision::HitCheckSphereToSphere(enemy2[1], colBullet[i]))
		{
			m_pEnemy2[1]->SetHitFlag(true);
			m_pEnemy2[1]->DownLife(-1);
		}

	}

	// �v���C���[�ƓG�Ƃ̐ڐG����
	for (int i = 0; i < 2; i++)
	{
		if (!m_pPlayer->GetHitFlag())
			if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), enemy1[i]))
				m_pPlayer->SetHitFlag(true);

		if (!m_pPlayer->GetHitFlag())
			if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), enemy2[i]))
				m_pPlayer->SetHitFlag(true);
	}
}


void PlayState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"PlayState");
	debugFont->draw();
	debugFont->print(10, 40, L"[Space] Title");
	debugFont->draw();

	// �v���C���[�\��
	m_pPlayer->Render(m_pFollowCamera->getViewMatrix());

	// �G�\��
	for (int i = 0; i < 2; i++)
	{
		m_pEnemy1[i]->Render(m_pFollowCamera->getViewMatrix());
		m_pEnemy2[i]->Render(m_pFollowCamera->getViewMatrix());
	}

	// ���̕\��
	m_pFloor->Render(m_pFollowCamera->getViewMatrix());

	//-----�f�o�b�O�p(����ȊO���ׂď���----------------------------------
	// �f�o�b�O�p���̕\��
	//m_pDebugFloor->Draw(context, debugCamera->getViewMatrix(), m_projection);

	//// �v���C���[�\��
	////m_pPlayer->Render(*m_pState.get(), debugCamera->getViewMatrix(), m_projection, m_color);

	//// �G�\��
	////m_pEnemy->Render(deviceResources->GetD3DDeviceContext(), *m_pState.get(), m_pFollowCamera->getViewMatrix(), m_projection, static_cast<Vector4>(Colors::Blue));

	//// ���̕\��
	////m_pFloor->Render(deviceResources->GetD3DDeviceContext(), *m_pState.get(), m_pDebugCamera->getViewMatrix(), m_projection);

	//----------------------------------------------------------------

}


void PlayState::Finalize()
{
	m_pDebugCamera.reset();
	m_pGridFloor.reset();
}