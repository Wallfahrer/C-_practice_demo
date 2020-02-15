#pragma once
#include<queue>
using std::queue;

typedef struct {
	int x;
	int y;
}COORDINATE;

class FindPathBFS
{
private:
	// �þ�������ʾһ��ͼ��m_chess��ά���飬false��ʾͨ·��true��ʾ��ͨ
	bool **m_chess; 
	// ����ڵ㿴�Ƿ��߹�
	bool **m_visit; 
	// ÿ�����ʹ��Ľڵ�ĸ��ڵ�
	COORDINATE **m_parent;
	// ��ͼ��С
	COORDINATE m_size;
	void FindPath(COORDINATE begin_point,COORDINATE end_point);
	void GetQueue(COORDINATE end_point);
public:
	// ���� ���� 
	FindPathBFS();
	~FindPathBFS();
	void InitMap(bool **chess);
	void GetPath(COORDINATE begin_point, COORDINATE end_point);
	queue<COORDINATE> m_paths_queue;
};




