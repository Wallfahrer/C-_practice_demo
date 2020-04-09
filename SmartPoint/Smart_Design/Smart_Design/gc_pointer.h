#pragma once
/*
	Pointer implements a pointer type that uses
	garbage collection to release unused memory.
	A Pointer must only be used to point to memory
	that was dynamically allocated using new.
	When used to refer to an allocated array,
	specify the array size.
*/
#include <iostream>
#include <list>
#include <typeinfo>
#include <cstdlib>
#include "gc_details.h"
#include "gc_iterator.h"

using namespace std;

template<class T,int size=0>
class Pointer
{
private:
	// refContainerά�������ռ��б�
	static list<PtrDetails<T>> refContainer;
	// ���һ��ָ��ָ��ǰ�����˵��ڴ�
	T *addr;
	// �ж��Ƿ���һ��array
	bool isArray;
	// ����
	unsigned arraySize;
	// �Ƿ��һ��ָ���Ѿ�������
	static bool first;
	// ��refContainer�з���ָ��ָ����ϸ��Ϣ�ĵ�����
	typename list<PtrDetails<T>>::iterator findPtrInfo(T *ptr);

public:
	// ����һ��ָ�����������
	typedef Iter<T> GCiterator;
	// Empty constructor
	// NOTE: templates aren't able to have prototypes with default arguments
	// this is why constructor is designed like this
	Pointer()
	{
		Pointer(NULL);
	}
	Pointer(T*);
	// �������캯��
	Pointer(const Pointer &ob);
	// ��������
	~Pointer();
	// �������������ҷ����Ƿ����һ������������Ƿ��ͷ�
	static bool collect();
	// ָ�뵽ָ������ظ�ֵ
	T *operator=(T *t);
	Pointer &operator=(Pointer &rv);
	// ����ָ�������ص�ָ��
	T &operator*()
	{
		return *addr;
	}
	// ���ص�ַ
	T *operator->()
	{
		return addr;
	}
	// ���ؾ���������Ӧ�ĵ�ַ
	T &operator[](int i)
	{
		return addr[i];
	}
	// ��Iter���ص��ѷ����ڴ�Ŀ�ͷ
	Iter<T> begin()
	{
		int _size;
		if (isArray) {
			_size = arraySize;
		}
		else {
			_size = 1;
		}
		return Iter<T>(addr, addr, addr + _size);
	}
	// ��Iter���ص��ѷ�������ĩβ֮���ֵ
	Iter<T> end()
	{
		int _size = 0;
		if (isArray) {
			_size = arraySize;
		}
		else {
			_size = 1;
		}
		return  Iter<T>(addr+_size,addr,addr+_size);
	}
	//���ش�����ָ���refContainer��С(list)
	static int refContainerSize()
	{
		return refContainer.size();
	}
	// ��ʾrefContainer����������
	static void showlist();
	// ���refContainer�������˳�ʱ
	static void shutdown();
};

// ʵ�ֺ���
// ��̬������ʼ��������һ���ڴ����̬����
template<class T,int size>
list<PtrDetails<T>> Pointer<T, size>::refContainer;

template<class T,int size>
bool Pointer<T, size>::first = true;

//��ʼ�������δ��ʼ������Ĺ��캯��
template<class T, int size>
Pointer<T, size>::Pointer(T *t)
{
	// ��shutdown()����ע���Ϊһ��exit()����,ʹ����main�����󱻵���
	if (first)
	{
		atexit(shutdown);
	}
	first = false;
	typename list<PtrDetails<T>>::iterator  p;
	p = findPtrInfo(t);

	if (p != refContainer.end())
	{
		p->refcount++;
	}
	else {
		PtrDetails<T> obj(t, size);
		refContainer.push_front(obj);
	}

	addr = t;
	arraySize = size;
	if (size > 0) {
		isArray = true;
	}
	else {
		isArray = false;
	}
}

// �������캯�������л�����ʱ����Ҫʹ�õ�
template<class T,int size>
Pointer<T, size>::Pointer(const Pointer &ob)
{
	typename list<PtrDetails<T>>::iterator p;
	p = findPtrInfo(ob.addr);
	// ����������
	p->refcount++;
	addr = ob.addr;
	arraySize = ob.arraySize;
	if (arraySize > 0)
	{
		isArray = true;
	}
	else {
		isArray = false;
	}
}

// ��������
template <class T, int size>
Pointer<T, size>::~Pointer()
{
	typename list<PtrDetails<T>>::iterator p;
	p = findPtrInfo(addr);
	if (p->refcount) {
		p->refcount--;
	}
	collect();
}

// �������������Ƿ������һ��ָ�룬����ǵ��ͷŵ�
template <class T, int size>
bool Pointer<T, size>::collect()
{
	// collect() will be called in the destructor,�����������б�����
	bool memfreed = false;
	typename list<PtrDetails<T>>::iterator p;
	do {
		for (p = refContainer.begin(); p != refContainer.end(); p++)
		{
			if (p->refcount > 0) continue;
			memfreed = true;
			refContainer.remove(*p);

			if (p->memPtr) {
				if (p->isArray) {
					delete[] p->memPtr;
				}
				else
				{
					delete p->memPtr;
				}
			}
			break;
		}
	} while (p != refContainer.end());
	return memfreed;
}

// �������
template <class T, int size>
T *Pointer<T, size>::operator=(T *t)
{
	typename list<PtrDetails<T>>::iterator p;
	p = findPtrInfo(addr);
	p->refcount--;
	p = findPtrInfo(t);
	if (p != refContainer.end()) {
		p->refcount++;
	}
	else {
		PtrDetails<T> obj(t, size);
		refContainer.push_front(obj);
	}
	addr = t;
	return t;
}

template <class T, int size>
Pointer<T, size> &Pointer<T, size>::operator=(Pointer &rv)
{
	typename list<PtrDetails<T>>::iterator p;
	p = findPtrInfo(addr);
	p->refcount--;
	p = findPtrInfo(rv.addr);
	p->refcount++;
	addr = rv.addr;
	return rv;
}

// show function()
template <class T, int size>
void Pointer<T, size>::showlist()
{
	typename list<PtrDetails<T>>::iterator p;
	cout << "refContainer :" << typeid(T).name << endl;
	cout<< "memPtr refcount value\n ";
	if (refContainer.begin() == refContainer.end())
	{
		cout << "refContainer is empty" << endl;
	}

	for (p = refContainer.begin(); p != refContainer.end(); p++)
	{
		cout << "[" << (void *)p->memPtr << "]" << " " << p->refcount << endl;
		if (p->memPtr) 
		{ cout << " " << *p->memPtr; }
		else
		{
			cout << "- - -";
			cout << endl;
		}
	}
	cout << endl;
}

template <class T, int size>
void Pointer<T, size>::shutdown()
{
	if (refContainerSize() == 0)
	{
		return; // ��ʱ�ǿ�����
	}
	typename list<PtrDetails<T>>::iterator p;
	for (p = refContainer.begin(); p != refContainer.end(); p++)
	{
		// ��������ص����ü�������0
		p->refcount = 0;
	}
	// ����ڴ�
	collect();
}

template <class T, int size>
typename list<PtrDetails<T>>::iterator  Pointer<T, size>::findPtrInfo(T *ptr)
{
	typename list<PtrDetails<T>>::iterator p;
	// ���ָ��ptr �� refContainer������
	for (p = refContainer.begin(); p != refContainer.end(); p++)
	{
		if (p->memPtr == ptr) {
			return p;
		}
	}
	return p;
}






