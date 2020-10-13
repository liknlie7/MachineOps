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

	Singleton() {}				// �O���ł̃C���X�^���X�쐬���֎~����
	virtual ~Singleton() {}

private:

	Singleton(const Singleton&) = delete;               // �R�s�[�R���X�g���N�^�̍폜
	Singleton& operator=(const Singleton&) = delete;    // ������Z�q�̍폜
	Singleton(Singleton&&) = delete;                    // ���[�u�R���X�g���N�^�̍폜
	Singleton& operator=(Singleton&&) = delete;         // ���[�u������Z�q�̍폜
};