#include "Operate.h"

int main()
{
	Box b1;
	Box b2;
	Box b3;
	Box b4;
	double volume = 0.0;

	b1.setLength(3.0);
	b1.setHeight(2.0);
	b1.setBreadth(4.0);
	volume = b1.getVolume();
	cout << "b1 �����:" << volume << endl;

	b2.setLength(2.0);
	b2.setHeight(4.5);
	b2.setBreadth(3.0);
	volume = b2.getVolume();
	cout << "b2 �����:" << volume << endl;
	
	// ��ϵ���ŵ�����
	if (b1 < b2) {
		cout << "b2 chang" << endl;
	}
	else {
		cout << "b1 chang" << endl;
	}

	// ��ֵ���ŵ�����
	b4 = b1;
	b4.print();

	// ++ -- ���������
	Time t1(2, 45);
	Time t2(10, 59);
	++t1;
	t1.displayTime();
	++t1;
	t1.displayTime();

	t2++;
	t2.displayTime();
	t2++;
	t2.displayTime();


	// b3ʹ������ֱ��+
	b3 = b1 + b2;
	volume = b3.getVolume();
	cout << "b3 ����+���:" << volume << endl;


	system("pause");
	return 0;
}

