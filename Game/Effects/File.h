#pragma once

#include <fstream>

// �t�@�C���Ǘ��N���X
class File
{
public: // ��{

	File(const wchar_t *fname);
	~File();

public: // �A�N�Z�b�T
	char* GetData() { return m_data; }
	unsigned int GetSize() { return m_length; }

public: // �ϐ�

	// �T�C�Y
	int m_length;

	// �ǂݍ��ݐ�̃o�b�t�@
	char* m_data;

};
