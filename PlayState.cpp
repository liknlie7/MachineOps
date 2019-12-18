#include "pch.h"

#include "PlayState.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

// コンストラクタ
PlayState::PlayState()
	: GameState()
{

}

// デストラクタ
PlayState::~PlayState()
{
}

// 初期化
void PlayState::Initialize()
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
	m_pEnemy = make_unique<Enemy>(m_pEnemy->BOSS_TYPE);
	m_pEnemy->Initialize(Vector3(0.0f, 1.0f, -15.0f));

	m_color = Colors::Red;

	// ビューポートの作成
	RECT size = GameContext::Get<DX::DeviceResources>()->GetOutputSize();
	m_viewPort =
		Matrix::CreateScale(Vector3(.5f, -.5f, 1.f)) *
		Matrix::CreateTranslation(Vector3(.5f, .5f, 0.f)) *
		Matrix::CreateScale(Vector3(float(size.right), float(size.bottom), 1.f));

	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\GreenHP.png", nullptr, m_greenHpBarTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\RedHP.png", nullptr, m_redHpBarTexture.GetAddressOf());

	// HP用
	m_gaugeDefaultPositionX = 350;
	m_gaugeDefaultScaleX = 1.0f;
	m_currentGaugePositionX = 350;
	m_prevGaugePositionX = m_currentGaugePositionX;
	m_currentGaugeScaleX = 1.0f;
	m_prevGaugeScaleX = m_currentGaugeScaleX;
}

// 更新
void PlayState::Update(DX::StepTimer const& timer)
{
	Mouse::State mouseState = Mouse::Get().GetState();
	Keyboard::State keyState = Keyboard::Get().GetState();

	// プレイヤー更新
	m_pPlayer->Update();

	// 敵更新
	m_pEnemy->SetPlayerPos(m_pPlayer->GetPos());
	m_pEnemy->Update();

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

	// プレイヤーと敵との接触判定
	if (!m_pPlayer->GetHitFlag())
		if (Collision::HitCheckSphereToSphere(m_pPlayer->GetCollider(), m_pEnemy->GetCollider()))
			m_pPlayer->SetHitFlag(true);

	// リザルトシーンへ遷移
	if (m_pEnemy->GetModel() == nullptr)
	{
		GameStateManager* gameStateManager = GameContext::Get<GameStateManager>();
		gameStateManager->RequestState("Result");
	}
	// 体力の比率計算
	float lifeRate = m_pEnemy->GetCurrentLife() / m_pEnemy->GetMaxLife();
	// ゲージのサイズ変更
	m_currentGaugeScaleX = m_gaugeDefaultScaleX * lifeRate;
	// サイズ変更に合わせて場所を移動
	m_currentGaugePositionX = m_gaugeDefaultPositionX - m_gaugeDefaultScaleX * (1 - lifeRate) * 0.5;
}

// 描画
void PlayState::Render()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->print(10, 10, L"PlayState");
	debugFont->draw();
	debugFont->print(10, 40, L"[Space] Title");
	debugFont->draw();


	// プレイヤー表示
	m_pPlayer->Render(m_pFollowCamera->getViewMatrix());

	// 敵表示
	m_pEnemy->Render(m_pFollowCamera->getViewMatrix());

	// 床の表示
	m_pFloor->Render(m_pFollowCamera->getViewMatrix());

	GameContext::Get<SpriteBatch>()->Begin(SpriteSortMode_Deferred, GameContext::Get<CommonStates>()->NonPremultiplied());
	////// 赤ゲージ表示
	////GameContext::Get<DirectX::SpriteBatch>()->Draw(m_redHpBarTexture.Get(), DirectX::SimpleMath::Vector2(350, 596), nullptr, Colors::White,
	////	0.0f, Vector2::Zero, Vector2(1.0f, 0.2f));
	// 薄緑ゲージ表示
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_greenHpBarTexture.Get(), DirectX::SimpleMath::Vector2(m_prevGaugePositionX + (m_currentGaugePositionX - m_prevGaugePositionX) * 0.01f, 600), nullptr, Vector4(1.0f, 1.0f, 1.0f, 0.5f),
		0.0f, Vector2::Zero, Vector2(m_prevGaugeScaleX + (m_currentGaugeScaleX - m_prevGaugeScaleX) * 0.01f, 0.2f));
	// 緑ゲージ表示
	GameContext::Get<DirectX::SpriteBatch>()->Draw(m_greenHpBarTexture.Get(), DirectX::SimpleMath::Vector2(m_currentGaugePositionX, 600), nullptr, Colors::White,
		0.0f, Vector2::Zero, Vector2(m_currentGaugeScaleX, 0.2f));

	GameContext::Get<SpriteBatch>()->End();

}

// 後始末
void PlayState::Finalize()
{
}