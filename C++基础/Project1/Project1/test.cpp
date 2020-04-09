// ��Ҫ����д�㷨��C++С���Ե���Ŀ
// 2020/2/16  - > ������  ->  Ͱ����  -> �鲢���� -> ��������
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

// ������ 1 ��������/С������ 2 ������
void max_heapify(int arr[], int start, int end) {
	//���������cָ�˺��ӹ��cָ��
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { //���ӹ��cָ���ڹ����Ȳ������^
		if (son + 1 <= end && arr[son] < arr[son + 1]) //�ȱ��^�ɂ��ӹ��c��С���x������
			son++;
		if (arr[dad] > arr[son]) //��������c����ӹ��c�����{���ꮅ��ֱ����������
			return;
		else { //��t���Q���Ӄ������^�m�ӹ��c�͌O���c���^
			swap(arr[dad], arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void heap_sort(int arr[], int len) {
	//��ʼ����i������һ�������c�_ʼ�{��
	for (int i = len / 2 - 1; i >= 0; i--)
		max_heapify(arr, i, len - 1);
	//�Ȍ���һ��Ԫ�غ��Ѿ��źõ�Ԫ��ǰһλ�����Q���ُ����{��(�յ�����Ԫ��֮ǰ��Ԫ��)��ֱ�������ꮅ
	for (int i = len - 1; i > 0; i--) {
		swap(arr[0], arr[i]);
		max_heapify(arr, 0, i - 1);
	}


}

// Ͱ����

// ��������
void CountSort(vector<int>& vecRaw, vector<int>& vecObj)
{
	// ȷ�������������ǿ�
	if (vecRaw.size() == 0)
		return;

	// ʹ�� vecRaw �����ֵ + 1 ��Ϊ�������� countVec �Ĵ�С
	int vecCountLength = (*max_element(begin(vecRaw), end(vecRaw))) + 1;
	vector<int> vecCount(vecCountLength, 0);

	// ͳ��ÿ����ֵ���ֵĴ���
	for (int i = 0; i < vecRaw.size(); i++)
		vecCount[vecRaw[i]]++;

	// ����ļ�ֵ���ֵ�λ��Ϊǰ�����м�ֵ���ֵĴ���֮��
	for (int i = 1; i < vecCountLength; i++)
		vecCount[i] += vecCount[i - 1];

	// ����ֵ�ŵ�Ŀ��λ��
	for (int i = vecRaw.size(); i > 0; i--)	// �˴�������Ϊ�˱�����ͬ��ֵ���ȶ���
		vecObj[--vecCount[vecRaw[i - 1]]] = vecRaw[i - 1];
}

// ������� ���ƶ��ֲ���
/*int InsertSearch(int* a,int value,int low,int high) 
{
	int mid =low+(value - a[low])/(a[high] - a[low])*(high - low) ;
	if (a[mid] == value)
		return mid;
	if (a[mid] > value)
		return InsertSearch(a,value,low,mid-1);
	if(a[mid] < value)
		return InsertSearch(a, value, mid + 1, high);
}*/

// ������
int Propotion(int *A,int low,int high) 
{
	int p = A[low];
	while (low < high) 
	{
		while (low < high && A[high] >= p)
			high--;
		A[low] = A[high];
		while (low < high && A[low] <= p)
			low++;
		A[high] = A[low];
	}
	A[low] = p;
	return low;
}

void QuickSort(int *A,int low,int high)
{
	if (low < high)
	{
		int p = Propotion(A, low, high);
		QuickSort(A, low, p - 1);
		QuickSort(A, p + 1, high);
	}

}


int main()
{
	// ������
	int arr[] = { 3, 5, 3, 0, 8, 5, 9, 7, 4, 0, 2, 6 };
	int len = (int)sizeof(arr) / sizeof(*arr);
	/*for (int i = 0; i < len; i++)
		cout << arr[i] << " ";
	cout << endl;
	heap_sort(arr, len);
	for (int i = 0; i < len; i++)
		cout << arr[i] << " ";
	cout << endl;
	heap_sort(arr,len);*/
	
	// ��������
	/*vector<int> vecRaw = { 0,5,7,9,6,3,4,5,2,8,6,9,2,1 };
	vector<int> vecObj(vecRaw.size(), 0);
	for (int i = 0; i < vecObj.size(); ++i)
		cout << vecRaw[i] << "  ";
	cout << endl;
	CountSort(vecRaw, vecObj);
	for (int i = 0; i < vecObj.size(); ++i)
		cout << vecObj[i] << "  ";
	cout << endl;*/

	// ������
	QuickSort(arr, 0, len - 1);
	for (int i = 0; i < len; i++)
		cout << arr[i] << " ";
	cout << endl;

	return 0;
}


