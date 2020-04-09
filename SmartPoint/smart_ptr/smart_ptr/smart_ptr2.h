#pragma once
#include <functional>
/*
	functionalģ�� ����������ã�
	map<string, function<int(int, int)>> binops;
	binops = {
		{"+",add},
		{"-",std::minus<int>()},
		{"/",divide()},
		{"*",[](int i,int j) {return i*j; }},
		{"%",mod}
	};
	binops["+"](10, 5); //����add(10,5);
	binops["-"](10, 5); //ʹ��minus<int>����ĵ��������
	binops["/"](10, 5); //ʹ��divide����ĵ��������
	binops["*"](10, 5); //����lambda��������

*/

using namespace std;
// ģ��shared_ptrʵ��һ������ָ��
template<class T>
class smart_ptr 
{
public:
	// �޲�������
	smart_ptr();
	// һ����������
	explicit smart_ptr(T*);
	// ����
	smart_ptr(const smart_ptr&);
	// ���������Ĺ���
	smart_ptr(T*, function<void(T*)>);
	// ����
	smart_ptr& operator=(const smart_ptr&);
	// ����
	T& operator*() const;
	// ���ط����������
	T* operator->() const;

	// ����
	~smart_ptr();
	// ��bool����ת��
	explicit operator bool() const;

	// ����Ƿ�Ψһ
	bool unique();
	// ���ú���
	void reset();
	void reset(T*);
	void reset(T*,function<void(T*)>);
	// �ͷ�
	T* release();
	// ��ȡ��ַ
	T* get() const;

private:
	// Ĭ��delete
	// function<void(T*)>��ʼ��һ��T* ���͵�default_del
	static function<void(T*)> default_del;
private:
	unsigned* m_p_use_count = nullptr;
	T* m_pobject = nullptr;
	function<void(T*)> m_del = default_del;
};

// �����Ĭ��delete����
template<class T>
function<void(T*)> smart_ptr<T>::default_del = [](T *p) 
{delete p; p = nullptr; }

// ����һ��ģʽT������һ���������args ��ͬһ��ģʽT���Դ����������
// C++11�����ص� &&��ֵ���ã�move�����ƶ�,forword����ת��
// ��ֵ�����ڴ濽����������ܣ� forword����ֵת��Ϊ��ֵ
template <typename T, typename... Args>
smart_ptr<T> make_smart(Args&&... args)
{
	smart_ptr<T> sp(new T(std::forward<Args>(args)...));
	return sp;
}

template<class T>
smart_ptr<T>::smart_ptr():m_pobject(nullptr),m_p_use_count(new unsigned(1))
{
}

template<class T>
smart_ptr<T>::smart_ptr(T *p):m_pobject(p),m_p_use_count(new unsigned(1))
{

}

template<class T>
smart_ptr<T>::smart_ptr(T *p,function<void(T*)> del):m_pobject(p),m_p_use_count(new unsigned(1)),m_del(del)
{
}

// ��������������һ���µ�ָ����������������++
template<class T>
smart_ptr<T>::smart_ptr(const smart_ptr & s):m_pobject(s.m_pobject), m_p_use_count(s.m_p_use_count),m_del(s.m_del)
{
	(*m_p_use_count)++;
}

template<class T>
smart_ptr<T>& smart_ptr<T>::operator =(const smart_ptr &s)
{
	m_del = s.m_del;
	// �ݼ�����������ü���
	++(*s.m_p_use_count);
	// �������Ķ���û�������û��ˣ����ͷŶ������ĳ�Ա
	if (--(*m_p_use_count) == 0)
	{
		m_del(m_pobject);
		delete m_p_use_count;
	}
	m_p_use_count = s.m_p_use_count;
	m_pobject = s.m_pobject;
	// ���ظö���
	return *this;
};

template<class T>
T& smart_ptr<T>::operator*() const
{
	return *m_pobject;
}

template<class T>
T* smart_ptr<T>::operator->() const
{
	return &this->operator*();
}

template<class T>
smart_ptr<T>::~smart_ptr()
{
	if (--(*m_p_use_count) == 0)
	{
		m_del(m_pobject);
		m_pobject = nullptr;

		delete m_p_use_count;
		m_p_use_count = nullptr;
	}
}

template<class T>
bool smart_ptr<T>::unique()
{
	return *m_p_use_count == 1;
}

template<class T>
void smart_ptr<T>::reset()
{
	(*m_p_use_count)--;
	if (*m_p_use_count == 0) 
	{
		m_del(m_pobject);
	}
	m_pobject = nullptr;
	*m_p_use_count = 1;
	m_del = default_del;
}

template<class T>
void smart_ptr<T>::reset(T *p)
{
	(*m_p_use_count)--;
	if (*m_p_use_count == 0)
	{
		m_del(m_pobject);
	}
	m_pobject = p;
	*m_p_use_count = 1;
	m_del = default_del;

}

template<class T>
T*  smart_ptr<T>::release()
{
	(*m_p_use_count)--;
	if (*m_p_use_count == 0)
	{
		m_del(m_pobject);
	}
	auto p = m_pobject;
	m_pobject = nullptr;
	return p;
}

template<class T>
T* smart_ptr<T>::get() const
{
	return m_pobject;
}

template<class T>
smart_ptr<T>::operator bool ()const
{
	return m_pobject != nullptr;
}





















