#include "../../pch.h"

#include <Keyboard.h>
#include <CommonStates.h>

#include "../Common/DeviceResources.h"
#include "../Manager/ResourceManager.h"
#include "../Common/GameContext.h"
#include "../Effects/Effectmask.h"
#include "../Sound/PlayerSound.h"
#include "../Sound/PlaySceneSound.h"
#include "../Manager/Collision.h"
#include "PlayScene.h"

// �G�l�~�[(�{�X)�����ʒu
const DirectX::SimpleMath::Vector3 PlayScene::ENEMY_BOSS_INIT_POS = DirectX::SimpleMath::Vector3(0.0f, 1.0f, -15.0f);

// ���C�t�Q�[�W�����ɂ����鎞��
const float PlayScene::DAMAGE_TIME = 1.0f;

// HP�Q�[�W�X�P�[���l
const float PlayScene::HP_SCALE_X = 1.0f;
const float PlayScene::HP_SCALE_Y = 0.2f;

// HP�Q�[�W�ʒu
const DirectX::SimpleMath::Vector2 PlayScene::HP_RED_POS = DirectX::SimpleMath::Vector2(350, 596);
const DirectX::SimpleMath::Vector2 PlayScene::HP_GREEN_POS = DirectX::SimpleMath::Vector2(350, 600);

// �����Q�[�W�p
const DirectX::SimpleMath::Vector4 PlayScene::HP_GAUGE_COLOR = DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 0.5f);

// �R���X�g���N�^
PlayScene::PlayScene()
	: m_gameState(STATE_START)
	, m_waveState(BOSS_WAVE)
{

}

// �f�X�g���N�^
PlayScene::~PlayScene()
{
	m_pSound.reset();
}

// ������
void PlayScene::Initialize()
{
	// �T�E���h��shared_ptr���󂯎��
	m_pSound = std::weak_ptr<Adx2Le>(ResourceManager::GetInstance()->GetSound(L"Resources\\Sounds\\PlayScene"));

	// �ǔ��J�����̍쐬
	m_pFollowCamera = std::make_unique<FollowCamera>();
	m_pFollowCamera->Initialize();
	GameContext::Register<FollowCamera>(m_pFollowCamera);

	// �J�[�\���̍쐬
	m_pReticle = std::make_unique<Reticle>();

	// �t���A�쐬
	m_pFloor = std::make_unique<Floor>();
	m_pFloor->Initialize();

	// �Ǎ쐬
	m_pWall = std::make_unique<Wall>();
	m_pWall->Initialize();

	// �e�Ǘ��p�I�u�W�F�N�g�쐬
	m_pBulletManager = std::make_unique<BulletManager>();
	m_pBulletManager->Initialize();

	// �v���C���[�쐬
	m_pPlayer = std::make_unique<Player>();
	m_pPlayer->Initialize();
	m_pPlayer->SetBulletManager(m_pBulletManager.get());

	// �G�l�~�[�f�[�^�̓ǂݍ���
	ResourceManager::GetInstance()->LoadEnemyData();

	// �G�l�~�[�쐬
	m_pEnemy = std::make_unique<Enemy>(ResourceManager::GetInstance()->GetEnemyData(Enemy::BOSS_ENEMY - 1));
	m_pEnemy->Initialize(ENEMY_BOSS_INIT_POS);
	m_pEnemy->SetBulletManager(m_pBulletManager.get());

	// �e�N�X�`���f�[�^���󂯎��
	m_textures[GREEN_HP] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\GreenHP.png");
	m_textures[RED_HP] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\RedHP.png");

	// �G�l�~�[�̃��C�t�f�t�H���g�X�P�[���l�̏�����
	m_defaultGaugeScaleX = 1.0f;

	// ���݂̃G�l�~�[�̃��C�t�X�P�[���l�̏�����
	m_currentGaugeScaleX = 1.0f;

	// �O�̃��C�t�X�P�[���l��ݒ�
	m_prevGaugeScaleX = m_currentGaugeScaleX;

	// ���킶�팸�郉�C�t�Q�[�W�̏�����
	m_lightGreenGaugeRate = 0;

	// �o�ߎ��ԏ�����
	m_totalTime = 0;

	// �̗̓Q�[�W�t���O
	m_gaugeFlag = false;

	// ��ʂ��J��
	GameContext::Get<EffectMask>()->Open();

	// �G�t�F�N�g�̍쐬
	m_batchEffect = std::make_unique<DirectX::BasicEffect>(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());
	m_batchEffect->SetTextureEnabled(true);
	m_batchEffect->SetVertexColorEnabled(true);
	GameContext::Register<DirectX::BasicEffect>(m_batchEffect);

	// ���̓��C�A�E�g����
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	GameContext::Get<DX::DeviceResources>()->GetD3DDevice()->
		CreateInputLayout(DirectX::VertexPositionColorTexture::InputElements,
			DirectX::VertexPositionColorTexture::InputElementCount,
			shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf());

	// �v���~�e�B�u�o�b�`�̍쐬
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext());

	// Warning�G�t�F�N�g�̍쐬
	m_warningEffect = std::make_unique<WarningEffect>();
	m_warningEffect->Initialize();

	// BGM�̍Đ�
	if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
	{
		sptr->Play(CRI_PLAYSCENE_PLAYSCENEBGM);
	}

	// Warning�Đ�
	if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
	{
		sptr->Play(CRI_PLAYSCENE_WARNING);
	}
}

// �X�V
void PlayScene::Update(DX::StepTimer const& _timer)
{
	float elapsedTime = float(_timer.GetElapsedSeconds());

	// �L�[�{�[�h�擾
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	// �G�t�F�N�g�}�X�N�擾
	EffectMask* fadeEffect = GameContext::Get<EffectMask>();


	switch (m_gameState)
	{
	case STATE_START:

		if (m_waveState == NORMAL_WAVE)
		{
			fadeEffect->Open();

			// ��ʂ��J���܂ł܂�
			if (fadeEffect->IsOpen())
			{
				// �Q�[���X�e�[�g���Q�[�����ɕύX
				m_gameState = STATE_GAME;
			}
		}

		if (m_waveState == BOSS_WAVE)
		{

			m_warningEffect->Update(elapsedTime);

			if (m_warningEffect->IsEnd())
			{
				m_gameState = STATE_GAME;
			}
		}
		break;

	case STATE_GAME:

		// �v���C���[�X�V
		m_pPlayer->Update();

		// �v���C���[�̍��W���G�l�~�[�ɓn��
		m_pEnemy->SetPlayerPos(m_pPlayer->GetPosition());

		// �G�l�~�[�X�V
		m_pEnemy->Update();

		// �ǔ��J�����X�V
		m_pFollowCamera->Update(m_pPlayer->GetPosition() + FollowCamera::EYE_VEC, m_pPlayer->GetPosition());

		// �J�[�\���X�V
		m_pReticle->Update();

		// �e�X�V
		m_pBulletManager->Update();

		// �����蔻��X�V
		CollisionUpdate();

		// �G��HP�X�V
		HpGaugeUpdate(_timer);

		break;
	}
}

// �`��
void PlayScene::Render()
{
	// �v���C���[�\��
	m_pPlayer->Render(m_pFollowCamera->GetViewMatrix());

	// �G�l�~�[�\��
	m_pEnemy->Render(m_pFollowCamera->GetViewMatrix());

	// �e�`��
	m_pBulletManager->Render(m_pFollowCamera->GetViewMatrix());

	// �t���A�̕\��
	m_pFloor->Render(m_pFollowCamera->GetViewMatrix());

	// �ǂ̕\��
	m_pWall->Render(m_pFollowCamera->GetViewMatrix());

	GameContext::Get<DirectX::SpriteBatch>()->Begin(DirectX::SpriteSortMode_Deferred, GameContext::Get<DirectX::CommonStates>()->NonPremultiplied());
	// �ԃQ�[�W�\��
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_textures[RED_HP].Get(), HP_RED_POS, nullptr, DirectX::Colors::Black,
		0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(HP_SCALE_X, HP_SCALE_Y));
	// ���΃Q�[�W�\��
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_textures[RED_HP].Get(), HP_RED_POS, nullptr, HP_GAUGE_COLOR,
		0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(m_lightGreenGaugeRate, HP_SCALE_Y));
	// �΃Q�[�W�\��
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_textures[GREEN_HP].Get(), HP_GREEN_POS, nullptr, DirectX::Colors::White,
		0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(m_currentGaugeScaleX, HP_SCALE_Y));

	// �J�[�\���̕`��
	m_pReticle->Render();

	// Warning�G�t�F�N�g�`��
	m_warningEffect->Render();

	GameContext::Get<DirectX::SpriteBatch>()->End();
}

// �����蔻��X�V
void PlayScene::CollisionUpdate()
{
	// �����_
	DirectX::SimpleMath::Vector3 hitPos;

	// �}�E�XRay�Ə��̓����蔻��(�����_���o)
	if (Collision::IntersectSegmentTriangle(m_pReticle->GetRayNear(), m_pReticle->GetRayFar(), m_pFloor->GetTriangle(0), &hitPos) ||
		Collision::IntersectSegmentTriangle(m_pReticle->GetRayNear(), m_pReticle->GetRayFar(), m_pFloor->GetTriangle(1), &hitPos))
	{
		m_pPlayer->SetMousePos(hitPos);
	}

	// �v���C���[�ƃG�l�~�[�̒e�p�z��
	std::vector<Bullet*> playerBullets;
	std::vector<Bullet*> enemyBullets;

	for (int i = 0; i < m_pBulletManager->NUM_BULLET; i++)
	{
		// �v���C���[�ƃG�l�~�[�̒e���擾����
		Bullet* bullet = m_pBulletManager->GetBulletInfo(i);
		if (bullet) {
			const std::string& tag = bullet->GetTag();
			if (tag == "BOX") {
				playerBullets.push_back(bullet);
			}
			else if (tag == "SPHERE") {
				enemyBullets.push_back(bullet);
			}
		}
	}

	// ����p
	std::vector<Collision::Box> playerBulletColliders;
	std::vector<Collision::Sphere> enemyBulletColliders;

	// �e�̐���������p�̔z����쐬
	playerBulletColliders.resize(playerBullets.size());
	enemyBulletColliders.resize(enemyBullets.size());

	// �v���C���[�̒e�̔���ݒ�
	for (unsigned int i = 0; i < playerBullets.size(); i++)
	{
		playerBulletColliders[i].center = playerBullets[i]->GetPosition();
		playerBulletColliders[i].radius = m_pBulletManager->BOX_BULLET_SIZE;
	}

	// �G�l�~�[�̒e�̔���ݒ�
	for (unsigned int i = 0; i < enemyBullets.size(); i++)
	{
		enemyBulletColliders[i].center = enemyBullets[i]->GetPosition();
		enemyBulletColliders[i].radius = m_pBulletManager->SPHERE_BULLET_RADIUS;
	}

	// �v���C���[�̒e�ƃG�l�~�[�̓����蔻��
	for (unsigned int i = 0; i < playerBullets.size(); i++)
	{
		// �v���C���[�̒e���g�p���Ȃ�
		if (playerBullets[i]->GetIsUsed())
		{
			// ���ƃ{�b�N�X�̓����蔻��
			if (Collision::HitCheckSphereToBox(m_pEnemy->GetCollider(), playerBulletColliders[i]))
			{
				m_pEnemy->OnCollision();

				// �v���C���[�̒e�𖢎g�p�ɐݒ肷��
				playerBullets[i]->SetIsUsed(false);

				// �G�l�~�[�̗̑̓Q�[�W�����炷
				float greenGaugeRate = m_pEnemy->GetLife() / m_pEnemy->GetMaxLife();
				m_currentGaugeScaleX = m_defaultGaugeScaleX * greenGaugeRate;

				if (m_pEnemy->GetLife() == 0)
				{
					// �T�E���h���~������
					if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
						sptr->Stop();

					SceneManager::GetInstance()->RequestScene(eScene::RESULT_CLEAR);
				}
			}
		}
	}

	// �v���C���[�ƃG�l�~�[�̒e�̓����蔻��
	for (unsigned int i = 0; i < enemyBullets.size(); i++)
	{
		if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), enemyBulletColliders[i]))
		{
	// �T�E���h���~������
	if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
		sptr->Stop();

			// �Q�[���I�[�o�[�ֈڍs
			SceneManager::GetInstance()->RequestScene(eScene::RESULT_GAMEOVER);
		}
	}

	// �ǂƃG�l�~�[�̒e�̓����蔻��
	for (unsigned int i = 0; i < enemyBullets.size(); i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Collision::HitCheckSphereToBox(enemyBulletColliders[i], m_pWall->GetCollider(j)))
			{
				// �G�l�~�[�̒e�𖢎g�p�ɐݒ�
				enemyBullets[i]->SetIsUsed(false);
			}
		}
	}

	// �v���C���[�ƃG�l�~�[�̓����蔻��
	if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), m_pEnemy->GetCollider()))
	{
		m_pPlayer->OnCollision();
	}
}

// �G�l�~�[��HP�X�V
void PlayScene::HpGaugeUpdate(DX::StepTimer const& _timer)
{
	// �o�ߎ���
	m_totalTime += (float)_timer.GetElapsedSeconds();

	if (m_totalTime < DAMAGE_TIME)
	{
		// �Q�[�W������������
		float time = m_totalTime / DAMAGE_TIME;
		m_lightGreenGaugeRate = Lerp(m_prevGaugeScaleX, m_currentGaugeScaleX, time);
		m_gaugeFlag = false;
	}
	else
	{
		m_totalTime = 0;
		m_gaugeFlag = true;
	}
	if (m_gaugeFlag)
	{
		// ���݂̃X�P�[���l��ۑ����Ă���
		m_prevGaugeScaleX = m_currentGaugeScaleX;
	}

}


// ���`���
float PlayScene::Lerp(float _start, float _end, float _time)
{
	return _start + (_end - _start) * _time;
}