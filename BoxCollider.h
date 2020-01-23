#pragma once

#include "Collider.h"

// ボックス
class BoxCollider : public Collider
{
public: // 基本

	// コンストラクタ
	BoxCollider(GameObject* _owner, const DirectX::SimpleMath::Vector3& _size = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f));
	// デストラクタ
	~BoxCollider() = default;

public: // アクセサ

	// サイズ取得
	const DirectX::SimpleMath::Vector3& GetSize() const
	{
		return m_size;
	}

	// サイズ設定
	void SetSize(const DirectX::SimpleMath::Vector3& _size)
	{
		m_size = _size;
	}

public: // 関数

	bool IsCollided(const Collider*       _collider) const override;
	bool IsCollided(const SphereCollider* _collider) const override;
	//bool IsCollided(const BoxCollider*    _collider) const override;

private: // 変数

	// サイズ
	DirectX::SimpleMath::Vector3 m_size;

};
