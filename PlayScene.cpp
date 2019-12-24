#include "pch.h"

#include "PlayScene.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;


// ライフゲージ減少にかかる時間
const float PlayScene::DAMAGE_TIME = 1.0f;

// コンストラクタ
PlayScene::PlayScene()
	: GameScene()
{
	bossFlag = true;
}

// デストラクタ
PlayScene::~PlayScene()
{
}

// 初期化
void PlayScene::Initialize()
{
	// 追尾カメラの作成
	m_pFollowCamera = make_unique<FollowCamera>();
	m_pFollowCamera->Initialize();

	// フロア作成
	m_pFloor = make_unique<Floor>();
	m_pFloor->Initialize();

	// プレイヤー作成
	m_pPlayer = make_unique<Player>();
	m_pPlayer->Initialize();

	// 敵作成
	if (bossFlag)
	{
		m_pEnemy = make_unique<Enemy>(m_pEnemy->BOSS_ENEMY);
		m_pEnemy->Initialize(Vector3(0.0f, 1.0f, -15.0f));
	}
	if (!bossFlag)
	{
		m_pEnemies[0] = make_unique<Enemy>(m_pEnemies[0]->NORMAL_ENEMY);
		m_pEnemies[0]->Initialize(Vector3(10.0f, 1.0f, -5.0f));
		m_pEnemies[1] = make_unique<Enemy>(m_pEnemies[1]->NORMAL_ENEMY);
		m_pEnemies[1]->Initialize(Vector3(-10.0f, 1.0f, -5.0f));
		m_pEnemies[2] = make_unique<Enemy>(m_pEnemies[2]->SHIELD_ENEMY);
		m_pEnemies[2]->Initialize(Vector3(10.0f, 1.0f, -10.0f));
		m_pEnemies[3] = make_unique<Enemy>(m_pEnemies[3]->SHIELD_ENEMY);
		m_pEnemies[3]->Initialize(Vector3(-10.0f, 1.0f, -10.0f));
	}

	m_color = Colors::Red;

	// ビューポートの作成
	RECT size = GameContext::Get<DX::DeviceResources>()->GetOutputSize();
	m_viewPort =
		Matrix::CreateScale(Vector3(.5f, -.5f, 1.f)) *
		Matrix::CreateTranslation(Vector3(.5f, .5f, 0.f)) *
		Matrix::CreateScale(Vector3(float(size.right), float(size.bottom), 1.f));

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
}

// 更新
void PlayScene::Update(DX::StepTimer const& _timer)
{
	Mouse::State mouseState = Mouse::Get().GetState();
	Keyboard::State keyState = Keyboard::Get().GetState();

	// プレイヤー更新
	m_pPlayer->Update();

	// 敵更新
	if (bossFlag)
	{
		m_pEnemy->SetPlayerPos(m_pPlayer->GetPos());
		m_pEnemy->Update();
	}
	if (!bossFlag)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pEnemies[i]->SetPlayerPos(m_pPlayer->GetPos());
			m_pEnemies[i]->Update();
		}
	}

	// 追尾カメラ更新
	m_pFollowCamera->Update(m_pPlayer->GetPos() + FollowCamera::EYE_VEC, m_pPlayer->GetPos());

	m_color = Colors::Red;

	// マウス座標をワールド座標へ変換
	// マウスRayの作成
	Vector3 mousePos = Vector3::Transform(Vector3((float)mouseState.x, (float)mouseState.y, 0), m_viewPort.Invert());
	Vector3 pointNear = Vector3(mousePos.x, mousePos.y, 0.0f);
	Vector3 pointFar = Vector3(mousePos.x, mousePos.y, 1.0f);
	Matrix inverseviewproj = (m_pFollowCamera->getViewMatrix() *  GameContext::Get<Projection>()->GetMatrix()).Invert();
	Vector3 rayNear = Vector3::Transform(pointNear, inverseviewproj);
	Vector3 rayFar = Vector3::Transform(pointFar, inverseviewproj);
	Vector3 raySubtraction = rayFar - rayNear;
	Vector3 rayDirection = raySubtraction;
	// 正規化
	rayDirection.Normalize();

	// 頂点ベクトル
	Vector3 v0 = Vector3(-50.0f, 0.0f, -50.0f);  // 左上
	Vector3 v1 = Vector3(-50.0f, 0.0f, 50.0f);   // 左下
	Vector3 v2 = Vector3(50.0f, 0.0f, 50.0f);    // 右下
	Vector3 v3 = Vector3(50.0f, 0.0f, -50.0f);   // 右上

	// 交差点
	Vector3 hitPos;

	// 三角形を作成
	Collision::Triangle tri1(v0, v2, v1);
	Collision::Triangle tri2(v0, v3, v2);

	// マウスRayと三角形の当たり判定(交差点検出)
	if (Collision::IntersectSegmentTriangle(rayNear, rayFar, tri1, &hitPos) ||
		Collision::IntersectSegmentTriangle(rayNear, rayFar, tri2, &hitPos))
	{
		m_pPlayer->SetMousePos(hitPos);
		geoVec = hitPos;
	}

	// 交差地点デバッグ
	geoMat = Matrix::CreateTranslation(geoVec);

	// 弾の中心と半径を設定
	if (bossFlag)
	{
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
				m_pPlayer->m_pWeapon->BulletOnCollision(i);
			}
		}
		for (unsigned int i = 0; i < enemyBullet.size(); i++)
		{
			if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), enemyBullet[i]))
			{
				m_pPlayer->SetHitFlag(true);
				m_pEnemy->BulletOnCollision(i);
				// 敵の体力の比率計算
				float greenGaugeRate = m_pEnemy->GetLife() / m_pEnemy->GetMaxLife();
				// 現在のゲージサイズ
				m_currentGaugeScaleX = m_defaultGaugeScaleX * greenGaugeRate;


			}
		}

		// プレイヤーと敵との接触判定
		if (!m_pPlayer->GetHitFlag())
			if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), m_pEnemy->GetCollider()))
				m_pPlayer->SetHitFlag(true);
		// リザルトシーンへ遷移
		if (m_pEnemy->GetModel() == nullptr)
		{
			GameSceneManager* gameSceneManager = GameContext::Get<GameSceneManager>();
			gameSceneManager->RequestScene("Result");
		}
	}


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
}

// 描画
void PlayScene::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"PlayScene");
	debugFont->draw();
	debugFont->print(10, 40, L"[Space] Title");
	debugFont->draw();


	// プレイヤー表示
	m_pPlayer->Render(m_pFollowCamera->getViewMatrix());

	// 敵表示
	if(bossFlag)
	m_pEnemy->Render(m_pFollowCamera->getViewMatrix());

	if (!bossFlag)
	{
		for (int i = 0; i < 4; i++)
		{
			m_pEnemies[i]->Render(m_pFollowCamera->getViewMatrix());
		}
	}

	// 床の表示
	m_pFloor->Render(m_pFollowCamera->getViewMatrix());

	if (bossFlag)
	{
		GameContext::Get<SpriteBatch>()->Begin(SpriteSortMode_Deferred, GameContext::Get<CommonStates>()->NonPremultiplied());
		// 赤ゲージ表示
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_redHpBarTexture.Get(), DirectX::SimpleMath::Vector2(350, 596), nullptr, Colors::Black,
			0.0f, Vector2::Zero, Vector2(1.0f, 0.2f));
		// 薄緑ゲージ表示
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_redHpBarTexture.Get(), DirectX::SimpleMath::Vector2(350, 596), nullptr, Vector4(1.0f, 1.0f, 1.0f, 0.5f),
			0.0f, Vector2::Zero, Vector2(m_lightGreenGaugeRate, 0.2f));
		// 緑ゲージ表示
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_greenHpBarTexture.Get(), DirectX::SimpleMath::Vector2(350, 600), nullptr, Colors::White,
			0.0f, Vector2::Zero, Vector2(m_currentGaugeScaleX, 0.2f));

		GameContext::Get<SpriteBatch>()->End();
	}
}

// 後始末
void PlayScene::Finalize()
{
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