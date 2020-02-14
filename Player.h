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
#include "Collision.h"
#include "GameContext.h"
#include "GameObject.h"
#include "Weapon.h"
#include "Adx2Le.h"
#include "PlayerSound.h"
#include "Utilities.h"

class Bullet;
class Weapon;

class Player : public GameObject
{
private:

	enum STATE
	{
		STATE_NORMAL,
		STATE_HIT,
		STATE_DEAD,
	};

public: // ��{

	// �R���X�g���N�^
	Player(const std::string& _tag);
	// �f�X�g���N�^
	~Player();

public: // �A�N�Z�T

	// ���W�̎擾
	DirectX::SimpleMath::Vector3 Player::GetPos() const
	{
		return m_position;
	}

	// �}�E�X���W�̐ݒ�
	void SetMousePos(const DirectX::SimpleMath::Vector3& _mousePos)
	{
		m_mousePos = _mousePos;
	}

	// �e�̍��W�擾
	std::vector<DirectX::SimpleMath::Vector3> GetBulletPos() const
	{
		return m_pWeapon->GetBulletPos();
	}

	// �ڐG����t���O�̎擾
	bool GetHitFlag() const
	{
		return m_hitFlag;
	}
	// �ڐG����t���O�̐ݒ�
	void SetHitFlag(const bool& _hitFlag)
	{
		m_hitFlag = _hitFlag;
	}

	// �A�N�e�B�u�t���O�̎擾
	bool GetActiveFlag() const
	{
		return m_activeFlag;
	}

	// �A�N�e�B�u�t���O�̐ݒ�
	void SetActiveFlag(const bool _flag)
	{
		m_activeFlag = _flag;
	}

	// �̗͂̎擾
	int GetLife() const
	{
		return m_life;
	}

	// �e�̃q�b�g�t���O�ݒ�
	void SetBulletHitFlag(const bool& _isHitFlag)
	{
		m_pWeapon->SetBulletHitFlag(_isHitFlag);
	}
	// �e�̔ԍ��擾
	void SetBulletNumber(const int& _bulletNumber)
	{
		m_pWeapon->SetBulletNumber(_bulletNumber);
	}

	// �����蔻��̎擾
	Collision::Sphere GetCollider() const
	{
		return m_collider;
	}

	// �T�E���h�v���[���[�̎擾
	void SetSoundPlayer(Adx2Le* _sound)
	{
		m_sound = _sound;
	}

public: // �֐�

	// ������
	void Initialize();
	// �X�V
	void Update() override;
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;
	// ��n��
	void Finalize();

	// �Փ�
	void OnCollision();

private: // �T�u�֐�

	// �_��
	void Blink();

	// �Փ�
	void OnCollision(GameObject* _object);

private: // �萔

	// �ړ������͈�
	static const DirectX::SimpleMath::Vector3 RANGE_MIN;
	static const DirectX::SimpleMath::Vector3 RANGE_MAX;

private: // �ϐ�

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard> m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;

	// �}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker m_mouseTracker;

	ID3D11DeviceContext* m_context;

	// �T�E���h
	Adx2Le*					m_sound;

private:

	// �v���C���[
	std::unique_ptr<DirectX::Model>				 m_pPlayer;
	Collision::Sphere							 m_collider;

	// ����
	DirectX::SimpleMath::Vector3				 m_dir;

	// �}�E�X���W
	DirectX::SimpleMath::Vector3				 m_mousePos;

	// �p�x
	float										 m_angle;
	// �C���^�[�o��
	float										 m_shotInterval;
	// �q�b�g�t���O
	bool										 m_hitFlag;
	// �_�Ŏ���
	int											 m_blinkTime;
	// Shift�{�^���t���O
	bool										 m_isShiftDown;
	// �̗�
	int											 m_life;
	// �A�N�e�B�u�t���O
	bool										 m_activeFlag;

public:

	// �e
	std::unique_ptr<Weapon>						 m_pWeapon;

};