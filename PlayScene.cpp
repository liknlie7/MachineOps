#include "pch.h"

#include "PlayScene.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;


// ���C�t�Q�[�W�����ɂ����鎞��
const float PlayScene::DAMAGE_TIME = 1.0f;

// �R���X�g���N�^
PlayScene::PlayScene()
	: GameScene()
	, m_gameState(STATE_START)
	, m_waveState(BOSS_WAVE)
	, m_waveCount(0)
{
	bossFlag = true;
}

// �f�X�g���N�^
PlayScene::~PlayScene()
{

}

// ������
void PlayScene::Initialize()
{
	// �T�E���h�̍쐬
	m_playSceneSound = std::make_unique<Adx2Le>();
	m_playerSound = std::make_unique<Adx2Le>();

	// �T�E���h�̐ݒ�
	m_playSceneSound->Initialize(L"Resources\\Sounds\\PlayScene.acf");
	m_playerSound->Initialize(L"Resources\\Sounds\\PlayScene.acf");
	m_playSceneSound->LoadAcbFile(L"Resources\\Sounds\\PlayScene.acb");
	m_playerSound->LoadAcbFile(L"Resources\\Sounds\\Player.acb");

	// BGM�̍Đ�
	m_playSceneSound->Play(CRI_PLAYSCENE_PLAYSCENEBGM,1.0f);

	// �ǔ��J�����̍쐬
	m_pFollowCamera = make_unique<FollowCamera>();
	m_pFollowCamera->Initialize();
	GameContext::Register<FollowCamera>(m_pFollowCamera);

	// �J�[�\���̍쐬
	m_pCursor = make_unique<MouseCursor>("Mouse");

	// �t���A�쐬
	m_pFloor = make_unique<Floor>("Floor");
	m_pFloor->Initialize();

	// �Ǎ쐬
	m_pWall = make_unique<Wall>("Wall");
	m_pWall->Initialize();

	// �v���C���[�쐬
	m_pPlayer = make_unique<Player>("Player");
	m_pPlayer->Initialize();
	m_pPlayer->SetSoundPlayer(m_playerSound.get());

	// �G�쐬
	if (bossFlag)
	{
		m_pEnemy = make_unique<Enemy>(m_pEnemy->BOSS_ENEMY, "Enemy");
		m_pEnemy->Initialize(Vector3(0.0f, 1.0f, -15.0f));
	}
	if (!bossFlag)
	{
		m_pEnemies[0] = make_unique<Enemy>(m_pEnemies[0]->NORMAL_ENEMY, "Enemy");
		m_pEnemies[0]->Initialize(Vector3(10.0f, 1.0f, 5.0f));
		m_pEnemies[1] = make_unique<Enemy>(m_pEnemies[1]->NORMAL_ENEMY, "Enemy");
		m_pEnemies[1]->Initialize(Vector3(10.0f, 1.0f, 5.0f));
		m_pEnemies[2] = make_unique<Enemy>(m_pEnemies[2]->SHIELD_ENEMY, "Enemy");
		m_pEnemies[2]->Initialize(Vector3(10.0f, 1.0f, 5.0f));
		m_pEnemies[3] = make_unique<Enemy>(m_pEnemies[3]->SHIELD_ENEMY, "Enemy");
		m_pEnemies[3]->Initialize(Vector3(10.0f, 1.0f, 5.0f));
	}

	m_color = Colors::Red;

	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\GreenHP.png", nullptr, m_greenHpBarTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\RedHP.png", nullptr, m_redHpBarTexture.GetAddressOf());

	// �G�̃��C�t�f�t�H���g�X�P�[���l
	m_defaultGaugeScaleX = 1.0f;
	// ���݂̓G�̃��C�t
	m_currentGaugeScaleX = 1.0f;
	// ���̓G�̃��C�t
	m_prevGaugeScaleX = m_currentGaugeScaleX;
	// ���킶�팸�郉�C�t�Q�[�W
	m_lightGreenGaugeRate = 0;
	// �o�ߎ���
	m_totalTime = 0;
	m_gaugeFlag = false;

	//// ��ʂ��J��
	//GameContext::Get<EffectManager>()->Open();


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

	m_warningEffect = std::make_unique<WarningEffect>();
	m_warningEffect->Initialize();
	
	m_waveCount = 5;
	m_playSceneSound->Play(CRI_PLAYSCENE_WARNING, 1.0f);

}

// �X�V
void PlayScene::Update(DX::StepTimer const& _timer)
{
	float elapsedTime = float(_timer.GetElapsedSeconds());

	Keyboard::State keyState = Keyboard::Get().GetState();

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
		if (m_pPlayer->GetActiveFlag() == true)
			m_pPlayer->Update();

		// �G�X�V
		if (bossFlag)
		{
			if (m_pPlayer->GetActiveFlag() == true)
				m_pEnemy->SetPlayerPos(m_pPlayer->GetPos());
			m_pEnemy->Update();
		}
		if (!bossFlag)
		{
			for (int i = 0; i < 4; i++)
			{
				if (m_pPlayer->GetActiveFlag() == true)
					m_pEnemies[i]->SetPlayerPos(m_pPlayer->GetPos());
				m_pEnemies[i]->Update();
			}
		}

		// �ǔ��J�����X�V
		if (m_pPlayer->GetActiveFlag() == true)
			m_pFollowCamera->Update(m_pPlayer->GetPos() + FollowCamera::EYE_VEC, m_pPlayer->GetPos());

		// �J�[�\���X�V
		m_pCursor->Update();

		m_color = Colors::Red;


		// �����_
		Vector3 hitPos;

		// �}�E�XRay�Ə��̓����蔻��(�����_���o)
		if (m_pPlayer->GetActiveFlag() == true)
		{
			if (Collision::IntersectSegmentTriangle(m_pCursor->GetRayNear(), m_pCursor->GetRayFar(), m_pFloor->GetTriangle(0), &hitPos) ||
				Collision::IntersectSegmentTriangle(m_pCursor->GetRayNear(), m_pCursor->GetRayFar(), m_pFloor->GetTriangle(1), &hitPos))
			{
				m_pPlayer->SetMousePos(hitPos);
			}
		}

		// �e�̒��S�Ɣ��a��ݒ�
		if (bossFlag)
		{
			vector<Vector3> playerBullets;

			if (m_pPlayer->GetActiveFlag() == true)
				playerBullets = m_pPlayer->GetBulletPos();

			vector<Vector3> enemyBullets = m_pEnemy->GetBulletPos();

			vector<Collision::Box> playerBullet;
			vector<Collision::Sphere> enemyBullet;

			playerBullet.resize(playerBullets.size());

			enemyBullet.resize(enemyBullets.size());
			for (unsigned int i = 0; i < playerBullets.size(); i++)
			{
				playerBullet[i].center = playerBullets[i];
				playerBullet[i].radius = Vector3(0.1f, 0.1, 0.5f);
			}
			for (unsigned int i = 0; i < enemyBullets.size(); i++)
			{
				enemyBullet[i].center = enemyBullets[i];
				enemyBullet[i].radius = 0.15f;
			}
			for (unsigned int i = 0; i < playerBullet.size(); i++)
			{
				if (Collision::HitCheckSphereToBox(m_pEnemy->GetCollider(), playerBullet[i]))
				{
					m_pEnemy->OnCollision();
					m_pPlayer->m_pWeapon->BulletOnCollision(i);
					// �G�̗̑͂̔䗦�v�Z
					float greenGaugeRate = m_pEnemy->GetLife() / m_pEnemy->GetMaxLife();
					// ���݂̃Q�[�W�T�C�Y
					m_currentGaugeScaleX = m_defaultGaugeScaleX * greenGaugeRate;

				}
			}

			// �v���C���[�ƓG�̒e�̓����蔻��
			for (unsigned int i = 0; i < enemyBullet.size(); i++)
			{
				if (m_pPlayer->GetActiveFlag() == true)
				{
					if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), enemyBullet[i]))
					{
						m_pPlayer->OnCollision();
						m_pEnemy->BulletOnCollision(i);
					}
				}
			}

			// �v���C���[�ƓG�̓����蔻��
			if (m_pPlayer->GetActiveFlag() == true
				&& m_pEnemy != nullptr)
			{
				if (!m_pPlayer->GetHitFlag())
				{
					if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), m_pEnemy->GetCollider()))
					{
						m_pPlayer->OnCollision();
					}
				}
			}

			// �̗͂��O�Ȃ����
			if (m_pPlayer->GetLife() == 0)
			{
				m_pPlayer->SetActiveFlag(false);
			}

		}
		// ���U���g�V�[���֑J��
		if (m_pEnemy->GetModel() == nullptr)
		{
			GameSceneManager* gameSceneManager = GameContext::Get<GameSceneManager>();
			gameSceneManager->RequestScene("Result");
		}



		// �̗̓Q�[�W
		// �o�ߎ���
		m_totalTime += (float)_timer.GetElapsedSeconds();
		if (m_totalTime < DAMAGE_TIME)
		{
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
			m_prevGaugeScaleX = m_currentGaugeScaleX;
		}

		break;
		//case STATE_CONTINUE:
		//	break;
		//case STATE_GAMEOVERA:
		//	break;
		//default:
		//	break;
	}
}

// �`��
void PlayScene::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"PlayScene");
	debugFont->draw();
	debugFont->print(10, 40, L"[Space] Title");
	debugFont->draw();


	// �v���C���[�\��
	if (m_pPlayer->GetActiveFlag() == true)
		m_pPlayer->Render(m_pFollowCamera->GetViewMatrix());

	// �G�\��
	if (bossFlag)
		m_pEnemy->Render(m_pFollowCamera->GetViewMatrix());

	if (!bossFlag)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pEnemies[i]->Render(m_pFollowCamera->GetViewMatrix());
		}
	}

	// �t���A�̕\��
	m_pFloor->Render(m_pFollowCamera->GetViewMatrix());

	// �ǂ̕\��
	m_pWall->Render(m_pFollowCamera->GetViewMatrix());

	GameContext::Get<SpriteBatch>()->Begin(SpriteSortMode_Deferred, GameContext::Get<CommonStates>()->NonPremultiplied());
	if (bossFlag)
	{
		// �ԃQ�[�W�\��
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_redHpBarTexture.Get(), DirectX::SimpleMath::Vector2(350, 596), nullptr, Colors::Black,
			0.0f, Vector2::Zero, Vector2(1.0f, 0.2f));
		// ���΃Q�[�W�\��
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_redHpBarTexture.Get(), DirectX::SimpleMath::Vector2(350, 596), nullptr, Vector4(1.0f, 1.0f, 1.0f, 0.5f),
			0.0f, Vector2::Zero, Vector2(m_lightGreenGaugeRate, 0.2f));
		// �΃Q�[�W�\��
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_greenHpBarTexture.Get(), DirectX::SimpleMath::Vector2(350, 600), nullptr, Colors::White,
			0.0f, Vector2::Zero, Vector2(m_currentGaugeScaleX, 0.2f));

	}

	m_pCursor->Render(m_pFollowCamera->GetViewMatrix());

	m_warningEffect->Render();

	GameContext::Get<SpriteBatch>()->End();
}

// ��n��
void PlayScene::Finalize()
{
}

// �v���C��
PlayScene::GAME_STATE PlayScene::PlayGame()
{
	return STATE_GAME;
}

// ���`���
float PlayScene::Lerp(float _start, float _end, float _time)
{
	return _start + (_end - _start) * _time;
}

// ���ʐ��`���
float PlayScene::Slerp(float _start, float _end, float _time)
{
	float rate = (sinf(0.0f * DirectX::XM_PI /
		2.0f - DirectX::XM_PI * _time) + 1.0f) / 2.0f;
	return _start + (_end - _start) * rate;
}