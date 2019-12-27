#include "pch.h"

#include "Sound.h"

// コンストラクタ
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

// 初期化
bool Sound::Initialize(HWND _hwnd)
{
	bool result;


	// ダイレクトサウンドとプライマリバッファの初期化
	result = InitializeDirectSound(_hwnd);
	if (!result)
	{
		return false;
	}

	// Wavファイルをセカンダリバッファへ読み込む
	result = LoadWaveFile("catridge.wav", &m_secondaryBuffer1[0], &m_secondary3DBuffer1[0]);
	return true;
}

// 終了
void Sound::Shutdown()
{
	// セカンダリバッファの開放
	for (int i = 0; i < ALL_SOUND; i++)
	{
		ShutdownWaveFile(&m_secondaryBuffer1[i], &m_secondary3DBuffer1[i]);
	}

	// ダイレクトサウンドの終了
	ShutdownDirectSound();
}


bool Sound::InitializeDirectSound(HWND _hwnd)
{
	HRESULT result;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;


	// ダイレクトサウンドの初期化
	result = DirectSoundCreate8(NULL, &m_directSound, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// 協調レベルの設定とプライマリサウンドバッファの形式を変更可能に
	result = m_directSound->SetCooperativeLevel(_hwnd, DSSCL_PRIORITY);
	if (FAILED(result))
	{
		return false;
	}

	// プライマリバッファの設定
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// プライマリサウンドバッファの制御を取得
	result = m_directSound->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// プライマリサウンドバッファの形式を設定
	// CDオーディオ形式,44,100,16bit,wavファイル
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 2;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// プライマリバッファの波形を設定
	result = m_primaryBuffer->SetFormat(&waveFormat);
	if (FAILED(result))
	{
		return false;
	}

	// リスナーインターフェイスの取得
	result = m_primaryBuffer->QueryInterface(IID_IDirectSound3DListener8, (LPVOID*)&m_listener);
	if (FAILED(result))
	{
		return false;
	}

	// リスナーの初期位置をシーンの中央へ設定
	m_listener->SetPosition(0.0f, 0.0f, 0.0f, DS3D_IMMEDIATE);

	return true;
}

// ダイレクトサウンドの終了
void Sound::ShutdownDirectSound()
{
	// リスナーインターフェイスの開放
	if (m_listener)
	{
		m_listener->Release();
		m_listener = 0;
	}

	// プライマリサウンドバッファの開放
	if (m_primaryBuffer)
	{
		m_primaryBuffer->Release();
		m_primaryBuffer = 0;
	}

	// ダイレクトサウンドの開放
	if (m_directSound)
	{
		m_directSound->Release();
		m_directSound = 0;
	}

	return;
}


// ファイルのロード
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


	// Wavファイルを開く
	error = fopen_s(&filePtr, _filename, "rb");
	if (error != 0)
	{
		return false;
	}

	// Wavファイルのヘッダーを読み取る
	count = fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);
	if (count != 1)
	{
		return false;
	}

	// RIFF形式の確認
	if ((waveFileHeader.chunkId[0] != 'R') || (waveFileHeader.chunkId[1] != 'I') ||
		(waveFileHeader.chunkId[2] != 'F') || (waveFileHeader.chunkId[3] != 'F'))
	{
		return false;
	}

	// ファイル形式の確認
	if ((waveFileHeader.format[0] != 'W') || (waveFileHeader.format[1] != 'A') ||
		(waveFileHeader.format[2] != 'V') || (waveFileHeader.format[3] != 'E'))
	{
		return false;
	}

	// サブチャンクIDの確認
	if ((waveFileHeader.subChunkId[0] != 'f') || (waveFileHeader.subChunkId[1] != 'm') ||
		(waveFileHeader.subChunkId[2] != 't') || (waveFileHeader.subChunkId[3] != ' '))
	{
		return false;
	}

	// オーディオ形式の確認
	if (waveFileHeader.audioFormat != WAVE_FORMAT_PCM)
	{
		return false;
	}

	// モノラルかどうか
	if (waveFileHeader.numChannels != 1)
	{
		return false;
	}

	// 周波数の確認
	if (waveFileHeader.sampleRate != 44100)
	{
		return false;
	}

	// 16bit形式かどうか
	if (waveFileHeader.bitsPerSample != 16)
	{
		return false;
	}

	// データチャンクヘッダーの確認
	if ((waveFileHeader.dataChunkId[0] != 'd') || (waveFileHeader.dataChunkId[1] != 'a') ||
		(waveFileHeader.dataChunkId[2] != 't') || (waveFileHeader.dataChunkId[3] != 'a'))
	{
		return false;
	}

	// セカンダリバッファの波形を設定
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = 44100;
	waveFormat.wBitsPerSample = 16;
	waveFormat.nChannels = 1;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	// セカンダリサウンドバッファの設定
	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D;
	bufferDesc.dwBufferBytes = waveFileHeader.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	// サウンドバッファの作成
	result = m_directSound->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);
	if (FAILED(result))
	{
		return false;
	}

	// 一時セカンダリバッファの作成
	result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&*_secondaryBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// 一時バッファの開放
	tempBuffer->Release();
	tempBuffer = 0;

	// データチャンクヘッダーの末尾から始まる波形データの戦闘に移動
	fseek(filePtr, sizeof(WaveHeaderType), SEEK_SET);

	// 波形ファイルデータを保持する一時バッファの作成
	waveData = new unsigned char[waveFileHeader.dataSize];
	if (!waveData)
	{
		return false;
	}

	// Wavファイルのデータを新しく作成されたバッファに読み込み
	count = fread(waveData, 1, waveFileHeader.dataSize, filePtr);
	if (count != waveFileHeader.dataSize)
	{
		return false;
	}

	// 読み取り完了後、ファイルを閉じる
	error = fclose(filePtr);
	if (error != 0)
	{
		return false;
	}

	// セカンダリバッファをロックして、Wavデータを書き込む
	result = (*_secondaryBuffer)->Lock(0, waveFileHeader.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);
	if (FAILED(result))
	{
		return false;
	}

	// 波形データをバッファにコピー
	memcpy(bufferPtr, waveData, waveFileHeader.dataSize);

	// データが書き込まれた後、セカンダリバッファのロックを解除する
	result = (*_secondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);
	if (FAILED(result))
	{
		return false;
	}

	// 波形データを解放
	delete[] waveData;
	waveData = 0;

	// セカンダリサウンドバッファへの3Dインターフェイスを取得
	result = (*_secondaryBuffer)->QueryInterface(IID_IDirectSound3DBuffer8, (void**)&*_secondary3DBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

// ファイルの開放
void Sound::ShutdownWaveFile(IDirectSoundBuffer8** _secondaryBuffer, IDirectSound3DBuffer8** _secondary3DBuffer)
{
	// セカンダリサウンドバッファへの3Dインターフェイスを開放
	if (*_secondary3DBuffer)
	{
		(*_secondary3DBuffer)->Release();
		*_secondary3DBuffer = 0;
	}

	// セカンダリサウンドバッファを開放
	if (*_secondaryBuffer)
	{
		(*_secondaryBuffer)->Release();
		*_secondaryBuffer = 0;
	}

	return;
}