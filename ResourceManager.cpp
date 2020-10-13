#include "pch.h"
#include "ResourceManager.h"

// �R���X�g���N�^
ResourceManager::ResourceManager()
{
	// �G�t�F�N�g�t�@�N�g���̍쐬
	m_pFactory = new DirectX::EffectFactory(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());

	// �ǂݍ��ރf�B���N�g���̐ݒ�
	m_pFactory->SetDirectory(L"Resources/Models");
}

// �f�X�g���N�^
ResourceManager::~ResourceManager()
{
	delete m_pFactory;
}

// ���f���f�[�^�̎擾
std::shared_ptr<DirectX::Model> ResourceManager::GetModel(const std::wstring _path)
{
	ID3D11Device1* device = GameContext::Get<DX::DeviceResources>()->GetD3DDevice();

	// �쐬����Ă���ꍇ���f���f�[�^��Ԃ�
	if (m_models.count(_path) != 0)
	{
		return m_models[_path];
	}

	// �쐬����Ă��Ȃ��ꍇ�쐬
	m_models[_path] = std::make_shared<DirectX::Model>();
	m_models[_path] = DirectX::Model::CreateFromCMO(device, _path.c_str(), *m_pFactory);

	// ���f���f�[�^��Ԃ�
	return m_models[_path];
}

// �T�E���h�f�[�^�̎擾--�g���q�͓n���Ȃ��Ă悢
std::shared_ptr<Adx2Le> ResourceManager::GetSound(const std::wstring _path)
{
	// �쐬����Ă���ꍇ�T�E���h�f�[�^��Ԃ�
	if (m_sounds.count(_path) != 0)
	{
		return m_sounds[_path];
	}

	std::wstring acf = L".acf";
	std::wstring acb = L".acb";

	std::wstring acfData = _path + acf;
	std::wstring acbData = _path + acb;

	m_sounds[_path] = std::make_shared<Adx2Le>();
	m_sounds[_path]->Initialize(acfData.c_str());
	m_sounds[_path]->LoadAcbFile(acbData.c_str());

	// �T�E���h�f�[�^��Ԃ�
	return m_sounds[_path];
}

// �e�N�X�`���f�[�^�̎擾
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ResourceManager::GetTexture(const std::wstring _path)
{
	ID3D11Device1* device = GameContext::Get<DX::DeviceResources>()->GetD3DDevice();

	// �쐬����Ă���ꍇ���f���f�[�^��Ԃ�
	if (m_textures.count(_path) != 0)
	{
		return m_textures[_path];
	}

	// �쐬����Ă��Ȃ��ꍇ�쐬
	DirectX::CreateWICTextureFromFile(device, _path.c_str(), nullptr, m_textures[_path].GetAddressOf());
	
	// �e�N�X�`���f�[�^��Ԃ�
	return m_textures[_path];
}


//// �T�E���h�̍쐬
//void ResourceManager::CreateSound(const int _soundNumber)
//{
//	switch (_soundNumber)
//	{
//		// �^�C�g���V�[���̃T�E���h��ǂݍ���
//	case TITLESCENE_SOUND:
//
//		m_sounds[TITLESCENE_SOUND]->Initialize(L"Resources\\Sounds\\TitleSounds.acf");
//		m_sounds[TITLESCENE_SOUND]->LoadAcbFile(L"Resources\\Sounds\\TitleSounds.acb");
//
//		break;
//
//		// �v���C�V�[���̃T�E���h��ǂݍ���
//	case PLAYSCENE_SOUND:
//
//		m_sounds[PLAYSCENE_SOUND]->Initialize(L"Resources\\Sounds\\PlayScene.acf");
//		m_sounds[PLAYSCENE_SOUND]->LoadAcbFile(L"Resources\\Sounds\\PlayScene.acb");
//
//		break;
//
//		// �v���C���[�̃T�E���h��ǂݍ���
//	case PLAYER_SOUND:
//
//		m_sounds[PLAYER_SOUND]->Initialize(L"Resources\\Sounds\\PlayScene.acf");
//		m_sounds[PLAYER_SOUND]->LoadAcbFile(L"Resources\\Sounds\\Player.acb");
//
//		break;
//
//	default:
//		break;
//	}
//}

