#include "pch.h"
#include "ResourceManager.h"

// コンストラクタ
ResourceManager::ResourceManager()
{
	// エフェクトファクトリの作成
	m_pFactory = new DirectX::EffectFactory(GameContext::Get<DX::DeviceResources>()->GetD3DDevice());

	// 読み込むディレクトリの設定
	m_pFactory->SetDirectory(L"Resources/Models");
}

// デストラクタ
ResourceManager::~ResourceManager()
{
	delete m_pFactory;
}

// モデルデータの取得
std::shared_ptr<DirectX::Model> ResourceManager::GetModel(const std::wstring _path)
{
	ID3D11Device1* device = GameContext::Get<DX::DeviceResources>()->GetD3DDevice();

	// 作成されている場合モデルデータを返す
	if (m_models.count(_path) != 0)
	{
		return m_models[_path];
	}

	// 作成されていない場合作成
	m_models[_path] = std::make_shared<DirectX::Model>();
	m_models[_path] = DirectX::Model::CreateFromCMO(device, _path.c_str(), *m_pFactory);

	// モデルデータを返す
	return m_models[_path];
}

// サウンドデータの取得--拡張子は渡さなくてよい
// acf,acbファイルが同名
std::shared_ptr<Adx2Le> ResourceManager::GetSound(const std::wstring _path)
{
	// 作成されている場合サウンドデータを返す
	if (m_sounds.count(_path) != 0)
	{
		return m_sounds[_path];
	}

	// 拡張子
	std::wstring acf = L".acf";
	std::wstring acb = L".acb";

	// パスに拡張子をつなぐ
	std::wstring acfData = _path + acf;
	std::wstring acbData = _path + acb;

	m_sounds[_path] = std::make_shared<Adx2Le>();
	m_sounds[_path]->Initialize(acfData.c_str());
	m_sounds[_path]->LoadAcbFile(acbData.c_str());

	// サウンドデータを返す
	return m_sounds[_path];
}

// サウンドデータの取得--拡張子は渡さなくてよい
// acf,acbファイルが別名
std::shared_ptr<Adx2Le> ResourceManager::GetSound(const std::wstring _acf, const std::wstring _acb)
{
	// 作成されている場合サウンドデータを返す
	if (m_sounds.count(_acb) != 0)
	{
		return m_sounds[_acb];
	}

	// 拡張子
	std::wstring acf = L".acf";
	std::wstring acb = L".acb";

	// パスに拡張子をつなぐ
	std::wstring acfData = _acf + acf;
	std::wstring acbData = _acb + acb;

	m_sounds[_acb] = std::make_shared<Adx2Le>();
	m_sounds[_acb]->Initialize(acfData.c_str());
	m_sounds[_acb]->LoadAcbFile(acbData.c_str());

	// サウンドデータを返す
	return m_sounds[_acb];
}

// テクスチャデータの取得
Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ResourceManager::GetTexture(const std::wstring _path)
{
	ID3D11Device1* device = GameContext::Get<DX::DeviceResources>()->GetD3DDevice();

	// 作成されている場合モデルデータを返す
	if (m_textures.count(_path) != 0)
	{
		return m_textures[_path];
	}

	// 作成されていない場合作成
	DirectX::CreateWICTextureFromFile(device, _path.c_str(), nullptr, m_textures[_path].GetAddressOf());
	
	// テクスチャデータを返す
	return m_textures[_path];
}

// エネミーデータ(csv)の読み込み
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

	// エネミーの数を取得
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
