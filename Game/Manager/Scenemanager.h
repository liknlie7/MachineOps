#pragma once

#include "../Common/StepTimer.h"
#include "../Common/Singleton.h"

// �V�[����
enum class eScene
{
	NONE,
	TITLE,			// �^�C�g��
	PLAY,			// �v���C
	RESULT_CLEAR,	// �Q�[���N���A
	RESULT_GAMEOVER,// �Q�[���I�[�o�[
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
	virtual void Initialize() = 0;

	// �X�V
	virtual void Update(DX::StepTimer const& _timer) = 0;

	// �`��
	virtual void Render() = 0;

	// �㏈��
	virtual void Finalize() = 0;
};

// �V�[���Ǘ��N���X
class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;

private: // ��{

	// �R���X�g���N�^
	SceneManager(eScene _scene = eScene::TITLE);

	// �f�X�g���N�^
	~SceneManager() {};

public: // �֐�

	// ���݂̃V�[���̍X�V
	void Update(DX::StepTimer const& _timer);

	// ���݂̃V�[���̕`��
	void Render();

	// ���̃V�[���̃��N�G�X�g
	void RequestScene(eScene _scene);

private:

	// �V�[���̍쐬
	IScene* CreateScene(eScene _scene);

	// �V�[���̐؂�ւ�
	void ChangeScene();

private: // �ϐ�

	// �V�[��
	IScene* m_pScene;

	// ���̃V�[��
	eScene m_nextScene;

};
