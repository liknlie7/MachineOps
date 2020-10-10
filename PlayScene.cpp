#include "pch.h"

#include "PlayScene.h"

// ライフゲージ減少にかかる時間
const float PlayScene::DAMAGE_TIME = 1.0f;

// コンストラクタ
PlayScene::PlayScene()
	: GameScene()
	, m_gameState(STATE_START)
	, m_waveState(BOSS_WAVE)
	, m_waveCount(0)
{
	bossFlag = true;
}

// デストラクタ
PlayScene::~PlayScene()
{
	m_pSound.reset();
}

// 初期化
eScene PlayScene::Initialize()
{
	// サウンドのshared_ptrを受け取る
	m_pSound = std::weak_ptr<Adx2Le>(ResourceManager::GetInstance().GetSound(L"Resources\\Sounds\\PlayScene"));

	// BGMの再生
	if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
		sptr->Play(CRI_PLAYSCENE_PLAYSCENEBGM, 1.0f);

	// 追尾カメラの作成
	m_pFollowCamera = std::make_unique<FollowCamera>();
	m_pFollowCamera->Initialize();
	GameContext::Register<FollowCamera>(m_pFollowCamera);

	// カーソルの作成
	m_pCursor = std::make_unique<MouseCursor>("Mouse");

	// フロア作成
	m_pFloor = std::make_unique<Floor>("Floor");
	m_pFloor->Initialize();

	// 壁作成
	m_pWall = std::make_unique<Wall>("Wall");
	m_pWall->Initialize();

	// プレイヤー作成
	m_pPlayer = std::make_unique<Player>("Player");
	m_pPlayer->Initialize();

	// 敵作成
	if (bossFlag)
	{
		m_pEnemy = std::make_unique<Enemy>(m_pEnemy->BOSS_ENEMY, "Enemy");
		m_pEnemy->Initialize(DirectX::SimpleMath::Vector3(0.0f, 1.0f, -15.0f));
	}
	if (!bossFlag)
	{
		m_pEnemies[0] = std::make_unique<Enemy>(m_pEnemies[0]->NORMAL_ENEMY, "Enemy");
		m_pEnemies[0]->Initialize(DirectX::SimpleMath::Vector3(10.0f, 1.0f, 5.0f));
		m_pEnemies[1] = std::make_unique<Enemy>(m_pEnemies[1]->NORMAL_ENEMY, "Enemy");
		m_pEnemies[1]->Initialize(DirectX::SimpleMath::Vector3(10.0f, 1.0f, 5.0f));
		m_pEnemies[2] = std::make_unique<Enemy>(m_pEnemies[2]->SHIELD_ENEMY, "Enemy");
		m_pEnemies[2]->Initialize(DirectX::SimpleMath::Vector3(10.0f, 1.0f, 5.0f));
		m_pEnemies[3] = std::make_unique<Enemy>(m_pEnemies[3]->SHIELD_ENEMY, "Enemy");
		m_pEnemies[3]->Initialize(DirectX::SimpleMath::Vector3(10.0f, 1.0f, 5.0f));
	}

	m_color = DirectX::Colors::Red;

	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\GreenHP.png", nullptr, m_greenHpBarTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\RedHP.png", nullptr, m_redHpBarTexture.GetAddressOf());

	// 敵のライフデフォルトスケール値
	m_defaultGaugeScaleX = 1.0f;
	// 現在の敵のライフ
	m_currentGaugeScaleX = 1.0f;
	// 次の敵のライフ
	m_prevGaugeScaleX = m_currentGaugeScaleX;
	// じわじわ減るライフゲージ
	m_lightGreenGaugeRate = 0;
	// 経過時間
	m_totalTime = 0;
	m_gaugeFlag = false;

	// 画面を開く
	GameContext::Get<EffectMask>()->Open();


	// エフェクトの作成
	m_batchEffect = std::make_unique<DirectX::BasicEffect>(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());
	m_batchEffect->SetTextureEnabled(true);
	m_batchEffect->SetVertexColorEnabled(true);
	GameContext::Register<DirectX::BasicEffect>(m_batchEffect);

	// 入力レイアウト生成
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	GameContext::Get<DX::DeviceResources>()->GetD3DDevice()->
		CreateInputLayout(DirectX::VertexPositionColorTexture::InputElements,
			DirectX::VertexPositionColorTexture::InputElementCount,
			shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf());

	// プリミティブバッチの作成
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext());

	m_warningEffect = std::make_unique<WarningEffect>();
	m_warningEffect->Initialize();

	m_waveCount = 5;

	// WARNING再生
	if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
		sptr->Play(CRI_PLAYSCENE_WARNING, 1.0f);

}

// 更新
eScene PlayScene::Update(DX::StepTimer const& _timer)
{
	float elapsedTime = float(_timer.GetElapsedSeconds());

	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	EffectMask* fadeEffect = GameContext::Get<EffectMask>();


	switch (m_gameState)
	{
	case STATE_START:

		if (m_waveState == NORMAL_WAVE)
		{
			fadeEffect->Open();

			// 画面が開くまでまつ
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

		// プレイヤー更新
		if (m_pPlayer->GetActiveFlag() == true)
			m_pPlayer->Update();

		// 敵更新
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

		// 追尾カメラ更新
		if (m_pPlayer->GetActiveFlag() == true)
			m_pFollowCamera->Update(m_pPlayer->GetPos() + FollowCamera::EYE_VEC, m_pPlayer->GetPos());

		// カーソル更新
		m_pCursor->Update();

		m_color = DirectX::Colors::Red;


		// 交差点
		DirectX::SimpleMath::Vector3 hitPos;

		// マウスRayと床の当たり判定(交差点検出)
		if (m_pPlayer->GetActiveFlag() == true)
		{
			if (Collision::IntersectSegmentTriangle(m_pCursor->GetRayNear(), m_pCursor->GetRayFar(), m_pFloor->GetTriangle(0), &hitPos) ||
				Collision::IntersectSegmentTriangle(m_pCursor->GetRayNear(), m_pCursor->GetRayFar(), m_pFloor->GetTriangle(1), &hitPos))
			{
				m_pPlayer->SetMousePos(hitPos);
			}
		}

		// 弾の中心と半径を設定
		if (bossFlag)
		{
			std::vector<DirectX::SimpleMath::Vector3> playerBullets;

			if (m_pPlayer->GetActiveFlag() == true)
				playerBullets = m_pPlayer->GetBulletPos();

			std::vector<DirectX::SimpleMath::Vector3> enemyBullets = m_pEnemy->GetBulletPos();

			std::vector<Collision::Box> playerBullet;
			std::vector<Collision::Sphere> enemyBullet;

			playerBullet.resize(playerBullets.size());

			enemyBullet.resize(enemyBullets.size());
			for (unsigned int i = 0; i < playerBullets.size(); i++)
			{
				playerBullet[i].center = playerBullets[i];
				playerBullet[i].radius = DirectX::SimpleMath::Vector3(0.1f, 0.1, 0.5f);
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
					// 敵の体力の比率計算
					float greenGaugeRate = m_pEnemy->GetLife() / m_pEnemy->GetMaxLife();
					// 現在のゲージサイズ
					m_currentGaugeScaleX = m_defaultGaugeScaleX * greenGaugeRate;

				}
			}

			// プレイヤーと敵の弾の当たり判定
			for (unsigned int i = 0; i < enemyBullet.size(); i++)
			{
				if (m_pPlayer->GetActiveFlag() == true)
				{
					if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), enemyBullet[i]))
					{
						// シーンマネージャーの取得
						GameSceneManager* gameSceneManager = GameContext::Get<GameSceneManager>();

						// プレイシーンへ遷移
						gameSceneManager->RequestScene("ResultGameOver");
					}
				}
			}

			// 壁と敵の弾の当たり判定
			for (unsigned int i = 0; i < enemyBullet.size(); i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (Collision::HitCheckSphereToBox(enemyBullet[i], m_pWall->GetCollider(j)))
					{
						m_pEnemy->BulletOnCollision(i);
					}
				}
			}

			// プレイヤーと敵の当たり判定
			if (m_pPlayer->GetActiveFlag() == true
				&& m_pEnemy != nullptr)
			{
				if (!m_pPlayer->GetHitFlag())
				{
					if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), m_pEnemy->GetCollider()))
					{
						m_pPlayer->OnCollisionEnemy(m_pEnemy->GetPosition());
					}
				}
			}

			// 体力が０なら消去
			if (m_pPlayer->GetLife() == 0)
			{
				m_pPlayer->SetActiveFlag(false);
			}

		}
		// リザルトシーンへ遷移
		//if (m_pEnemy->GetModel() == nullptr)
		//{
		//	GameSceneManager* gameSceneManager = GameContext::Get<GameSceneManager>();
		//	gameSceneManager->RequestScene("ResultClear");
		//}



		// 体力ゲージ
		// 経過時間
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

// 描画
eScene PlayScene::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"PlayScene");
	debugFont->draw();
	debugFont->print(10, 40, L"[Space] Title");
	debugFont->draw();


	// プレイヤー表示
	if (m_pPlayer->GetActiveFlag() == true)
		m_pPlayer->Render(m_pFollowCamera->GetViewMatrix());

	// 敵表示
	if (bossFlag)
		m_pEnemy->Render(m_pFollowCamera->GetViewMatrix());

	if (!bossFlag)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pEnemies[i]->Render(m_pFollowCamera->GetViewMatrix());
		}
	}

	// フロアの表示
	m_pFloor->Render(m_pFollowCamera->GetViewMatrix());

	// 壁の表示
	m_pWall->Render(m_pFollowCamera->GetViewMatrix());

	GameContext::Get<DirectX::SpriteBatch>()->Begin(DirectX::SpriteSortMode_Deferred, GameContext::Get<DirectX::CommonStates>()->NonPremultiplied());
	if (bossFlag)
	{
		// 赤ゲージ表示
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_redHpBarTexture.Get(), DirectX::SimpleMath::Vector2(350, 596), nullptr, DirectX::Colors::Black,
			0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(1.0f, 0.2f));
		// 薄緑ゲージ表示
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_redHpBarTexture.Get(), DirectX::SimpleMath::Vector2(350, 596), nullptr, DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 0.5f),
			0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(m_lightGreenGaugeRate, 0.2f));
		// 緑ゲージ表示
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_greenHpBarTexture.Get(), DirectX::SimpleMath::Vector2(350, 600), nullptr, DirectX::Colors::White,
			0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(m_currentGaugeScaleX, 0.2f));

	}

	m_pCursor->Render(m_pFollowCamera->GetViewMatrix());

	m_warningEffect->Render();

	GameContext::Get<DirectX::SpriteBatch>()->End();
}

// 後始末
eScene PlayScene::Finalize()
{
}

// プレイ中
PlayScene::GAME_STATE PlayScene::PlayGame()
{
	return STATE_GAME;
}

// 線形補間
float PlayScene::Lerp(float _start, float _end, float _time)
{
	return _start + (_end - _start) * _time;
}

// 球面線形補間
float PlayScene::Slerp(float _start, float _end, float _time)
{
	float rate = (sinf(0.0f * DirectX::XM_PI /
		2.0f - DirectX::XM_PI * _time) + 1.0f) / 2.0f;
	return _start + (_end - _start) * rate;
}