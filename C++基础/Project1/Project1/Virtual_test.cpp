#include <iostream>

using namespace std;

class Shape {
public:
	Shape();
	void calcArea(); // �麯��
	~Shape();  // ����������
};

Shape::Shape() 
{
	cout << "���ǹ��캯����" << endl;
}
Shape::~Shape() 
{
	cout << "��������" << endl;
}
void Shape::calcArea() 
{
	cout << "���㷽��" << endl;
}

int main()
{
	Shape *a = new Shape();
	a->calcArea();
	delete a;
	a = NULL;
	return 0;
}


