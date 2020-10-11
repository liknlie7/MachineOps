#pragma once

#include "StepTimer.h"
#include "Singleton.h"

enum class eScene
{
	NONE,
	TITLE,
	PLAY,
	RESULT_CLEAR,
	RESULT_GAMEOVER,
};

// �V�[���C���^�[�t�F�[�X
class IScene
{
public: // ��{

	// �R���X�g���N�^
	IScene() = default;

	// �f�X�g���N�^
	virtual ~IScene() = default;

public: // �֐�

	// ������
	virtual eScene Initialize() = 0;

	// �X�V
	virtual eScene Update(DX::StepTimer const& _timer) = 0;

	// �`��
	virtual eScene Render() = 0;

	// �㏈��
	virtual eScene Finalize() = 0;
};

// �V�[���}�l�[�W���[
class SceneManager : public Singleton<SceneManager>
{
public: // ��{

	// �R���X�g���N�^
	SceneManager();

	// �f�X�g���N�^
	~SceneManager();

public: // �֐�

	// ���݂̃V�[���̏�����
	void Initialize();

	// ���݂̃V�[���̍X�V
	void Update(DX::StepTimer const& _timer);

	// ���݂̃V�[���̕`��
	void Render();

	// ���݂̃V�[���̌㏈��
	void Finalize();

	// �ŏ��̃V�[���̐ݒ�
	void SetStartScene(eScene _scene);

	// ���̃V�[���̃��N�G�X�g
	void RequestScene(eScene _scene);

	// �V�[���̍쐬
	IScene* ChangeScene(eScene _scene);

private: // �ϐ�

	// �V�[��
	IScene* m_pScene;

	// ���̃V�[��
	eScene m_nextScene;

};
