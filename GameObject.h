#pragma once

#include <SimpleMath.h>
#include <string>
#include <functional>

// ゲームオブジェクト
class GameObject
{
public: // 基本

	// コンストラクタ
	GameObject();
	// デストラクタ
	virtual ~GameObject();

public: // 関数

	// 更新
	virtual void Update() = 0;
	// 描画
	virtual void Render(const DirectX::SimpleMath::Matrix& _view) = 0;

	// 無効化
	void Invalidate();
	// 有効
	bool IsValid() const;
	// 無効
	bool IsInvalid() const;

	// 座標取得
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	// 速度取得
	const DirectX::SimpleMath::Vector3& GetVelocity() const;
	// 回転取得
	const DirectX::SimpleMath::Vector3& GetRotation() const;
	// 大きさ取得
	const DirectX::SimpleMath::Vector3& GetScale() const;

	// 座標設定
	void SetPosition(const DirectX::SimpleMath::Vector3& _position);
	// 速度設定
	void SetVelocity(const DirectX::SimpleMath::Vector3& _velocity);
	// 回転設定
	void SetRotation(const DirectX::SimpleMath::Vector3& _rotation);
	// 大きさ設定
	void SetScale(const DirectX::SimpleMath::Vector3& _scale);

	// 消去
	static void Destroy(GameObject* _object);

private: // 変数

	// 有効か
	bool m_isValid;

protected: // 変数

	// 座標
	DirectX::SimpleMath::Vector3 m_position;
	// 回転
	DirectX::SimpleMath::Vector3 m_rotation;
	// 大きさ
	DirectX::SimpleMath::Vector3 m_scale;
	// ベクトル
	DirectX::SimpleMath::Vector3 m_velocity;
	// 行列
	DirectX::SimpleMath::Matrix m_matrix;


};

// 有効
inline bool GameObject::IsValid() const
{
	return m_isValid;
}

// 無効
inline bool GameObject::IsInvalid() const
{
	return !m_isValid;
}

// 座標取得
inline const DirectX::SimpleMath::Vector3& GameObject::GetPosition() const
{
	return m_position;
}

// 速度取得
inline const DirectX::SimpleMath::Vector3& GameObject::GetVelocity() const
{
	return m_velocity;
}

// 回転取得
inline const DirectX::SimpleMath::Vector3 & GameObject::GetRotation() const
{
	return m_rotation;
}

// 大きさ取得
inline const DirectX::SimpleMath::Vector3 & GameObject::GetScale() const
{
	return m_scale;
}

// 座標設定
inline void GameObject::SetPosition(const DirectX::SimpleMath::Vector3& _position)
{
	m_position = _position;
}

// 速度設定
inline void GameObject::SetVelocity(const DirectX::SimpleMath::Vector3& _velocity)
{
	m_velocity = _velocity;
}

// 回転設定
inline void GameObject::SetRotation(const DirectX::SimpleMath::Vector3& _rotation)
{
	m_rotation = _rotation;
}

// 大きさ設定
inline void GameObject::SetScale(const DirectX::SimpleMath::Vector3& _scale)
{
	m_scale = _scale;
}

// 消去
inline void GameObject::Destroy(GameObject * _object)
{
	_object->Invalidate();
}