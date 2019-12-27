#pragma once

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>

class Sound
{
private: // �\����

	struct WaveHeaderType
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};

public: // �A�N�Z�T

	// �T�E���h�̎擾
	IDirectSoundBuffer8* GetSound(int _number)
	{
		return m_secondaryBuffer1[_number];
	}

public: // �֐�

	// �R���X�g���N�^
	Sound();
	// �f�X�g���N�^
	~Sound() {}

	// ������
	bool Initialize(HWND _hwnd);
	// �I��
	void Shutdown();

private: // �T�u�֐�

	// DirectSound������
	bool InitializeDirectSound(HWND _hwnd);
	// DirectSound�I��
	void ShutdownDirectSound();

	// �t�@�C�����[�h
	bool LoadWaveFile(char* _fileName, IDirectSoundBuffer8** _secondaryBuffer, IDirectSound3DBuffer8** _secondary3DBuffer);
	// �t�@�C���̊J��
	void ShutdownWaveFile(IDirectSoundBuffer8** _secondaryBuffer, IDirectSound3DBuffer8** _secondary3DBuffer);

public: // �萔

	enum SoundName
	{
		SHOT,

		ALL_SOUND
	};

private:// �ϐ�

	// �_�C���N�g�T�E���h
	IDirectSound8*						m_directSound;
	// �v���C�}���o�b�t�@
	IDirectSoundBuffer*					m_primaryBuffer;

	// ���X�i�[
	IDirectSound3DListener8*			m_listener;

	// �Z�J���_���o�b�t�@
	IDirectSoundBuffer8*				m_secondaryBuffer1[ALL_SOUND];
	// �Z�J���_��3D�o�b�t�@
	IDirectSound3DBuffer8*				m_secondary3DBuffer1[ALL_SOUND];
};