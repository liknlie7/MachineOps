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

// リソース管理クラス
class ResourceManager : public Singleton<ResourceManager>
{
public: // 定数

	// モデルデータ
	//enum class ModelData {
	//	PLAYER,			// プレイヤー
	//	ENEMY,			// 敵
	//};

	//// サウンドデータ
	//enum class SoundData {
	//	TITLESCENE,		// タイトルシーンのサウンド
	//	PLAYSCENE,		// プレイシーンのサウンド
	//	PLAYER,			// プレイヤーのサウンド
	//};

public: // 基本

	// コンストラクタ
	ResourceManager();

	// デストラクタ
	~ResourceManager();

public: // 関数

	// モデルデータの取得
	std::shared_ptr<DirectX::Model> GetModel(std::wstring _path);

	// サウンドの作成
	void CreateSound(const int _soundNumber);

	// サウンドの取得 -- 拡張子は渡さなくてよい
	std::shared_ptr<Adx2Le> GetSound(std::wstring _path);

private: // 変数

	// エフェクトファクトリ
	DirectX::EffectFactory*									m_factory;

	// モデルデータ
	std::map<std::wstring, std::shared_ptr<DirectX::Model>> m_models;

	// サウンドデータ
	std::map<std::wstring, std::shared_ptr<Adx2Le>>			m_sounds;
};



