#include <iostream>
#include <string.h>
using namespace std;
#include "ShallowReplication.h"
#include "DeepReplication.h"

// ��ǳ������main ����
// ǳ���������ڴ�й©



int main()
{
	// ǳ����
	ShallowRep sRep("best");
	ShallowRep sRep2(sRep);
	sRep2.show();

	// ���
	/*C_DeepRep cDrep("ljw");
	cDrep.show();
	C_DeepRep cDrep2(cDrep);
	cDrep2.show();
	cout << "-----" << endl;
	cDrep2.setName("pop");
	cDrep2.show();*/

	system("pause");
	return 0;
}

