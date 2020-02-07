#pragma once

#include <fstream>

// ファイル管理クラス
class File
{
public: // 基本

	File(const wchar_t *fname);
	~File();

public: // アクセッサ
	char* GetData() { return m_data; }
	unsigned int GetSize() { return m_length; }

public: // 変数

	// サイズ
	int m_length;

	// 読み込み先のバッファ
	char* m_data;

};
