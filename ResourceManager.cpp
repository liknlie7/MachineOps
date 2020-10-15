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
// acf,acb�t�@�C��������
std::shared_ptr<Adx2Le> ResourceManager::GetSound(const std::wstring _path)
{
	// �T�E���h�f�[�^��Ԃ�
	return GetSound(_path, _path);
}

// �T�E���h�f�[�^�̎擾--�g���q�͓n���Ȃ��Ă悢
// acf,acb�t�@�C�����ʖ�
std::shared_ptr<Adx2Le> ResourceManager::GetSound(const std::wstring _acfPath, const std::wstring _acbPath)
{
	// �쐬����Ă���ꍇ�T�E���h�f�[�^��Ԃ�
	if (m_sounds.count(_acbPath) != 0)
	{
		return m_sounds[_acbPath];
	}

	// �g���q
	std::wstring acf = L".acf";
	std::wstring acb = L".acb";

	// �p�X�Ɋg���q���Ȃ�
	std::wstring acfData = _acfPath + acf;
	std::wstring acbData = _acbPath + acb;

	m_sounds[_acbPath] = std::make_shared<Adx2Le>();
	m_sounds[_acbPath]->Initialize(acfData.c_str());
	m_sounds[_acbPath]->LoadAcbFile(acbData.c_str());

	// �T�E���h�f�[�^��Ԃ�
	return m_sounds[_acbPath];
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

// �G�l�~�[�f�[�^(csv)�̓ǂݍ���
void ResourceManager::LoadEnemyData()
{
	std::ifstream ifs("Resources\\csv\\EnemyData.csv");

	std::string lineBuf;

	std::vector<std::vector<std::string>> csvData;

	while (std::getline(ifs, lineBuf))
	{
		csvData.push_back(std::vector<std::string>());

		std::stringstream stream(lineBuf);

		std::string indexBuf;

		while (std::getline(stream, indexBuf, ','))
		{
			(*(csvData.end() - 1)).push_back(indexBuf);
		}
	}

	// �G�l�~�[�̐����擾
	int enemyNum = stoi(csvData[0][1]);

	for (int i = 2; i < enemyNum + 2; i++)
	{
		EnemyData data;

		data.enemyType = stoi(csvData[i][0]);
		data.moveSpeed = stof(csvData[i][1]);
		data.life = stoi(csvData[i][2]);
		data.shotType = stoi(csvData[i][3]);
		data.collider = stof(csvData[i][4]);

		m_enemyData.push_back(data);
	}
}
