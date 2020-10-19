#pragma once

#include <SimpleMath.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <Model.h>

#include "../../Manager/Collision.h"
#include "../../Manager/Bulletmanager.h"
#include "../../Objects/GameObject.h"
#include "../../Sound/Adx2Le.h"

// �v���C���[�N���X
class Player : public GameObject
{
public: // ��{

	// �R���X�g���N�^
	Player();

	// �f�X�g���N�^
	~Player();

public: // �֐�

	// ������
	void Initialize();

	// �X�V
	void Update() override;

	// �`��
	void Render(const DirectX::SimpleMath::Matrix& _view) override;

	// ��n��
	void Finalize() {};

	// �Փ�
	void OnCollision();

private: //�֐�

	// �ړ�
	void Move();

	// �e������
	void Shot();

public: // �A�N�Z�T

	// �}�E�X���W�̐ݒ�
	void SetMousePos(const DirectX::SimpleMath::Vector3& _mousePos)
	{
		m_mousePos = _mousePos;
	}

	// �����蔻��̎擾
	Collision::Sphere GetCollider() const
	{
		return m_collider;
	}

	// �e�Ǘ��N���X�̃A�h���X��ݒ�
	void SetBulletManager(BulletManager* _bullet)
	{
		m_pBulletManager = _bullet;
	}

private: // �萔

	// �ړ������͈�
	static const DirectX::SimpleMath::Vector3 RANGE_MIN;
	static const DirectX::SimpleMath::Vector3 RANGE_MAX;

	// �e�̑��x
	static const float BULLET_SPEED;

	// �e�����Ԋu
	static const float SHOT_INTERVAL;

	// �v���C���[�ړ����x
	static const float MOVE_SPEED;

	// �v���C���[�ړ����x(�V�t�g����)
	static const float MOVE_SLOW_SPEED;

private: // �ϐ�

	// �L�[�{�[�h
	std::unique_ptr<DirectX::Keyboard>			 m_keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> m_keyboardTracker;

	// �}�E�X�g���b�J�[
	DirectX::Mouse::ButtonStateTracker			 m_mouseTracker;

	// �T�E���h
	std::weak_ptr<Adx2Le>						 m_pSound;

	// �v���C���[
	std::weak_ptr<DirectX::Model>				 m_pPlayer;
	Collision::Sphere							 m_collider;

	// �e�Ǘ��̃I�u�W�F�N�g
	BulletManager*								 m_pBulletManager;

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

	// Shift�{�^���t���O
	bool										 m_isShiftDown;
};