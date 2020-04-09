#pragma once
// C++ ���
// ǳ����ֻ�Ƕ�ָ��Ŀ���������������ָ��ָ�������ڴ�ռ䣬
// ���������ָ����п��������Ҷ�ָ��ָ�������Ҳ���п����������������ָ����ָ��������ͬ�ĵ�ַ
#include<iostream>
#include <string.h>
using namespace std;

class C_DeepRep 
{
public:
	// ���캯��
	C_DeepRep(const char *Name)
	{
		_Name = new char[strlen(Name)+1];
		memcpy(_Name,Name,strlen(Name)+1);
	}
	// ����
	C_DeepRep(const C_DeepRep& cd)
	{
		cout << "��ȿ���" << endl;
		C_DeepRep strTemp(cd._Name);
		swap(_Name,strTemp._Name);
	}

	// ��������
	~C_DeepRep()
	{
		if (_Name) 
		{
			cout << "��������" << endl;
			delete[] _Name;
		}
	}

	void show()
	{
		cout << "Name :" << _Name <<endl;
	}

	void setName(const char *pName)
	{
		_Name = new char[strlen(pName) + 1];
		memcpy(_Name, pName, strlen(pName) + 1);
	}


private:
	char* _Name;
	int nAge;
};



