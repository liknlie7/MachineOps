#pragma once

template <class T>
class Singleton
{
public:

	static inline T* GetInstance()
	{
		static T instance;
		return &instance;
	}

protected:

	Singleton() {}				// 外部でのインスタンス作成を禁止する
	virtual ~Singleton() {}

private:

	Singleton(const Singleton&) = delete;               // コピーコンストラクタの削除
	Singleton& operator=(const Singleton&) = delete;    // 代入演算子の削除
	Singleton(Singleton&&) = delete;                    // ムーブコンストラクタの削除
	Singleton& operator=(Singleton&&) = delete;         // ムーブ代入演算子の削除
};