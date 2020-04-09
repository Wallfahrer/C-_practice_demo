#pragma once
#include <iostream>
using namespace std;

// ����ģʽ
class Singleton {
private:
	// ���캯��
	Singleton() {}
	// ��������
	~Singleton() {}
	// ����
	Singleton(const Singleton&);
	// ����
	Singleton & operator= (const Singleton &);
public:
	static Singleton&GetInstance()
	{
		cout << "Singleton&GetInstance " << endl;
		static Singleton instance;
		return instance;
	}
	void DoSomething();
};

