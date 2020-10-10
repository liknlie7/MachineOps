#include "pch.h"

#include "TitleScene.h"

// TODO: ボリュームを徐々に下げる処理
//		 フェードのパターン変更

// コンストラクタ
TitleScene::TitleScene()
	//: GameScene()
	: m_time(0)
	, m_volumeFadeFlag(false)
	, m_volume(1.0f)
{
	// トラッカーの設定
	m_keyboardTracker = GameContext::Get<DirectX::Keyboard::KeyboardStateTracker>();

	// サウンドのshared_ptrを受け取る
	m_pSound = std::weak_ptr<Adx2Le>(ResourceManager::GetInstance().GetSound(L"Resources\\Sounds\\TitleSounds"));
}

// デストラクタ
TitleScene::~TitleScene()
{
	m_pSound.reset();
}

// 初期化
eScene TitleScene::Initialize()
{
	// テクスチャ読み込み
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\BackGround.png", nullptr, m_backGroundTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Title.png", nullptr, m_titleTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Massage.png", nullptr, m_massageTexture.GetAddressOf());

	// BGMの再生
	if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
		sptr->Play(CRI_TITLE_TITLEBGM, m_volume);
}

// 描画
eScene TitleScene::Update(DX::StepTimer const& _timer)
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
		if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
			sptr->Play(CRI_TITLE_STARTSE, m_volume);


		// フェードアウト
		effectMask->Close();
		m_volumeFadeFlag = true;
	}

	// ボリュームを徐々に下げる
	if (m_volumeFadeFlag)
	{
		m_volume -= elapsedTime;

		//m_adx2Le->SetVolumeByID(CRI_TITLE_TITLEBGM, m_volume);
		if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
			sptr->SetVolumeByID(CRI_TITLE_TITLEBGM, m_volume);

		if (m_volume <= 0.0f)
			m_volumeFadeFlag = false;
	}

	// 画面が閉じるまでまつ
	if (effectMask->IsClose() && m_volume < 0.0f)
	{
		// シーンマネージャーの取得
		GameSceneManager* gameSceneManager = GameContext::Get<GameSceneManager>();

		// サウンドを停止させる
		if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
			sptr->Stop();

		// プレイシーンへ遷移
		gameSceneManager->RequestScene("Play");
	}
}

// 描画
eScene TitleScene::Render()
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
eScene TitleScene::Finalize()
{

}