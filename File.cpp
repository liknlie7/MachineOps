#include "pch.h"
#include "File.h"
#include <limits>

using namespace std;

// コンストラクタ
File::File(const wchar_t *fname)
: m_length(0)
, m_data(nullptr)
{
	ifstream in(fname, ios::in | ios::binary);

	// オープン成功？
	_ASSERT(in);

	// ファイルサイズを取得
	ios::pos_type tmp = in.tellg();
	ios::off_type size_ = in.seekg(0, ios::end).tellg() - in.seekg(0, ios::beg).tellg();
	in.seekg(tmp);

	// ファイルサイズがintで表せる最大値を超えていないか
	_ASSERT(!(std::numeric_limits<int>::max() < size_));
	m_length = static_cast<int>(size_);

	//メモリを確保して読み込む
	m_data = new char[m_length];
	in.read(m_data, m_length);

	// クローズ
	in.close();
}

// デストラクタ
File::~File()
{
	if (m_data)
	{
		delete[] m_data;
	}
}

