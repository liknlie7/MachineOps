#include "pch.h"

#include "TitleScene.h"

// コンストラクタ
TitleScene::TitleScene()
	: GameScene()
	, m_time(0)
{
	// トラッカーの設定
	m_keyboardTracker = GameContext::Get<DirectX::Keyboard::KeyboardStateTracker>();

	// サウンドの設定
	GameContext::Get<Adx2Le>()->Initialize(L"Resources\\Sounds\\TitleSounds.acf");
	GameContext::Get<Adx2Le>()->LoadAcbFile(L"Resources\\Sounds\\TitleSounds.acb");
}

// デストラクタ
TitleScene::~TitleScene()
{
}

// 初期化
void TitleScene::Initialize()
{
	// テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\BackGround.png", nullptr, m_backGroundTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Title.png", nullptr, m_titleTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Massage.png", nullptr, m_massageTexture.GetAddressOf());

	// BGMの再生
	GameContext::Get<Adx2Le>()->Play(CRI_TITLE_TITLEBGM);
}

// 描画
void TitleScene::Update(DX::StepTimer const& _timer)
{
	// フェードエフェクトの取得
	auto effectMask = GameContext::Get<EffectMask>();

	// 経過時間の更新
	float elapsedTime = float(_timer.GetElapsedSeconds());
	m_time += elapsedTime;

	// キーボードの取得
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	// キーボードトラッカー更新
	m_keyboardTracker->Update(keyState);

	// スペースキーを押したら
	if (m_keyboardTracker->pressed.Space)
	{
		// スタート音の再生
		GameContext::Get<Adx2Le>()->Play(CRI_TITLE_STARTSE);

		// フェードアウト
		effectMask->Close();
	}
	// 画面が閉じるまでまつ
	if (effectMask->IsClose())
	{
		// シーンマネージャーの取得
		GameSceneManager* gameSceneManager = GameContext::Get<GameSceneManager>();
		// サウンドを停止させる
		GameContext::Get<Adx2Le>()->Stop();
		// プレイシーンへ遷移
		gameSceneManager->RequestScene("Play");
	}
}

// 描画
void TitleScene::Render()
{
	// スプライトバッチの取得
	DirectX::SpriteBatch* spriteBatch = GameContext::Get<DirectX::SpriteBatch>();

	// テクスチャ描画
	spriteBatch->Begin();
	spriteBatch->Draw(m_backGroundTexture.Get(), DirectX::SimpleMath::Vector2::Zero);
	spriteBatch->Draw(m_titleTexture.Get(), DirectX::SimpleMath::Vector2(190, 220), nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(0.8f, 0.8f));
	// 点滅
	if (sin(m_time * 4) > 0) {
		spriteBatch->Draw(m_massageTexture.Get(), DirectX::SimpleMath::Vector2(380, 450), nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(0.3f, 0.3f));
	}
	spriteBatch->End();
}

// 後処理
void TitleScene::Finalize()
{

}