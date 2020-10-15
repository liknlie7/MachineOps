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

// リソース管理クラス
class ResourceManager : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;

private: // 基本

	// コンストラクタ
	ResourceManager();

	// デストラクタ
	~ResourceManager();

public: // 関数

	// モデルデータの取得
	std::shared_ptr<DirectX::Model> GetModel(const std::wstring _path);

	// サウンドの取得 -- 拡張子は渡さなくてよい
	// acb,acfファイルが同名
	std::shared_ptr<Adx2Le> GetSound(const std::wstring _path);
	// acb,acfファイルが別名
	std::shared_ptr<Adx2Le> GetSound(const std::wstring _acfPath, const std::wstring _acbPath);

	// テクスチャの取得
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTexture(const std::wstring _path);

	//　エネミーデータ(csv)の読み込み
	void LoadEnemyData();

	// エネミーデータの取得
	EnemyData GetEnemyData(int _enemyType)
	{
		return m_enemyData[_enemyType];
	}

private: // 変数

	// エフェクトファクトリ
	DirectX::EffectFactory*									m_pFactory;

	// モデルデータ
	std::map<std::wstring, std::shared_ptr<DirectX::Model>> m_models;

	// サウンドデータ
	std::map<std::wstring, std::shared_ptr<Adx2Le>>			m_sounds;

	// テクスチャデータ
	std::map <std::wstring, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>>		m_textures;

	// エネミーデータ
	std::vector<EnemyData>									m_enemyData;
};