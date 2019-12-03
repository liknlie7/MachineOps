#include "pch.h"

#include "Normal.h"

// �R���X�g���N�^
Normal::Normal(Weapon* _player,Enemy* _enemy)
{
	m_player = _player;
	m_enemy = _enemy;
}

// ������
void Normal::Initialize(BulletFactory* bulletFactory)
{
	m_bulletFactory = bulletFactory;
}

// �e�𔭎˂���
void Normal::Shoot(const DX::StepTimer& _timer, const DirectX::SimpleMath::Vector3& _position, const float& _angle)
{
	// �o�ߎ��Ԃ̎擾
	float elapsedTime = float(_timer.GetElapsedSeconds());

	Bullet* bullet = nullptr;
	// 5�t���[�����ɒe�𔭎�
	if (_timer.GetFrameCount() % 5 == 0)
	{
		for (int index = 0; index < BulletFactory::BULLET_NUM; index++)
		{
			// �z��̗v�f��nullptr�̏ꍇ
			if (m_player->GetBullets()[index] == nullptr || m_player->GetBullets()[index]->IsUsed() == false)
			{
				// �e�𔭎˂���
				bullet = m_bulletFactory->Create(position, angle);
				// �e���Ȃ��ꍇ
				if (bullet == nullptr)
					continue;
				if (m_player->GetBullets()[index] == nullptr)
				{
					if (m_player->GetBulletNum() < BulletFactory::BULLET_NUM - 1)
						// ���˂����e���𑝂₷
						m_player->SetBulletNum(m_player->GetBulletNum() + 1);
				}
				// Bullet�I�u�W�F�N�g��z��Ɋi�[����
				m_player->GetBullets()[index] = bullet;
				break;
			}
		}
	}
}

// ��n��������
void Normal::Finalize()
{

}