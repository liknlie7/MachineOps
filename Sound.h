#pragma once

#include <windows.h>
#include <mmsystem.h>
#include <dsound.h>
#include <stdio.h>

class Sound
{
private: // 構造体

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

public: // アクセサ

	// サウンドの取得
	IDirectSoundBuffer8* GetSound(int _number)
	{
		return m_secondaryBuffer1[_number];
	}

public: // 関数

	// コンストラクタ
	Sound();
	// デストラクタ
	~Sound() {}

	// 初期化
	bool Initialize(HWND _hwnd);
	// 終了
	void Shutdown();

private: // サブ関数

	// DirectSound初期化
	bool InitializeDirectSound(HWND _hwnd);
	// DirectSound終了
	void ShutdownDirectSound();

	// ファイルロード
	bool LoadWaveFile(char* _fileName, IDirectSoundBuffer8** _secondaryBuffer, IDirectSound3DBuffer8** _secondary3DBuffer);
	// ファイルの開放
	void ShutdownWaveFile(IDirectSoundBuffer8** _secondaryBuffer, IDirectSound3DBuffer8** _secondary3DBuffer);

public: // 定数

	enum SoundName
	{
		SHOT,

		ALL_SOUND
	};

private:// 変数

	// ダイレクトサウンド
	IDirectSound8*						m_directSound;
	// プライマリバッファ
	IDirectSoundBuffer*					m_primaryBuffer;

	// リスナー
	IDirectSound3DListener8*			m_listener;

	// セカンダリバッファ
	IDirectSoundBuffer8*				m_secondaryBuffer1[ALL_SOUND];
	// セカンダリ3Dバッファ
	IDirectSound3DBuffer8*				m_secondary3DBuffer1[ALL_SOUND];
};