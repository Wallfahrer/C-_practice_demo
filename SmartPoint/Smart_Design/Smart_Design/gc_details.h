#pragma once
// ��Ҫ��Ϊ��ʵ��һ���Լ����������ܣ��������ջ���,ǿ��һ��template��ʹ��
// This class defines an element that is stored,�����˱��洢��Ԫ��
// in the garbage collection information list.
#include <iostream>

using namespace std;

template<class T>
class PtrDetails 
{
public:
	// ��ǰ���ü���
	unsigned refcount;
	// ָ���Ѿ������ڴ��ָ��
	T *memPtr;
	// ָ��ָ����Ƿ���һ������������
	bool isArray;
	// ���鳤��
	unsigned arraysize;
	// ����ϸ�ڴ������ָ�������ˣ�size���������С
	PtrDetails(T *mPtr,unsigned size = 0)
	{
		refcount = 1;
		memPtr = mPtr;
		arraysize = size;
		
		if (size != 0)
		{
			isArray = true;
		}
		else 
		{
			isArray = false;
		}
	}
};

// Overloading operator== allows two class objects to be compared.
// This is needed by the STL list class.
template<class T>
bool operator==(const PtrDetails<T> & obj1, const PtrDetails<T> & obj2)
{
	return obj1.memPtr == obj2.memPtr;
}





