#pragma once
/*
	������ܷ������쳣��ʹ��һЩ����������ĵ�����iter
	
*/
#include <iostream>

using namespace std;

class OutOfRangeExc
{
	// �����쳣��
	// ��Ӻ��������Ҫ��������
	OutOfRangeExc()
	{
		cout << "Attempted Access is Out of Range" << endl;
	}
};

// ��Ҫ���д���һ��������iter
template<class T>
class Iter
{
private:
	T *ptr;
	// current pointer value
	T *end;
	// points to element one past end
	T *begin;
	// points to start of allocated array
	unsigned length; // �����ĳ���

public:
	Iter()
	{
		ptr = end = begin = NULL;
		length = 0;
	}
	Iter(T *p,T *first,T *last)
	{
		ptr = p;
		begin = first;
		end = last;
		length = last - first;
	}
	// Return length of sequence to which this
	// Iter points.
	unsigned size() { return length; }
	// Return value pointed to by ptr.
	// Do not allow out-of-bounds access. ����Խ��
	T &operator*() {
		if ((ptr >= end) || (ptr < begin)) {
			throw OutOfRangeExc();
		}
		return *ptr;
	}

	// Return address contained in ptr.
	// Do not allow out-of-bounds access.
	T *operator->()
	{
		if ((ptr >= end) || (ptr < begin))
		{
			throw OutOfRangeExc();
		}
		return ptr;
	}

	// ���� ǰ��++
	Iter operator++()
	{
		ptr++;
		return *this;
	}
	// ǰ�� - -
	Iter operator--()
	{
		ptr--;
		return *this;
	}
	// ����++
	Iter operator++(int)
	{
		T *tmp = ptr;
		ptr++;
		return Iter<T>(tmp,begin,end);
	}
	// ����--
	Iter operator--(int)
	{
		T *tmp = ptr;
		ptr--;
		return Iter<T>(tmp, begin, end);
	}
	// Return a reference to the object at the specified index
	T &operator[](int i)
	{
		if (i < 0 || i >= (end - begin)) {
			throw OutOfRangeExc();
		}
	}
	// ��ع�ϵ������
	bool operator==(const Iter &op2)
	{
		return ptr == op2.ptr;
	}
	bool operator!=(const Iter &op2)
	{
		return ptr != op2.ptr;
	}
	bool operator<(const Iter &op2)
	{
		return ptr < op2.ptr;
	}
	bool operator<=(const Iter &op2)
	{
		return ptr <= op2.ptr;
	}
	bool operator>(const Iter &op2)
	{
		return ptr > op2.ptr;
	}
	bool operator>=(const Iter &op2)
	{
		return ptr >= op2.ptr;
	}
	
	// ����+ - ���� ����
	Iter operator-(int n)
	{
		ptr -= n;
		return *this;
	}
	Iter operator+(int n)
	{
		ptr += n;
		return *this;
	}
	// ��������iter������֮���Ԫ�ظ���
	int operator-(const Iter<T> &itr2)
	{
		return ptr - itr2.ptr;
	}
};






