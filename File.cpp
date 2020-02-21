#include "pch.h"
#include "File.h"
#include <limits>

// �R���X�g���N�^
File::File(const wchar_t *fname)
: m_length(0)
, m_data(nullptr)
{
	std::ifstream in(fname, std::ios::in | std::ios::binary);

	// �I�[�v�������H
	_ASSERT(in);

	// �t�@�C���T�C�Y���擾
	std::ios::pos_type tmp = in.tellg();
	std::ios::off_type size_ = in.seekg(0, std::ios::end).tellg() - in.seekg(0, std::ios::beg).tellg();
	in.seekg(tmp);

	// �t�@�C���T�C�Y��int�ŕ\����ő�l�𒴂��Ă��Ȃ���
	_ASSERT(!(std::numeric_limits<int>::max() < size_));
	m_length = static_cast<int>(size_);

	//���������m�ۂ��ēǂݍ���
	m_data = new char[m_length];
	in.read(m_data, m_length);

	// �N���[�Y
	in.close();
}

// �f�X�g���N�^
File::~File()
{
	if (m_data)
	{
		delete[] m_data;
	}
}

