// ʵ�ֶѵĵ���api
#include <iostream>
using namespace std;
#pragma warning(disable:4996)

template<typename T>
class Heap 
{
public:
	Heap(size_t size)
	{
		currentSize = 0;
		//heap[0]����ʹ��
		heap = new T[capacity + 1];
		capacity = size;
	}
	~Heap()
	{
		delete[] heap;
		heap = NULL;
	}
	bool IsEmpty()
	{
		return currentSize == 0;
	}
	// ��ȡ��
	T top()
	{
		return heap[1];
	}
	void push( T const &data)
	{
		if(currentSize >= capacity)
			cout << "The Capacity Is Full!" << endl;
		else 
		{
			currentSize++;
			int currentNode = currentSize;
			while (currentNode > 1 && heap[currentNode / 2] < data)
			{
				heap[currentNode] = heap[currentNode / 2];
				currentNode = currentNode / 2;
			}
			heap[currentNode] = data;
		}
	}

	void Pop()
	{
		if(IsEmpty())
			cout << "The Heap Is Empty!" << endl;
		else 
		{
			cout << currentSize << endl;
			T last = heap[currentSize];
			currentSize--;
			int currentNode = 1;
			int child = 2;
			// ������
			while (child <= currentSize)
			{
				if (child < currentSize && heap[child] < heap[child + 1])
					child++;
				if (last >= heap[child])
					break;
				else
				{
					heap[currentNode] = heap[child];
					currentNode = child;
					child = child * 2;
				}
			}
			heap[currentNode] = last;

		}
	}

private:
	T *heap;
	int currentSize;
	int capacity;
};


int main()
{
	int c = 8,b = 10;
	c = c >> 1;
	b = (b - 1) >> 1;
	cout << c<< endl;
	cout << b << endl;

	Heap<int> h(100);
	h.push(20);
	h.push(30);
	h.push(15);
	h.push(40);
	h.push(90);
	h.push(100);
	
	cout << "�Ѷ�Ԫ��:" << h.top() << endl;
	h.Pop();
	cout << "�Ƿ�Ϊ�գ�" << h.IsEmpty() << endl;


	return 0;
}