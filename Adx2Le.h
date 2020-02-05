/// ADX2LE���������C�u����
#pragma once

#include <string>
#include <cri_adx2le.h>



// ADX2LE�N���X
class Adx2Le
{
public: // ��{

	// �R���X�g���N�^
	Adx2Le();
	// �f�X�g���N�^
	~Adx2Le();

public: // �V�X�e���ɑ΂��鑀��

	// ����������
	void Initialize(const wchar_t* atomConfigFile);
	// �I������
	void Finalize();
	// �X�V����
	void Update();

	// ACB�t�@�C��(�L���[�V�[�g���)�̓ǂݍ���
	void LoadAcbFile(const wchar_t* atomCueSheetBinaryFile, const wchar_t* atomWaveBankFile = L"");

public: // �v���[���ɑ΂��鑀��

	// �w��L���[�̍Đ� 
	CriAtomExPlaybackId Play(CriAtomExCueId cueId, float volume = 1.0f);

	// �v���[���̈ꎞ��~
	void Pause();

	// �v���[���̈ꎞ��~��Ԃ̉���
	void Resume();

	// �v���[���̒�~
	void Stop();

	// �v���[���̉��ʂ̐ݒ�
	void SetVolume(float volume);

public: // �v���[���ɑ΂����Ԃ̖₢���킹

	// �v���[�����ꎞ��~��Ԃ��ǂ���
	bool IsPaused();

public:	// �����ɑ΂��鑀��

	// ID�w�肵���������ꎞ��~
	void PauseByID(CriAtomExPlaybackId playbackId);

	// ID�w�肵�������̈ꎞ��~��Ԃ̉���
	void ResumeByID(CriAtomExPlaybackId playbackId);

	// ID�w�肵���������~
	void StopByID(CriAtomExPlaybackId playbackId);

	// ID�w�肵�������̉��ʂ̐ݒ�
	void SetVolumeByID(CriAtomExPlaybackId playbackId, float volume);

public: // �����ɑ΂����Ԃ̖₢���킹

	// ID�w�肵���������Đ���(�Đ����������܂�)���ǂ���
	bool IsPlayingByID(CriAtomExPlaybackId playbackId);

	// ID�w�肵���������ꎞ��~��Ԃ��ǂ���
	bool IsPausedByID(CriAtomExPlaybackId playbackId);

	// ID�w�肵���������Đ��I��(��~���܂�)��Ԃ��ǂ���
	bool IsPlayEndedByID(CriAtomExPlaybackId playbackId);

private: // �R�[���o�b�N�֐�

	// �G���[�R�[���o�b�N
	static void  OnError(const CriChar8* errorId, CriUint32 p1, CriUint32 p2, CriUint32* parray);

	// �������A���P�[�^
	static void* Allocate(void* obj, CriUint32 size);
	static void  Deallocate(void* obj, void* ptr);

private: // ������̕ϊ�

	// wstring ����string�ւ̕ϊ�
	static std::string WStringToString(const std::wstring& s);

	// string ����wstring�ւ̕ϊ�
	static std::wstring StringToWString(const std::string& s);

private: // �N���X�萔

	// �����Đ����֘A
	static const int MAX_VOICES;            // �v�[�����鉹���̐�
	static const int MAX_VIRTUAL_VOICES;    // �A�v���P�[�V�����œ����ɔ���������s�������̐�
	static const int MAX_LOADERS;           // �A�v���P�[�V�������Ŏg�p���郍�[�_�̐�

	// �T���v�����O���[�g�֘A
	static const int MAX_SAMPLING_RATE;      // �Đ����鉹���̃T���v�����O���[�g
	static const int SAMPLING_RATE_HCAMX;    // �Đ�����HCA-MX�f�[�^�̃T���v�����O���[�g

private: // �����o�ϐ�

	CriAtomExPlayerHn    m_player;              // �����Đ��p�v���[��
	CriAtomExVoicePoolHn m_standardVoicePool;   // ADX/HCA�R�[�f�b�N�p�{�C�X�v�[��
	CriAtomExVoicePoolHn m_hcamxVoicePool;		// HCA-MX�R�[�f�b�N�p�{�C�X�v�[��
	CriAtomExAcbHn       m_acb;                 // �L���[�V�[�g���
	CriAtomDbasId        m_dbas;                // D-BAS

};
