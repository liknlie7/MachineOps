#include "pch.h"

#include "Sound.h"

// �R���X�g���N�^
Sound::Sound()
	: m_directSound(0)
	, m_primaryBuffer(0)
	, m_listener(0)
{
	for (int i = 0; i < ALL_SOUND; i++)
	{
		m_secondaryBuffer1[i] = 0;
		m_secondary3DBuffer1[i] = 0;
	}
}

// ������
bool Sound::Initialize(HWND _hwnd)
{
	bool result;


	// �_�C���N�g�T�E���h�ƃv���C�}���o�b�t�@�̏�����
	result = InitializeDirectSound(_hwnd);
	if (!result)
	{
		return false;
	}

	// Wav�t�@�C�����Z�J���_���o�b�t�@�֓ǂݍ���
	result = LoadWaveFile("catridge.wav", &m_secondaryBuffer1[0], &m_secondary3DBuffer1[0]);
	return true;
}

// �I��
void Sound::Shutdown()
{
	// �Z�J���_���o�b�t�@�̊J��
	for (int i = 0; i < ALL_SOUND; i++)
	{
		ShutdownWaveFile(&m_secondaryBuffer1[i], &m_secondary3DBuffer1[i]);
	}

	// �_�C���N�g�T�E���h�̏I��
	ShutdownDirectSound();
}


bool Sound::InitializeDirectSound(HWND _hwnd)
{
	HRESULT result;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;


	// �_�C���N�g�T�E���h�̏�����
	result = DirectSoundCreate8(NULL, &m_directSound, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// �������x���̐ݒ�ƃv���C�}���T�E���h�o�b�t�@�̌`����ύX�\��
	result = m_directSound->SetCooperativeLevel(_hwnd, DSSCL_PRIORITY);
	if (FAILED(result))
	{
		return false;
	}

	// �v���C�}���o�b�t�@�̐ݒ�
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// �v���C�}���T�E���h�o�b�t�@�̐�����擾
	result = m_directSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// �v���C�}���T�E���h�o�b�t�@�̌`����ݒ�
	// CD�I�[�f�B�I�`��,44,100,16bit,wav�t�@�C��
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// �v���C�}���o�b�t�@�̔g�`��ݒ�
	result = m_primaryBuffer->SetFormat(&waveFormat);
	if (FAILED(result))
	{
		return false;
	}

	// ���X�i�[�C���^�[�t�F�C�X�̎擾
	result = m_primaryBuffer->QueryInterface(IID_IDirectSound3DListener8, (LPVOID*)&m_listener);
	if (FAILED(result))
	{
		return false;
	}

	// ���X�i�[�̏����ʒu���V�[���̒����֐ݒ�
	m_listener->SetPosition(0.0f, 0.0f, 0.0f, DS3D_IMMEDIATE);

	return true;
}

// �_�C���N�g�T�E���h�̏I��
void Sound::ShutdownDirectSound()
{
	// ���X�i�[�C���^�[�t�F�C�X�̊J��
	if (m_listener)
	{
		m_listener->Release();
		m_listener = 0;
	}

	// �v���C�}���T�E���h�o�b�t�@�̊J��
	if (m_primaryBuffer)
	{
		m_primaryBuffer->Release();
		m_primaryBuffer = 0;
	}

	// �_�C���N�g�T�E���h�̊J��
	if (m_directSound)
	{
		m_directSound->Release();
		m_directSound = 0;
	}

	return;
}


// �t�@�C���̃��[�h
bool Sound::LoadWaveFile(char* _filename, IDirectSoundBuffer8** _secondaryBuffer, IDirectSound3DBuffer8** _secondary3DBuffer)
{
	int error;
	FILE* filePtr;
	unsigned int count;
	WaveHeaderType waveFileHeader;
	WAVEFORMATEX waveFormat;
	DSBUFFERDESC bufferDesc;
	HRESULT result;
	IDirectSoundBuffer* tempBuffer;
	unsigned char* waveData;
	unsigned char* bufferPtr;
	unsigned long bufferSize;


	// Wav�t�@�C�����J��
	error = fopen_s(&filePtr, _filename, "rb");
	if (error != 0)
	{
		return false;
	}

	// Wav�t�@�C���̃w�b�_�[��ǂݎ��
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	// RIFF�`���̊m�F
	if ((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') ||
		(waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
	{
		return false;
	}

	// �t�@�C���`���̊m�F
	if ((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
		(waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
	{
		return false;
	}

	// �T�u�`�����NID�̊m�F
	if ((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
		(waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
	{
		return false;
	}

	// �I�[�f�B�I�`���̊m�F
	if (waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
	{
		return false;
	}

	// ���m�������ǂ���
	if (waveFileHeader.numChannels != 1)
	{
		return false;
	}

	// ���g���̊m�F
	if (waveFileHeader.sampleRate != 44100)
	{
		return false;
	}

	// 16bit�`�����ǂ���
	if (waveFileHeader.bitsPerSample != 16)
	{
		return false;
	}

	// �f�[�^�`�����N�w�b�_�[�̊m�F
	if ((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
		(waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
	{
		return false;
	}

	// �Z�J���_���o�b�t�@�̔g�`��ݒ�
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 1;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// �Z�J���_���T�E���h�o�b�t�@�̐ݒ�
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// �T�E���h�o�b�t�@�̍쐬
	result = m_directSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// �ꎞ�Z�J���_���o�b�t�@�̍쐬
	result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*_secondaryBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// �ꎞ�o�b�t�@�̊J��
	tempBuffer->Release();
	tempBuffer = 0;

	// �f�[�^�`�����N�w�b�_�[�̖�������n�܂�g�`�f�[�^�̐퓬�Ɉړ�
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

	// �g�`�t�@�C���f�[�^��ێ�����ꎞ�o�b�t�@�̍쐬
	waveData = new unsigned char[waveFileHeader.dataSize];
	if (!waveData)
	{
		return false;
	}

	// Wav�t�@�C���̃f�[�^��V�����쐬���ꂽ�o�b�t�@�ɓǂݍ���
	count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
	if (count != waveFileHeader.dataSize)
	{
		return false;
	}

	// �ǂݎ�芮����A�t�@�C�������
	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	// �Z�J���_���o�b�t�@�����b�N���āAWav�f�[�^����������
	result = (*_secondaryBuffer)->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if (FAILED(result))
	{
		return false;
	}

	// �g�`�f�[�^���o�b�t�@�ɃR�s�[
	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);

	// �f�[�^���������܂ꂽ��A�Z�J���_���o�b�t�@�̃��b�N����������
	result = (*_secondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if (FAILED(result))
	{
		return false;
	}

	// �g�`�f�[�^�����
	delete[] waveData;
	waveData = 0;

	// �Z�J���_���T�E���h�o�b�t�@�ւ�3D�C���^�[�t�F�C�X���擾
	result = (*_secondaryBuffer)->QueryInterface(IID_IDirectSound3DBuffer8, (void**)&*_secondary3DBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

// �t�@�C���̊J��
void Sound::ShutdownWaveFile(IDirectSoundBuffer8** _secondaryBuffer, IDirectSound3DBuffer8** _secondary3DBuffer)
{
	// �Z�J���_���T�E���h�o�b�t�@�ւ�3D�C���^�[�t�F�C�X���J��
	if (*_secondary3DBuffer)
	{
		(*_secondary3DBuffer)->Release();
		*_secondary3DBuffer = 0;
	}

	// �Z�J���_���T�E���h�o�b�t�@���J��
	if (*_secondaryBuffer)
	{
		(*_secondaryBuffer)->Release();
		*_secondaryBuffer = 0;
	}

	return;
}