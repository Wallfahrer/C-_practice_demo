#pragma once
// Cmd ������ȥ����Linker.h 
// ��Ҫ����һЩhelp�������õķ���

typedef void(*pfun)();

struct CMD_MAP
{
	const char *m_szcmd;
	pfun m_pfun;
};

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

void Finally();





