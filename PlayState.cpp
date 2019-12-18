#include "pch.h"

#include "PlayState.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

// �R���X�g���N�^
PlayState::PlayState()
	: GameState()
{

}

// �f�X�g���N�^
PlayState::~PlayState()
{
}

// ������
void PlayState::Initialize()
{
	// �ǔ��J�����̍쐬
	m_pFollowCamera = make_unique<FollowCamera>();
	m_pFollowCamera->Initialize();

	// �t���A�쐬
	m_pFloor = make_unique<Floor>();
	m_pFloor->Initialize();

	// �v���C���[�쐬
	m_pPlayer = make_unique<Player>();
	m_pPlayer->Initialize();

	// �G�쐬
	m_pEnemy = make_unique<Enemy>(m_pEnemy->BOSS_TYPE);
	m_pEnemy->Initialize(Vector3(0.0f, 1.0f, -15.0f));

	m_color = Colors::Red;

	// �r���[�|�[�g�̍쐬
	RECT size = GameContext::Get<DX::DeviceResources>()->GetOutputSize();
	m_viewPort =
		Matrix::CreateScale(Vector3(.5f, -.5f, 1.f)) *
		Matrix::CreateTranslation(Vector3(.5f, .5f, 0.f)) *
		Matrix::CreateScale(Vector3(float(size.right), float(size.bottom), 1.f));

	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\GreenHP.png", nullptr, m_greenHpBarTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\RedHP.png", nullptr, m_redHpBarTexture.GetAddressOf());

	// HP�p
	m_gaugeDefaultPositionX = 350;
	m_gaugeDefaultScaleX = 1.0f;
	m_currentGaugePositionX = 350;
	m_prevGaugePositionX = m_currentGaugePositionX;
	m_currentGaugeScaleX = 1.0f;
	m_prevGaugeScaleX = m_currentGaugeScaleX;
}

// �X�V
void PlayState::Update(DX::StepTimer const& timer)
{
	Mouse::State mouseState = Mouse::Get().GetState();
	Keyboard::State keyState = Keyboard::Get().GetState();

	// �v���C���[�X�V
	m_pPlayer->Update();

	// �G�X�V
	m_pEnemy->SetPlayerPos(m_pPlayer->GetPos());
	m_pEnemy->Update();

	// �ǔ��J�����X�V
	m_pFollowCamera->Update(m_pPlayer->GetPos() + FollowCamera::EYE_VEC, m_pPlayer->GetPos());

	m_color = Colors::Red;

	// �}�E�X���W�����[���h���W�֕ϊ�
	// �}�E�XRay�̍쐬
	Vector3 mousePos = Vector3::Transform(Vector3((float)mouseState.x, (float)mouseState.y, 0), m_viewPort.Invert());
	Vector3 pointNear = Vector3(mousePos.x, mousePos.y, 0.0f);
	Vector3 pointFar = Vector3(mousePos.x, mousePos.y, 1.0f);
	Matrix inverseviewproj = (m_pFollowCamera->getViewMatrix() *  GameContext::Get<Projection>()->GetMatrix()).Invert();
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
	if (Collision::IntersectSegmentTriangle(rayNear, rayFar, tri1, &hitPos) ||
		Collision::IntersectSegmentTriangle(rayNear, rayFar, tri2, &hitPos))
	{
		m_pPlayer->SetMousePos(hitPos);
		geoVec = hitPos;
	}

	// �����n�_�f�o�b�O
	geoMat = Matrix::CreateTranslation(geoVec);

	// �e�̒��S�Ɣ��a��ݒ�
	vector<Vector3> playerBullets = m_pPlayer->GetBulletPos();
	vector<Vector3> enemyBullets = m_pEnemy->GetBulletPos();

	vector<Collision::Sphere> playerBullet;
	vector<Collision::Sphere> enemyBullet;

	playerBullet.resize(playerBullets.size());
	enemyBullet.resize(enemyBullets.size());

	for (unsigned int i = 0; i < playerBullets.size(); i++)
	{
		playerBullet[i].center = playerBullets[i];
		playerBullet[i].radius = 0.15f;
	}
	for (unsigned int i = 0; i < enemyBullets.size(); i++)
	{
		enemyBullet[i].center = enemyBullets[i];
		enemyBullet[i].radius = 0.15f;
	}

	for (unsigned int i = 0; i < playerBullet.size(); i++)
	{
		if (Collision::HitCheckSphereToSphere(m_pEnemy->GetCollider(), playerBullet[i]))
		{
			m_pEnemy->OnCollision();
			m_prevGaugeScaleX = m_currentGaugeScaleX;
			m_prevGaugePositionX = m_currentGaugePositionX;
			m_pPlayer->m_pWeapon->BulletOnCollision(i);
		}
	}
	for (unsigned int i = 0; i < enemyBullet.size(); i++)
	{
		if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), enemyBullet[i]))
		{
			m_pPlayer->SetHitFlag(true);
			m_pEnemy->BulletOnCollision(i);
		}
	}

	// �v���C���[�ƓG�Ƃ̐ڐG����
	if (!m_pPlayer->GetHitFlag())
		if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), m_pEnemy->GetCollider()))
			m_pPlayer->SetHitFlag(true);

	// ���U���g�V�[���֑J��
	if (m_pEnemy->GetModel() == nullptr)
	{
		GameStateManager* gameStateManager = GameContext::Get<GameStateManager>();
		gameStateManager->RequestState("Result");
	}
	// �̗͂̔䗦�v�Z
	float lifeRate = m_pEnemy->GetCurrentLife() / m_pEnemy->GetMaxLife();
	// �Q�[�W�̃T�C�Y�ύX
	m_currentGaugeScaleX = m_gaugeDefaultScaleX * lifeRate;
	// �T�C�Y�ύX�ɍ��킹�ďꏊ���ړ�
	m_currentGaugePositionX = m_gaugeDefaultPositionX - m_gaugeDefaultScaleX * (1 - lifeRate) * 0.5;
}

// �`��
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
	m_pEnemy->Render(m_pFollowCamera->getViewMatrix());

	// ���̕\��
	m_pFloor->Render(m_pFollowCamera->getViewMatrix());

	GameContext::Get<SpriteBatch>()->Begin(SpriteSortMode_Deferred, GameContext::Get<CommonStates>()->NonPremultiplied());
	////// �ԃQ�[�W�\��
	////GameContext::Get<DirectX::SpriteBatch>()->Draw(m_redHpBarTexture.Get(), DirectX::SimpleMath::Vector2(350, 596), nullptr, Colors::White,
	////	0.0f, Vector2::Zero, Vector2(1.0f, 0.2f));
	// ���΃Q�[�W�\��
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_greenHpBarTexture.Get(), DirectX::SimpleMath::Vector2(m_prevGaugePositionX + (m_currentGaugePositionX - m_prevGaugePositionX) * 0.01f, 600), nullptr, Vector4(1.0f, 1.0f, 1.0f, 0.5f),
		0.0f, Vector2::Zero, Vector2(m_prevGaugeScaleX + (m_currentGaugeScaleX - m_prevGaugeScaleX) * 0.01f, 0.2f));
	// �΃Q�[�W�\��
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_greenHpBarTexture.Get(), DirectX::SimpleMath::Vector2(m_currentGaugePositionX, 600), nullptr, Colors::White,
		0.0f, Vector2::Zero, Vector2(m_currentGaugeScaleX, 0.2f));

	GameContext::Get<SpriteBatch>()->End();

}

// ��n��
void PlayState::Finalize()
{
}