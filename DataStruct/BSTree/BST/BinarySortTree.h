#pragma once
// �����������������������������һ�������ƽ�������

#include <iostream>
#include <stdlib.h>
using namespace std;

template<class K,class V>
struct BST_Node
{
	BST_Node(const K& key,const V& value):_key(key),_value(value),_left(nullptr),_right(nullptr) {}
	BST_Node<K, V> *_left;
	BST_Node<K, V> *_right;
	K _key;
	V _value;
};

template<class K, class V>
class BSTree
{
	typedef BST_Node<K, V> Node;
public:
	BSTree():_root(nullptr) {}
	// ����ڵ� ��Ѱ��λ�ӣ�Ȼ����룬�ٽ�����ʣ�µ���������
	bool Insert(const K& key, const V& value)
	{
		if (_root == nullptr) 
		{
			_root = new Node(key, value);
			return true;
		}
		Node* pCur = _root;
		Node* pParent = nullptr;
		while (pCur)
		{
			if (key < pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_left;
			}
			else if(key > pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_right;
			}
			else
			{
				return false;
			}
		}
		// �ҵ������λ��,Ȼ�󴴽�������Ľڵ�
		pCur = new Node(key, value);
		if (key < pParent->_key)
		{
			pParent->_left = pCur;
		}
		else if(key > pParent->_key)
		{
			pParent->_right = pCur;
		}
		return true;
	}

	// �Ƿ�ɾ���˶�ӦֵΪkey�Ľڵ�
	bool Remove(const K& key)
	{
		if (_root == nullptr)
			return false;
		if (_root->_left == nullptr && _root->_right == nullptr)
		{
			delete _root;
			_root = nullptr;
			return true;
		}
		// ��ʼ��ɾ����λ��
		Node* pCur = _root;
		Node* pParent = nullptr;
		while (pCur)
		{
			if (key < pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_left;
			}
			else if(key > pCur->_key)
			{
				pParent = pCur;
				pCur = pCur->_right;
			}
			else
			{
				break;
			}
		}
		// pParent �Ѿ������ˣ�λ�ýڵ����Ϣ
		if (pCur == nullptr)
		{
			return false;
		}
		// ���� ɾ����û����ڵ㣬 ����û���ҽڵ㣬 ���߶����ڡ�
		if (pCur->_left == nullptr)
		{
			// �ж��Ƿ�Ϊ���ڵ�
			if (pCur->_key == key)
			{
				_root = pCur->_right;
				delete pCur;
				pCur = nullptr;
				return true;
			}
			else if (pParent->_left == pCur)
			{
				// ˫�׵���ڵ�
				pParent->_left = pCur->_right;
			}
			else
			{
				// ˫�׵��ҽڵ�
				pParent->_right = pCur->_right;
			}
		}
		else if (pCur->_right == nullptr)
		{
			if (pCur->_key == key)
			{
				_root = pCur->_left;
				delete pCur;
				pCur = nullptr;
				return true;
			}
			else if (pParent->_right == pCur)
			{
				pParent->_right = pCur->_left;
			}
			else
			{
				pParent->_left = pCur->_left;
			}
		}
		else
		{
			// ���Ҷ����ڵ�ʱ��
			Node* sub = pCur;
			Node* First = pCur->_right;
			if (First->_left)
			{
				sub = First;
				First = First->_left;
			}
			swap(pCur->_key,First->_key);
			swap(pCur->_value,First->_value);
			pCur = First;
			if (pCur->_left == nullptr)
			{
				if (sub->_left == pCur)
				{
					sub->_left = pCur->_right;
				}
				else
				{
					sub->_right = pCur->_right;
				}
			}
			else if(pCur->_right == nullptr)
			{
				if (sub->_left == pCur)
				{
					sub->_left = pCur->_left;
				}
				else
				{
					sub->_right = pCur->_left;
				}
			}
		}
		delete pCur;
		pCur = nullptr;
		return true;
	}
	// Ѱ�ҽڵ�
	Node* Find(const K& key)
	{
		if (_root == nullptr) return nullptr;
		Node* pCur = _root;
		while (pCur)
		{
			if (key < pCur->_key)
			{
				pCur = pCur->_left;
			}
			else if (key > pCur->_key)
			{
				pCur = pCur->_right;
			}
			else
			{
				break;
			}
		}
		return pCur;
	}

	// �����ұ�
	void Insert_R(const K &key,const V &value)
	{
		if (_Insert_R(_root, key, value))
		{
			cout << "����ɹ� :" << key << endl;
		}
		else
		{
			cout << "����ʧ��" << endl;
		}
	}
	// ɾ��
	void Remove_R(const K &key)
	{
		if (_Remove_R(_root,key))
		{
			cout << "successed del node key is:"<<key << endl;
		}
		else
		{
			cout << "failed del!" << endl;
		}
	}
	// ǰ���У��������ӡ
	void PreOrder()
	{
		cout << "PreOrder��";
		_PreOrder(_root);
		cout << endl;
	}
	void MidOrder()
	{
		cout << "MidOrder��";
		_MidOrder(_root);
		cout << endl;
	}
	void PostOrder()
	{
		cout << "PostOrder��";
		_PostOrder(_root);
		cout << endl;
	}
	void Height()
	{
		cout << "height��" << _Height(_root)-1<< endl;
	}

protected:
	// ˽�к��� *& ���޸ĵ�root
	bool _Insert_R(Node*& root, const K& key,const V &value )
	{
		if (root == nullptr)
		{
			root = new Node(key, value);
			return true;
		}
		if (key < root->_key)
		{
			return _Insert_R(root->_left, key, value);
		}
		else if(key > root->_key)
		{
			return _Insert_R(root->_right, key, value);
		}
		else
		{
			return false;
		}
	}

	bool _Remove_R(Node*& root, const K& key)
	{
		if (root == nullptr) return false;
		if (key > root->_key)
			return _Remove_R(root->_right, key);
		else if (key < root->_key)
			return _Remove_R(root->_left, key);
		// �ҵ���
		else
		{
			Node *pCur = root;
			if (root->_left == nullptr)
				root = root->_right;
			else if (root->_right == nullptr)
				root = root->_left;
			else
			{
				Node *tmp = root->_right;
				while (tmp->_left)
				{
					tmp = tmp->_left;
				}
				swap(pCur->_key, tmp->_key);
				swap(pCur->_value, tmp->_value);
				return _Remove_R(root->_right, key);
			}
			delete pCur;
			pCur = nullptr;
			return true; 
		}
	}

	void _PreOrder(Node* root)
	{
		if (root == nullptr)
			return ;
		cout << root->_key << " ";
		_PreOrder(root->_left);
		_PreOrder(root->_right);
		
	}

	void _MidOrder(Node* root)
	{
		if (root == nullptr)
			return ;
		if (root)
		{
			_MidOrder(root->_left);
			cout << root->_key << " ";
			_MidOrder(root->_right);
		}
	}

	void _PostOrder(Node* root)
	{
		if (root == nullptr)
			return ;
		_PostOrder(root->_left);
		_PostOrder(root->_right);
		cout << root->_key << " ";
		
	}

	int _Height(Node* root)
	{
		if (root == nullptr) return 0;
		if (root->_left == nullptr && root->_right == nullptr) return 1;
		int left = _Height(root->_left);
		int right = _Height(root->_right);
		return left > right ? left + 1 : right + 1;
	}

protected:
	// ��Ա����
	Node *_root;
};



