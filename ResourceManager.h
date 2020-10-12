#pragma once

#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>
#include <string>
#include <map>

#include "GameContext.h"
#include "DeviceResources.h"
#include "Adx2Le.h"
#include "Singleton.h"
#include "Projection.h"

// ���\�[�X�Ǘ��N���X
class ResourceManager : public Singleton<ResourceManager>
{
public: // �萔

	// ���f���f�[�^
	//enum class ModelData {
	//	PLAYER,			// �v���C���[
	//	ENEMY,			// �G
	//};

	//// �T�E���h�f�[�^
	//enum class SoundData {
	//	TITLESCENE,		// �^�C�g���V�[���̃T�E���h
	//	PLAYSCENE,		// �v���C�V�[���̃T�E���h
	//	PLAYER,			// �v���C���[�̃T�E���h
	//};

public: // ��{

	// �R���X�g���N�^
	ResourceManager();

	// �f�X�g���N�^
	~ResourceManager();

public: // �֐�

	// ���f���f�[�^�̎擾
	std::shared_ptr<DirectX::Model> GetModel(std::wstring _path);

	// �T�E���h�̍쐬
	void CreateSound(const int _soundNumber);

	// �T�E���h�̎擾 -- �g���q�͓n���Ȃ��Ă悢
	std::shared_ptr<Adx2Le> GetSound(std::wstring _path);

private: // �ϐ�

	// �G�t�F�N�g�t�@�N�g��
	DirectX::EffectFactory*									m_factory;

	// ���f���f�[�^
	std::map<std::wstring, std::shared_ptr<DirectX::Model>> m_models;

	// �T�E���h�f�[�^
	std::map<std::wstring, std::shared_ptr<Adx2Le>>			m_sounds;
};



