#pragma once
// ǳ����
#include <iostream>
#include <string.h>
using namespace std;

class ShallowRep 
{
public:
	// ���캯��
	ShallowRep(const char *Name)
	{

		// �ж�ָ���Ƿ�Ϊ��
		if (Name == NULL)
		{
			Name = new char[1];
		}
		else 
		{
			Name = new char[strlen(Name)+1];
			memcpy(_Name,Name,strlen(Name)+1 );
		}
	}
	// ����
	~ShallowRep()
	{
		cout << "������������" << endl;
		if (_Name)
		{
			delete[] _Name;
		}
	}
	void show() 
	{
		cout << "name is : "<<_Name << endl;
	}






private:
	char* _Name;
};
