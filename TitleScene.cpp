#include "pch.h"

#include "TitleScene.h"

// TODO: �{�����[�������X�ɉ����鏈��
//		 �t�F�[�h�̃p�^�[���ύX

// �R���X�g���N�^
TitleScene::TitleScene()
	//: GameScene()
	: m_time(0)
	, m_volumeFadeFlag(false)
	, m_volume(1.0f)
{
	// �g���b�J�[�̐ݒ�
	m_keyboardTracker = GameContext::Get<DirectX::Keyboard::KeyboardStateTracker>();

	// �T�E���h��shared_ptr���󂯎��
	m_pSound = std::weak_ptr<Adx2Le>(ResourceManager::GetInstance().GetSound(L"Resources\\Sounds\\TitleSounds"));
}

// �f�X�g���N�^
TitleScene::~TitleScene()
{
	m_pSound.reset();
}

// ������
eScene TitleScene::Initialize()
{
	// �e�N�X�`���ǂݍ���
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\BackGround.png", nullptr, m_backGroundTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Title.png", nullptr, m_titleTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Massage.png", nullptr, m_massageTexture.GetAddressOf());

	// BGM�̍Đ�
	if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
		sptr->Play(CRI_TITLE_TITLEBGM, m_volume);

	return eScene::TITLE;
}

// �X�V
eScene TitleScene::Update(DX::StepTimer const& _timer)
{
	// �t�F�[�h�G�t�F�N�g�̎擾
	auto effectMask = GameContext::Get<EffectMask>();

	// �o�ߎ��Ԃ̍X�V
	float elapsedTime = float(_timer.GetElapsedSeconds());
	m_time += elapsedTime;

	// �L�[�{�[�h�̎擾
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();
	// �L�[�{�[�h�g���b�J�[�X�V
	m_keyboardTracker->Update(keyState);

	// �X�y�[�X�L�[����������
	if (m_keyboardTracker->pressed.Space)
	{
		// �X�^�[�g���̍Đ�
		if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
			sptr->Play(CRI_TITLE_STARTSE, m_volume);


		// �t�F�[�h�A�E�g
		effectMask->Close();
		m_volumeFadeFlag = true;
	}

	// �{�����[�������X�ɉ�����
	if (m_volumeFadeFlag)
	{
		m_volume -= elapsedTime;

		//m_adx2Le->SetVolumeByID(CRI_TITLE_TITLEBGM, m_volume);
		if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
			sptr->SetVolumeByID(CRI_TITLE_TITLEBGM, m_volume);

		if (m_volume <= 0.0f)
			m_volumeFadeFlag = false;
	}

	// ��ʂ�����܂ł܂�
	if (effectMask->IsClose() && m_volume < 0.0f)
	{
		// �V�[���}�l�[�W���[�̎擾
		//GameSceneManager* gameSceneManager = GameContext::Get<GameSceneManager>();

		// �T�E���h���~������
		if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
			sptr->Stop();

		// �v���C�V�[���֑J��
		//gameSceneManager->RequestScene("Play");
		SceneManager::GetInstance().RequestScene(eScene::PLAY);
	}


	return eScene::TITLE;
}

// �`��
eScene TitleScene::Render()
{
	// �X�v���C�g�o�b�`�̎擾
	DirectX::SpriteBatch* spriteBatch = GameContext::Get<DirectX::SpriteBatch>();

	// �e�N�X�`���`��
	spriteBatch->Begin();
	spriteBatch->Draw(m_backGroundTexture.Get(), DirectX::SimpleMath::Vector2::Zero);
	spriteBatch->Draw(m_titleTexture.Get(), DirectX::SimpleMath::Vector2(190, 220), nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(0.8f, 0.8f));
	// �_��
	if (sin(m_time * 4) > 0) {
		spriteBatch->Draw(m_massageTexture.Get(), DirectX::SimpleMath::Vector2(380, 450), nullptr, DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero, DirectX::SimpleMath::Vector2(0.3f, 0.3f));
	}
	spriteBatch->End();

	return eScene::TITLE;
}

// �㏈��
eScene TitleScene::Finalize()
{
	return eScene::TITLE;
}