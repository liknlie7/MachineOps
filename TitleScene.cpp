#include "pch.h"

#include "TitleScene.h"
#include "GameContext.h"
#include "ResourceManager.h"
#include "TitleSoundSeet.h"
#include "EffectMask.h"

// �^�C�g���ʒu
const DirectX::SimpleMath::Vector2 TitleScene::TITLE_POSITION = DirectX::SimpleMath::Vector2(190.0f, 220.0f);

// �^�C�g���g�嗦
const DirectX::SimpleMath::Vector2 TitleScene::TITLE_SCALE = DirectX::SimpleMath::Vector2(0.8f, 0.8f);

// �e�L�X�g�ʒu
const DirectX::SimpleMath::Vector2 TitleScene::TEXT_POSITION = DirectX::SimpleMath::Vector2(380.0f, 450.0f);

// �e�L�X�g�g�嗦
const DirectX::SimpleMath::Vector2 TitleScene::TEXT_SCALE = DirectX::SimpleMath::Vector2(0.3f, 0.3f);

// �R���X�g���N�^
TitleScene::TitleScene()
	: m_time(0)
{
	// �g���b�J�[�̐ݒ�
	m_pKeyboardTracker = GameContext::Get<DirectX::Keyboard::KeyboardStateTracker>();

	// �T�E���h��shared_ptr���󂯎��
	m_pSound = std::weak_ptr<Adx2Le>(ResourceManager::GetInstance()->GetSound(L"Resources\\Sounds\\TitleSounds"));
}

// �f�X�g���N�^
TitleScene::~TitleScene()
{
	// �T�E���h�̃����N���N���A
	m_pSound.reset();
}

// ������
void TitleScene::Initialize()
{
	// �e�N�X�`���f�[�^���󂯎��
	m_pTextures[TITLE] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\Title.png");
	m_pTextures[BACK_GROUND] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\BackGround.png");
	m_pTextures[TEXT] = ResourceManager::GetInstance()->GetTexture(L"Resources\\Textures\\Massage.png");

	// BGM�̍Đ�
	if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
		sptr->Play(CRI_TITLE_TITLEBGM);
}

// �X�V
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
	m_pKeyboardTracker->Update(keyState);

	// �X�y�[�X�L�[����������
	if (m_pKeyboardTracker->pressed.Space)
	{
		// �X�^�[�g���̍Đ�
		if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
			sptr->Play(CRI_TITLE_STARTSE);

		// �t�F�[�h�A�E�g
		effectMask->Close();
	}

	// ��ʂ�����܂ł܂�
	if (effectMask->IsClose())
	{
		// �T�E���h���~������
		if (std::shared_ptr<Adx2Le> sptr = m_pSound.lock())
			sptr->Stop();

		// �v���C�V�[���֑J��
		SceneManager::GetInstance()->RequestScene(eScene::PLAY);
	}
}

// �`��
void TitleScene::Render()
{
	// �X�v���C�g�o�b�`�̎擾
	DirectX::SpriteBatch* spriteBatch = GameContext::Get<DirectX::SpriteBatch>();

	spriteBatch->Begin();

	// �w�i�`��
	spriteBatch->Draw(m_pTextures[BACK_GROUND].Get(), DirectX::SimpleMath::Vector2::Zero);

	// �^�C�g���`��
	spriteBatch->Draw(m_pTextures[TITLE].Get(), TITLE_POSITION, nullptr,
		DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero,
		TITLE_SCALE);

	// �e�L�X�g�`��
	// �_�ł�����
	if (sin(m_time * 4) > 0) {
		spriteBatch->Draw(m_pTextures[TEXT].Get(), TEXT_POSITION, nullptr,
			DirectX::Colors::White, 0.0f, DirectX::SimpleMath::Vector2::Zero,
			TEXT_SCALE);
	}

	spriteBatch->End();
}