#include <iostream>
#include <stdio.h>
/*
	������¼���� ָ��/����֮���
	����ֻ�Ǳ���
	�������� int &x ����ֱ��ʵ�κ��βα�ʹ��
	const int &x ʱ���Ը�ֵ �������ڲ����������Բ��ܱ��޸� ����������������  ������ֵ/�Ͳ�ƥ�����͵Ĳ���
	����long long
	
*/
using namespace std;

void f( const int &x)
{
	int p = x;
	cout<< p<<endl;

}


int main()
{
	int p = 5;
	int q = 7;
	int *const x = &p;
	long l = 100001;
	int &y = q;
	//q = 10;
	y = 99;
	
	cout<<  *x <<endl;
	cout << y << endl;
	cout << "q:" << &q << endl;
	f(l);
	cout << "f:"<< q << endl;

	system("pause");
	return 0;
}


