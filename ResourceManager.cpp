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
std::shared_ptr<Adx2Le> ResourceManager::GetSound(const std::wstring _path)
{
	// 作成されている場合サウンドデータを返す
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

	// サウンドデータを返す
	return m_sounds[_path];
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


//// サウンドの作成
//void ResourceManager::CreateSound(const int _soundNumber)
//{
//	switch (_soundNumber)
//	{
//		// タイトルシーンのサウンドを読み込む
//	case TITLESCENE_SOUND:
//
//		m_sounds[TITLESCENE_SOUND]->Initialize(L"Resources\\Sounds\\TitleSounds.acf");
//		m_sounds[TITLESCENE_SOUND]->LoadAcbFile(L"Resources\\Sounds\\TitleSounds.acb");
//
//		break;
//
//		// プレイシーンのサウンドを読み込む
//	case PLAYSCENE_SOUND:
//
//		m_sounds[PLAYSCENE_SOUND]->Initialize(L"Resources\\Sounds\\PlayScene.acf");
//		m_sounds[PLAYSCENE_SOUND]->LoadAcbFile(L"Resources\\Sounds\\PlayScene.acb");
//
//		break;
//
//		// プレイヤーのサウンドを読み込む
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

