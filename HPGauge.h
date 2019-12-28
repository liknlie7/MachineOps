#pragma once

#include "DeviceResources.h"
#include "WICTextureLoader.h" 
#include "GameContext.h"

// HP�Q�[�W
class HPGauge
{
public: // ��{

	// �R���X�g���N�^
	HPGauge();
	// �f�X�g���N�^
	~HPGauge();

public: // �A�N�Z�T

	// �̗͂̐ݒ�
	void SetLife(const float& _life)
	{
		m_life = _life;
	}
	
	// �̗͂̎擾
	float GetLife() const
	{
		return m_life;
	}

	// �̗͍ő�l�̐ݒ�
	void SetMaxLife(const float& _maxLife)
	{
		m_maxLife = _maxLife;
	}


public: // �֐�

	// �X�V
	void Update();

	// �`��
	void Render();

private: // �T�u�֐�

	// ���`���
	float Lerp(float _start, float _end, float _time)
	{
		return _start + (_end - _start) * _time;
	}

private: // �萔

	// �f�t�H���gX�T�C�Y
	static const float DEFAULT_GAUGE_SCALE_X;

private: // �ϐ�

	// �̗̓e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_greenHpBarTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>		m_redHpBarTexture;

	// �̗�
	float m_life;
	// �̗͍ő�l
	float m_maxLife;
	// �̗̓Q�[�W�f�t�H���g�T�C�Y
	float m_defaultGaugeScaleX;
	// ���݂̗̑̓Q�[�W�X�P�[��
	float m_currentGaugeScaleX;
	// �O�̗̑̓Q�[�W�X�P�[��
	float m_prevGaugeScaleX;
	// ���킶�팸������Q�[�W
	float m_lightGreenGaugeRate;
	bool m_gaugeFlag;
	// �o�ߎ���
	float												m_totalTime;

};

