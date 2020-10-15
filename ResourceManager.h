#pragma once

#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>
#include <string>
#include <map>
#include <WICTextureLoader.h>
#include <sstream>
#include <fstream>

#include "GameContext.h"
#include "DeviceResources.h"
#include "Adx2Le.h"
#include "Singleton.h"
#include "Projection.h"
#include "EnemyData.h"

// ���\�[�X�Ǘ��N���X
class ResourceManager : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;

private: // ��{

	// �R���X�g���N�^
	ResourceManager();

	// �f�X�g���N�^
	~ResourceManager();

public: // �֐�

	// ���f���f�[�^�̎擾
	std::shared_ptr<DirectX::Model> GetModel(const std::wstring _path);

	// �T�E���h�̎擾 -- �g���q�͓n���Ȃ��Ă悢
	// acb,acf�t�@�C��������
	std::shared_ptr<Adx2Le> GetSound(const std::wstring _path);
	// acb,acf�t�@�C�����ʖ�
	std::shared_ptr<Adx2Le> GetSound(const std::wstring _acfPath, const std::wstring _acbPath);

	// �e�N�X�`���̎擾
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTexture(const std::wstring _path);

	//�@�G�l�~�[�f�[�^(csv)�̓ǂݍ���
	void LoadEnemyData();

	// �G�l�~�[�f�[�^�̎擾
	EnemyData GetEnemyData(int _enemyType)
	{
		return m_enemyData[_enemyType];
	}

private: // �ϐ�

	// �G�t�F�N�g�t�@�N�g��
	DirectX::EffectFactory*									m_pFactory;

	// ���f���f�[�^
	std::map<std::wstring, std::shared_ptr<DirectX::Model>> m_models;

	// �T�E���h�f�[�^
	std::map<std::wstring, std::shared_ptr<Adx2Le>>			m_sounds;

	// �e�N�X�`���f�[�^
	std::map <std::wstring, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>		m_textures;

	// �G�l�~�[�f�[�^
	std::vector<EnemyData>									m_enemyData;
};