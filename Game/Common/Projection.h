#pragma once

#include "SimpleMath.h"

// プロジェクション
class Projection final
{
public: // 基本

	// コンストラクタ
	Projection() = default;

	// デストラクタ
	~Projection() = default;

public: // 関数

	// 行列の取得
	const DirectX::SimpleMath::Matrix& GetMatrix() const;

	// 視野の設定
	void SetPerspectiveFieldOfView(float _fov, float _aspectRatio, float _nearPlane, float _farPlane);

private: // 変数

	// 行列
	DirectX::SimpleMath::Matrix m_matrix;
};

// 行列の取得
inline const DirectX::SimpleMath::Matrix& Projection::GetMatrix() const
{
	return m_matrix;
}

// 視野の設定
inline void Projection::SetPerspectiveFieldOfView(float _fov, float _aspectRatio, float _nearPlane, float _farPlane)
{
	m_matrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(_fov, _aspectRatio, _nearPlane, _farPlane);
}