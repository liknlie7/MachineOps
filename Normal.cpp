#include "pch.h"

#include "Normal.h"

// コンストラクタ
Normal::Normal(Weapon* _player,Enemy* _enemy)
{
	m_player = _player;
	m_enemy = _enemy;
}

// 初期化
void Normal::Initialize(BulletFactory* bulletFactory)
{
	m_bulletFactory = bulletFactory;
}

// 弾を発射する
void Normal::Shoot(const DX::StepTimer& _timer, const DirectX::SimpleMath::Vector3& _position, const float& _angle)
{
	// 経過時間の取得
	float elapsedTime = float(_timer.GetElapsedSeconds());

	Bullet* bullet = nullptr;
	// 5フレーム毎に弾を発射
	if (_timer.GetFrameCount() % 5 == 0)
	{
		for (int index = 0; index < BulletFactory::BULLET_NUM; index++)
		{
			// 配列の要素がnullptrの場合
			if (m_player->GetBullets()[index] == nullptr || m_player->GetBullets()[index]->IsUsed() == false)
			{
				// 弾を発射する
				bullet = m_bulletFactory->Create(position, angle);
				// 弾がない場合
				if (bullet == nullptr)
					continue;
				if (m_player->GetBullets()[index] == nullptr)
				{
					if (m_player->GetBulletNum() < BulletFactory::BULLET_NUM - 1)
						// 発射した弾数を増やす
						m_player->SetBulletNum(m_player->GetBulletNum() + 1);
				}
				// Bulletオブジェクトを配列に格納する
				m_player->GetBullets()[index] = bullet;
				break;
			}
		}
	}
}

// 後始末をする
void Normal::Finalize()
{

}