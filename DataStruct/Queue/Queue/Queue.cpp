/*
	auther:@Bylian
	time:2019/4/5
	�ṹ�� ʵ��һ������
*/ 
#include <iostream>
using namespace std;

template<class T>
struct Node
{
	// �ı��ⲿʵ�ε�ֵ��������
	Node(T &t)
	{
		data = t;
		next = NULL;
	}
	int data;
	Node *next;
};

template<typename T>
class Queue
{
public:
	Queue(T &n)
	{
		Node<T> *p = new Node<T>(n);
		length = 0;
		front = rear = p;
	}
	int QueueLength()
	{
		return length;
	}
	bool empty()
	{
		return length == 0;
	}
	void Push(T n)
	{
		Node<T> *p = new Node<T>(n);
		rear->next = p;
		rear = p;
		length++;
	}
	bool CanPop()
	{
		if (front == rear)
			return false;
		Node<T> *t = front->next;
		front->next = t->next;
		if (front->next == nullptr)
			rear = front;
		delete t;
		length--;
		return true;
	}

	void PrintQueue()
	{
		Node<T> *t = front->next;
		cout << "��������" << endl;
		while (t)
		{
			cout << t->data << " ";
			t = t->next;
		}
		cout << endl;
	}

private:
	int length;
	Node<T> *front;
	Node<T> *rear;
};


int main()
{
	int head = 0;
	Queue<int> *q = new Queue<int>(head);
	cout << q->CanPop() << endl;
	cout << q->QueueLength() << endl;
	q->Push(1);
	q->Push(25);
	q->Push(32);
	q->Push(40);
	q->PrintQueue();
	cout << q->CanPop() << endl;

	float head2 = 0;
	Queue<float> *q2 = new Queue<float>(head2);
	cout << q2->CanPop() << endl;
	q2->Push(1.0);
	q2->Push(2.5);
	q2->PrintQueue();
	
	return 0;
}




