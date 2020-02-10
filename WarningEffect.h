#pragma once

#include <SimpleMath.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <WICTextureLoader.h>

#include "DeviceResources.h"
#include "GameContext.h"
#include "WarningLine.h"
#include "WarningMessage.h"

class WarningEffect
{
public: // 基本

	// コンストラクタ
	WarningEffect();
	// デストラクタ
	~WarningEffect() {};

public: // 関数

	// 初期化
	void Initialize();
	// 更新
	void Update(float _elapsedTime);
	// 描画
	void Render();

private: // 変数

	// ライン
	std::unique_ptr<WarningLine>		m_pLine[2];
	// メッセージ
	std::unique_ptr<WarningMessage>		m_pMessage;
	
	// ラインテクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_lineTexture;
	// メッセージテクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_messageTexture;
	// アイコンテクスチャ
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_iconTexture;

};