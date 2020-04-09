#pragma once

// ����˫����
// ͬʱ���������ϵĲ���

struct NODE
{
	char m_szName[20];
	int m_Age;
	char m_szSex[4];
	char m_szAddr[100];
	char m_szTel[20];

	// ����next �� prior
	NODE *m_next;
	NODE *m_prior;
};

// ��������
// ����һ���մ����õĿհ׽ڵ�
void MyInputNode(NODE& pt);

// ����ڵ�
void MyOutputNode(NODE& pt);

// ��������
void MyCreateList();

// ����һ���ڵ�
NODE& MyAdd_Node();
// ����β�����һ���ڵ�
NODE* MyAddNode();
void MyShowList();
// FINDNODE + SHOWNODE
void MyShowNode();
NODE& MyFindNode(char *FindName);
// ǰ�壬���ڲ�ѯ�ڵ�֮ǰ
void MyInsertFront(char* ptName, NODE* pResFindNode, NODE* pNew);
// ��壬���ڲ�ѯ�ڵ�֮��
void MyInsertNext(char* pName, NODE* pResFindNode, NODE* pNew);
void MyInsertNode();
void MyModifyNode();
void MyDeleteNode();
void MyClearnList();
void MyHelp();


