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

// エネミー(ボス)初期位置
const DirectX::SimpleMath::Vector3 PlayScene::ENEMY_BOSS_INIT_POS = DirectX::SimpleMath::Vector3(0.0f, 1.0f, -15.0f);

// ライフゲージ減少にかかる時間
const float PlayScene::DAMAGE_TIME = 1.0f;

// HPゲージスケール値
const float PlayScene::HP_SCALE_X = 1.0f;
const float PlayScene::HP_SCALE_Y = 0.2f;

// HPゲージ位置
const DirectX::SimpleMath::Vector2 PlayScene::HP_RED_POS = DirectX::SimpleMath::Vector2(350, 596);
const DirectX::SimpleMath::Vector2 PlayScene::HP_GREEN_POS = DirectX::SimpleMath::Vector2(350, 600);

// 薄いゲージ用
const DirectX::SimpleMath::Vector4 PlayScene::HP_GAUGE_COLOR = DirectX::SimpleMath::Vector4(1.0f, 1.0f, 1.0f, 0.5f);

// コンストラクタ
PlayScene::PlayScene()
	: m_gameState(STATE_START)
	, m_waveState(BOSS_WAVE)
{

}

// デストラクタ
PlayScene::~PlayScene()
{
	m_pSound.reset();
}

// 初期化
void PlayScene::Initialize()
{
	// サウンドのshared_ptrを受け取る
	m_pSound = std::weak_ptr<Adx2Le>(ResourceManager::GetInstance()->GetSound(L"Resources\\Sounds\\PlayScene"));

	// 追尾カメラの作成
	m_pFollowCamera = std::make_unique<FollowCamera>();
	m_pFollowCamera->Initialize();
	GameContext::Register<FollowCamera>(m_pFollowCamera);

	// カーソルの作成
	m_pReticle = std::make_unique<Reticle>();

	// フロア作成
	m_pFloor = std::make_unique<Floor>();
	m_pFloor->Initialize();

	// 壁作成
	m_pWall = std::make_unique<Wall>();
	m_pWall->Initialize();

	// 弾管理用オブジェクト作成
	m_pBulletManager = std::make_unique<BulletManager>();
	m_pBulletManager->Initialize();

	// プレイヤー作成
	m_pPlayer = std::make_unique<Player>();
	m_pPlayer->Initialize();
	m_pPlayer->SetBulletManager(m_pBulletManager.get());

	// エネミーデータの読み込み
	ResourceManager::GetInstance()->LoadEnemyData();

	// エネミー作成
	m_pEnemy = std::make_unique<Enemy>(ResourceManager::GetInstance()->GetEnemyData(Enemy::BOSS_ENEMY - 1));
	m_pEnemy->Initialize(ENEMY_BOSS_INIT_POS);
	m_pEnemy->SetBulletManager(m_pBulletManager.get());

	// テクスチャデータを受け取る
	m_textures[GREEN_HP] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\GreenHP.png");
	m_textures[RED_HP] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\RedHP.png");

	// エネミーのライフデフォルトスケール値の初期化
	m_defaultGaugeScaleX = 1.0f;

	// 現在のエネミーのライフスケール値の初期化
	m_currentGaugeScaleX = 1.0f;

	// 前のライフスケール値を設定
	m_prevGaugeScaleX = m_currentGaugeScaleX;

	// じわじわ減るライフゲージの初期化
	m_lightGreenGaugeRate = 0;

	// 経過時間初期化
	m_totalTime = 0;

	// 体力ゲージフラグ
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

	// Warningエフェクトの作成
	m_warningEffect = std::make_unique<WarningEffect>();
	m_warningEffect->Initialize();

	// BGMの再生
	if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
	{
		sptr->Play(CRI_PLAYSCENE_PLAYSCENEBGM);
	}

	// Warning再生
	if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
	{
		sptr->Play(CRI_PLAYSCENE_WARNING);
	}
}

// 更新
void PlayScene::Update(DX::StepTimer const& _timer)
{
	float elapsedTime = float(_timer.GetElapsedSeconds());

	// キーボード取得
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	// エフェクトマスク取得
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
				// ゲームステートをゲーム中に変更
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
		m_pPlayer->Update();

		// プレイヤーの座標をエネミーに渡す
		m_pEnemy->SetPlayerPos(m_pPlayer->GetPosition());

		// エネミー更新
		m_pEnemy->Update();

		// 追尾カメラ更新
		m_pFollowCamera->Update(m_pPlayer->GetPosition() + FollowCamera::EYE_VEC, m_pPlayer->GetPosition());

		// カーソル更新
		m_pReticle->Update();

		// 弾更新
		m_pBulletManager->Update();

		// 当たり判定更新
		CollisionUpdate();

		// 敵のHP更新
		HpGaugeUpdate(_timer);

		break;
	}
}

// 描画
void PlayScene::Render()
{
	// プレイヤー表示
	m_pPlayer->Render(m_pFollowCamera->GetViewMatrix());

	// エネミー表示
	m_pEnemy->Render(m_pFollowCamera->GetViewMatrix());

	// 弾描画
	m_pBulletManager->Render(m_pFollowCamera->GetViewMatrix());

	// フロアの表示
	m_pFloor->Render(m_pFollowCamera->GetViewMatrix());

	// 壁の表示
	m_pWall->Render(m_pFollowCamera->GetViewMatrix());

	GameContext::Get<DirectX::SpriteBatch>()->Begin(DirectX::SpriteSortMode_Deferred, GameContext::Get<DirectX::CommonStates>()->NonPremultiplied());
	// 赤ゲージ表示
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_textures[RED_HP].Get(), HP_RED_POS, nullptr, DirectX::Colors::Black,
		0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(HP_SCALE_X, HP_SCALE_Y));
	// 薄緑ゲージ表示
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_textures[RED_HP].Get(), HP_RED_POS, nullptr, HP_GAUGE_COLOR,
		0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(m_lightGreenGaugeRate, HP_SCALE_Y));
	// 緑ゲージ表示
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_textures[GREEN_HP].Get(), HP_GREEN_POS, nullptr, DirectX::Colors::White,
		0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(m_currentGaugeScaleX, HP_SCALE_Y));

	// カーソルの描画
	m_pReticle->Render();

	// Warningエフェクト描画
	m_warningEffect->Render();

	GameContext::Get<DirectX::SpriteBatch>()->End();
}

// 当たり判定更新
void PlayScene::CollisionUpdate()
{
	// 交差点
	DirectX::SimpleMath::Vector3 hitPos;

	// マウスRayと床の当たり判定(交差点検出)
	if (Collision::IntersectSegmentTriangle(m_pReticle->GetRayNear(), m_pReticle->GetRayFar(), m_pFloor->GetTriangle(0), &hitPos) ||
		Collision::IntersectSegmentTriangle(m_pReticle->GetRayNear(), m_pReticle->GetRayFar(), m_pFloor->GetTriangle(1), &hitPos))
	{
		m_pPlayer->SetMousePos(hitPos);
	}

	// プレイヤーとエネミーの弾用配列
	std::vector<Bullet*> playerBullets;
	std::vector<Bullet*> enemyBullets;

	for (int i = 0; i < m_pBulletManager->NUM_BULLET; i++)
	{
		// プレイヤーとエネミーの弾を取得する
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

	// 判定用
	std::vector<Collision::Box> playerBulletColliders;
	std::vector<Collision::Sphere> enemyBulletColliders;

	// 弾の数だけ判定用の配列を作成
	playerBulletColliders.resize(playerBullets.size());
	enemyBulletColliders.resize(enemyBullets.size());

	// プレイヤーの弾の判定設定
	for (unsigned int i = 0; i < playerBullets.size(); i++)
	{
		playerBulletColliders[i].center = playerBullets[i]->GetPosition();
		playerBulletColliders[i].radius = m_pBulletManager->BOX_BULLET_SIZE;
	}

	// エネミーの弾の判定設定
	for (unsigned int i = 0; i < enemyBullets.size(); i++)
	{
		enemyBulletColliders[i].center = enemyBullets[i]->GetPosition();
		enemyBulletColliders[i].radius = m_pBulletManager->SPHERE_BULLET_RADIUS;
	}

	// プレイヤーの弾とエネミーの当たり判定
	for (unsigned int i = 0; i < playerBullets.size(); i++)
	{
		// プレイヤーの弾が使用中なら
		if (playerBullets[i]->GetIsUsed())
		{
			// 球とボックスの当たり判定
			if (Collision::HitCheckSphereToBox(m_pEnemy->GetCollider(), playerBulletColliders[i]))
			{
				m_pEnemy->OnCollision();

				// プレイヤーの弾を未使用に設定する
				playerBullets[i]->SetIsUsed(false);

				// エネミーの体力ゲージを減らす
				float greenGaugeRate = m_pEnemy->GetLife() / m_pEnemy->GetMaxLife();
				m_currentGaugeScaleX = m_defaultGaugeScaleX * greenGaugeRate;

				if (m_pEnemy->GetLife() == 0)
				{
					// サウンドを停止させる
					if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
						sptr->Stop();

					SceneManager::GetInstance()->RequestScene(eScene::RESULT_CLEAR);
				}
			}
		}
	}

	// プレイヤーとエネミーの弾の当たり判定
	for (unsigned int i = 0; i < enemyBullets.size(); i++)
	{
		if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), enemyBulletColliders[i]))
		{
	// サウンドを停止させる
	if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
		sptr->Stop();

			// ゲームオーバーへ移行
			SceneManager::GetInstance()->RequestScene(eScene::RESULT_GAMEOVER);
		}
	}

	// 壁とエネミーの弾の当たり判定
	for (unsigned int i = 0; i < enemyBullets.size(); i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (Collision::HitCheckSphereToBox(enemyBulletColliders[i], m_pWall->GetCollider(j)))
			{
				// エネミーの弾を未使用に設定
				enemyBullets[i]->SetIsUsed(false);
			}
		}
	}

	// プレイヤーとエネミーの当たり判定
	if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), m_pEnemy->GetCollider()))
	{
		m_pPlayer->OnCollision();
	}
}

// エネミーのHP更新
void PlayScene::HpGaugeUpdate(DX::StepTimer const& _timer)
{
	// 経過時間
	m_totalTime += (float)_timer.GetElapsedSeconds();

	if (m_totalTime < DAMAGE_TIME)
	{
		// ゲージを減少させる
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
		// 現在のスケール値を保存しておく
		m_prevGaugeScaleX = m_currentGaugeScaleX;
	}

}


// 線形補間
float PlayScene::Lerp(float _start, float _end, float _time)
{
	return _start + (_end - _start) * _time;
}