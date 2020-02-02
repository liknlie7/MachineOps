#include "pch.h"

#include "TitleScene.h"

// �R���X�g���N�^
TitleScene::TitleScene()
	: GameScene()
	, m_time(0)
{
	// �g���b�J�[�̐ݒ�
	m_keyboardTracker = GameContext::Get<DirectX::Keyboard::KeyboardStateTracker>();

	// �T�E���h�̐ݒ�
	GameContext::Get<Adx2Le>()->Initialize(L"Resources\\Sounds\\TitleSounds.acf");
	GameContext::Get<Adx2Le>()->LoadAcbFile(L"Resources\\Sounds\\TitleSounds.acb");
}

// �f�X�g���N�^
TitleScene::~TitleScene()
{
}

// ������
void TitleScene::Initialize()
{
	// �e�N�X�`���ǂݍ���
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\BackGround.png", nullptr, m_backGroundTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Title.png", nullptr, m_titleTexture.GetAddressOf());
	DirectX::CreateWICTextureFromFile(GameContext::Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\Massage.png", nullptr, m_massageTexture.GetAddressOf());

	// BGM�̍Đ�
	GameContext::Get<Adx2Le>()->Play(CRI_TITLE_TITLEBGM);
}

// �`��
void TitleScene::Update(DX::StepTimer const& _timer)
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
		GameContext::Get<Adx2Le>()->Play(CRI_TITLE_STARTSE);

		// �t�F�[�h�A�E�g
		effectMask->Close();
	}
	// ��ʂ�����܂ł܂�
	if (effectMask->IsClose())
	{
		// �V�[���}�l�[�W���[�̎擾
		GameSceneManager* gameSceneManager = GameContext::Get<GameSceneManager>();
		// �T�E���h���~������
		GameContext::Get<Adx2Le>()->Stop();
		// �v���C�V�[���֑J��
		gameSceneManager->RequestScene("Play");
	}
}

// �`��
void TitleScene::Render()
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
}

// �㏈��
void TitleScene::Finalize()
{

}