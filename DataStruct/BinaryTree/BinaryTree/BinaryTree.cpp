// �������Ķ���

#include <iostream>
#include <string>
using namespace std;

// ���ӱ�ʾ�� -> �൱����������ʾ
template<typename T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T &value) :_value(value), _pleft(nullptr), _pright(nullptr) {};
	T _value;
	BinaryTreeNode<T> *_pleft;
	BinaryTreeNode<T> *_pright;
};

template<typename T>
class BinaryTree
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree() :_root(nullptr)
	{}
	// �вι���һ����
	BinaryTree(const T arr[],size_t size,const T& invalid)
	{
		size_t index = 0;
		_CreateBinaryTree(_root,arr,size,index,invalid);
	}
	// ����
	BinaryTree<T> & operator=(const BinaryTree<T>&bt)
	{
		if (this != &bt)
		{
			_DestroyBinaryTree(_root);
		}
		return *this;
	}
	// �ͷ��ڴ�
	~BinaryTree()
	{
		_DestroyBinaryTree(_root);
	}
	// ����
	void Preorder()
	{

		_Preorder(_root);
	}
	void Midorder()
	{
		cout << "Midorder:";
		_Midorder(_root);
		cout << endl;
	}


	int Find(const T& value)
	{
		return _Find(_root,value);
	}

private:
	void _CreateBinaryTree(Node *&_proot,const T arr[], size_t size,size_t &index,const T& invalid)
	{
		// ע���������жϴ���
		if (index < size && invalid != arr[index])
		{
			// �������ڵ�
			auto _proot = new Node(arr[index]);
			// �ݹ鴴��������
			_CreateBinaryTree(_proot->_pleft, arr, size, ++index, invalid);
			// ������
			_CreateBinaryTree(_proot->_pright, arr, size, ++index, invalid);
		}
	}
	void _DestroyBinaryTree(Node *&root) 
	{
		if (root)
		{
			_DestroyBinaryTree(root->_pleft);
			_DestroyBinaryTree(root->_pright);
			delete root;
			root = nullptr;
		}
	}

	void _Preorder(Node* root)
	{
		if (root)
		{
			cout << root->_value << " ";
			_Preorder(root->_pleft);
			_Preorder(root->_pright);
		}
	}
	void _Midorder(Node *root)
	{
		if (root)
		{
			_Midorder(root->_pleft);
			cout << root->_value << " ";
			_Midorder(root->_pright);
		}
	}

	int _Find(Node *root,const T& value)
	{
		if (root)
		{
			if (root->_value == value) return 1;
			else
			{
				_Find(root->_pleft, value);
				_Find(root->_pright, value);
			}
		}
		return -1;
	}

private:
	// ���ڵ�
	Node* _root;
};

int main()
{	//{'1','2','4','#','#','#','3','5','#','#','6'}
	char ptr[12] = { '1','2','4','#','#','#','3','5','#','#','6', '\0' };
	BinaryTree<char> bt(ptr, strlen(ptr), '#');
	//BinaryTree<char> bt1(bt);
	bt.Midorder();
	cout << bt.Find('1') << endl;

	//cout << bt1.Find(2) << endl;
	BinaryTree<char> bt2;
	bt2 = bt;
	bt2.Preorder();

	return 0;
}




