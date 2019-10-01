#pragma once

#include <SimpleMath.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <GeometricPrimitive.h>
#include <Model.h>
#include <Effects.h>
#include <CommonStates.h>

#include "DeviceResources.h"
#include "Projection.h"
#include "StepTimer.h"
#include "GameContext.h"
#include "Weapon.h"
#include "GameObject.h"


class Bullet;
class Weapon;

class Player : public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Player();
	// �f�X�g���N�^
	~Player();

public: // �A�N�Z�T

	// ���W�̎擾
	DirectX::SimpleMath::Vector3 Player::GetPos()
	{
		return m_pos;
	}
	DirectX::SimpleMath::Vector3 Player::GetDecisionAreaPos()
	{
		return m_decisionAreaPos;
	}

	// �}�E�X���W�̐ݒ�
	void SetMousePos(DirectX::SimpleMath::Vector3 _mousePos)
	{
		m_mousePos = _mousePos;
	}

	// �e�̍��W�擾
	std::vector<DirectX::SimpleMath::Vector3> GetBulletPos()
	{
		return m_pWeapon->GetBulletPos();
	}

	// �ڐG����t���O�̎擾
	bool Player::GetHitFlag()
	{
		return m_hitFlag;
	}
	// �ڐG����t���O�̐ݒ�
	void Player::SetHitFlag(bool _hitFlag)
	{
		m_hitFlag = _hitFlag;
	}

	void Player::SetBulletHitFlag(bool _bulletHitFlag)
	{
		m_pWeapon->SetBulletHitFlag(_bulletHitFlag);
	}
	void Player::SetBulletNumber(int _bulletNumber)
	{
		m_pWeapon->SetBulletNumber(_bulletNumber);
	}

public: // �֐�

	// ������
	void Initialize();
	// �X�V
	void Update();
	// �`��
	void Render(DirectX::SimpleMath::Matrix _view);
	// ��n��
	void Finalize();

	// �_��
	void Blink();

private: // �ϐ�

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;

	// �}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker m_mouseTracker;

	ID3D11DeviceContext* m_context;

private:

	// �v���C���[
	std::unique_ptr<DirectX::Model>				 m_pPlayer;
	// �e
	std::unique_ptr<Weapon>						 m_pWeapon;

	// ����
	DirectX::SimpleMath::Vector3				 m_dir;
	
	//�����蔻��p
	std::unique_ptr<DirectX::GeometricPrimitive> m_pDecisionArea;
	DirectX::SimpleMath::Vector3				 m_decisionAreaPos;
	DirectX::SimpleMath::Matrix					 m_decisionAreaMat;

	// �}�E�X���W
	DirectX::SimpleMath::Vector3				 m_mousePos;

	// �d��
	float										 m_gravity;
	// �p�x
	float										 m_angle;
	// �C���^�[�o��
	float										 m_shotInterval;
	// �q�b�g�t���O
	bool										 m_hitFlag;
	// �_�Ŏ���
	int											 m_blinkTime;
};