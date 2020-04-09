#include "stdafx.h"
#include "Linker.h"
#include "Cmd.h"

void Create()
{
	MyCreateList();
}

void Add()
{
	MyAddNode();
}

void Insert()
{
	MyInsertNode();
}

void Delete()
{
	MyDeleteNode();
}

void Clearn()
{
	MyClearnList();
}

void Modify()
{
	MyModifyNode();
}

void Find()
{
	MyShowNode();
}
void Show()
{
	MyShowList();
}
void Help()
{
	MyHelp();
}

void Exit()
{
	exit(0);
}

// ����һ�� Map ӳ��
CMD_MAP g_Cmd_Map[] = {
					{"Create", Create},
					{"Add", Add},
					{"Insert", Insert},
					{"Delete", Delete},
					{"Clearn", Clearn},
					{"Modify", Modify},
					{"Find", Find},
					{"Show", Show},
					{"Help", Help},
					{"Exit", Exit},
					{"NULL", NULL}
};

void Finally()
{
	system("title ˫������ easy_system - v1.1.0");
	system("color 0e");

	// ֱ���ṩ�����˵�
	Help();
	char szCmdBuf[20] = "";
	CMD_MAP *pCmdMap = NULL;
	
	while (true)
	{
		pCmdMap = g_Cmd_Map;
		cout << endl << "����������:";
		cin >> szCmdBuf;
		while (true)
		{
			system("cls");
			if (0 == strcmp(szCmdBuf, pCmdMap->m_szcmd))
			{
				pCmdMap->m_pfun();
				break;
			}

			if ("NULL" == pCmdMap->m_szcmd)
			{
				cout << "�����������������������룡" << endl;
				break;
			}

			pCmdMap++;
		}

	}

}

