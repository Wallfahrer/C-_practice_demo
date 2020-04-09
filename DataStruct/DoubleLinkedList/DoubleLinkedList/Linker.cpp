// ʵ��Linker.h �������ĺ�������
#include "stdafx.h"
#include "Linker.h"

// �����������ܽڵ� head,end
NODE *g_head = NULL;
NODE *g_end = NULL;

void MyInputNode(NODE& pt)
{
	pt.m_next = NULL;
	pt.m_next = NULL;
	cout << "����:";      cin >> pt.m_szName;
	cout << "����:";      cin >> pt.m_Age;
	cout << "�Ա�:";      cin >> pt.m_szSex;
	cout << "��ϵ��ʽ:";   cin >> pt.m_szTel;
	cout << "סַ:";      cin >> pt.m_szAddr;

}

void MyOutputNode(NODE& pt)
{
	cout << "������" << pt.m_szName << endl;
	cout << "���䣺" << pt.m_Age << endl;
	cout << "�Ա�: " << pt.m_szSex << endl;
	cout << "�绰: " << pt.m_szTel << endl;
	cout << "סַ: " << pt.m_szAddr << endl<<endl;
}

void MyCreateList()
{
	NODE *Temp = new NODE;
	if (Temp == NULL)
	{
		cout << "����ʧ�ܣ�" << endl;
	}
	else
	{
		MyInputNode(*Temp);
		cout << "��������ɹ���" << endl << endl;
	}
	g_head = Temp;
	g_end = Temp;
}

// ��������һ���ڵ�
NODE& MyAdd_Node()
{
	NODE* pTemp = new NODE;

	if (NULL != pTemp)
	{
		MyInputNode(*pTemp);
	}

	return *pTemp;
}

NODE* MyAddNode()
{
	if (g_head == NULL || g_end == NULL)
	{
		cout << "���������ڣ������´������ٲ�����" << endl;
	}
	NODE *pNew = &MyAdd_Node(); // ����ʹ��
	g_end->m_next = pNew;
	pNew->m_prior = g_end;
	g_end = pNew;
	return NULL;
}

void MyShowList()
{
	int nCount = 1;
	if (g_head != NULL && g_end != NULL)
	{
		NODE* pt = g_head;
		cout << "<--------------��ӡ����-------------->" << endl;
		while (pt != NULL)
		{
			cout<<"��"<<nCount<<"���ڵ�"<<endl;
			MyOutputNode(*pt);
			pt = pt->m_next;
			nCount++;
		}
		cout << "<--------------��ӡ����-------------->" << endl << endl;
	}
}

NODE& MyFindNode(char *FindName)
{
	// ������������
	NODE * pt = g_head;
	while (true)
	{
		if (pt != NULL)
		{
			if (strcmp(pt->m_szName,FindName)==0)
			{
				return *pt;
			}
			else
			{
				pt = pt->m_next;
			}

		}
		else
		{
			cout << "��ѯ�ڵ㲻����!" <<endl <<endl;
			return *pt;
		}
	}
}

void MyShowNode()
{
	char szNameBuf[20] = "";
	cout << "�������������:";
	cin >> szNameBuf;
	MyOutputNode(MyFindNode(szNameBuf));
}

void MyInsertFront(char* ptName, NODE* pResFindNode, NODE* pNew)
{	
	// ǰ��
	if (pResFindNode == g_head)
	{
		pNew->m_next = g_head;
		g_head->m_prior = pNew;
		g_head = pNew;
	}
	else  
	{
		pNew->m_prior = pResFindNode->m_prior;
		pNew->m_next = pResFindNode;
		pResFindNode->m_prior->m_next = pNew;
		pResFindNode->m_prior = pNew;
	}
}

void MyInsertNext(char* pName, NODE* pResFindNode, NODE* pNew)
{
	// ���
	if (pResFindNode == g_end)
	{
		pResFindNode->m_next = pNew;
		pNew->m_prior = pResFindNode;
		g_end = pNew;
	}
	else
	{
		pNew->m_next = pResFindNode->m_next;
		pResFindNode->m_next->m_prior = pNew;
		pNew->m_prior = pResFindNode;
		pResFindNode->m_next = pNew;
	}
}

void MyInsertNode()
{
	// ����ط��߼�����BUG Ӧ�����ж�����������Ƿ���������..Ȼ����ִ�в���
	char szNameBuf[20] = "";
	cout << "���������� :";
	cin >> szNameBuf;
	NODE *pNew = &MyAdd_Node();
	NODE *pResFindNode = &MyFindNode(szNameBuf);

	cout << "-------------���������ʼ-------------" << endl;
	int Chose = 1;
	cout << "1 - - - ����ڵ�ǰ�� 2 - - - ����ڵ��(Ĭ���ǽڵ�ǰ) ";
	cin >> Chose;
	if (Chose == 1)
	{
		MyInsertFront(szNameBuf,pResFindNode,pNew);
	}
	else if(Chose == 2)
	{
		MyInsertNext(szNameBuf, pResFindNode, pNew);
	}
	else
	{
		cout << "������1����2��������ٴγ������룡" << endl;
	}
	cout << "-------------����������-------------" << endl << endl;
}

void MyModifyNode()
{
	char szNameBuf[20] = "";
	cout << "�����뽫Ҫ�޸ĵ��û�������";
	cin >> szNameBuf;
	cout << "-------------�޸Ĳ�����ʼ-------------" << endl;
	NODE *pResFindNode = &MyFindNode(szNameBuf);
	MyInputNode(*pResFindNode);
	cout << "-------------�޸Ĳ�������-------------" << endl << endl;
}

void MyDeleteNode()
{
	char szNameBuf[20] = "";
	cout << "������Ҫɾ�����û�����:";
	cin >> szNameBuf;

	cout << "-------------ɾ������������-------------" << endl;
	NODE *pResFindNode = &MyFindNode(szNameBuf);
	if (pResFindNode == g_head)
	{
		g_head = pResFindNode->m_next;
		pResFindNode->m_next->m_prior = NULL;
	}
	else if (pResFindNode == g_end)
	{
		g_end = pResFindNode->m_prior;
		g_end->m_next = NULL;
	}
	else
	{
		pResFindNode->m_prior->m_next = pResFindNode->m_next;

	}
	// �ͷ��ڴ�
	delete []pResFindNode;
	cout << "-------------ɾ����������-------------" << endl << endl;

}

void MyClearnList()
{
	NODE *pt = g_head;
	cout << "-------------������������-------------" << endl;
	while (pt != NULL)
	{
		delete []pt;
		pt = pt->m_next;
	}
	g_head = NULL;
	g_end = NULL;
	cout << "-------------����������-------------" << endl << endl;
}

void MyHelp()
{
	for (size_t i = 0; i < 80; i++)
		putchar('=');
	cout << endl;

	void Create();
	void Add();
	void Insert();
	void Delete();
	void Clearn();
	void Modify();
	void Find();
	void Show();
	void Help();
	void Exit();
	cout << "����           ���         ��������    " << endl;
	cout << "Create         ����         ����һ������" << endl;
	cout << "Add            ���         �ڸ������β�����һ���µĽڵ�" << endl;
	cout << "Insert         ����         ����������ط��������һ���½ڵ�" << endl;
	cout << "Delete         ɾ��         ����������ط�����ɾ��һ�����нڵ�" << endl;
	cout << "Clearn         ���         �����������" << endl;
	cout << "Modify         �޸�         ����������ط��������޸�һ�����нڵ�" << endl;
	cout << "Show           ��ʾ         ��������ʾ����������нڵ����ϸ��Ϣ" << endl;
	cout << "Help           ����         �鿴����˵���ĵ�" << endl;
	cout << "Exit           �˳�         �˳�������������" << endl;


	for (size_t i = 0; i < 80; i++)
		putchar('=');

	cout << endl << endl;
}


