/*
	�򵥵�̰���ߣ�AIģʽ �� �ֶ�ģʽ
	���ߣ�@by Lian
	ʱ�䣺2020/2/7
	AI: ä�� -> bfs �� dfs �� Astar 
*/
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ctime>
#include <conio.h>
#include <Windows.h>

#include "FindPathBFS.h"
using namespace std;

// �����ĸ�������
int dir[4][2] = { (0,1),(0,-1),(1,0),(-1,0) };

// ���峣��
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define HEAD 0

int speed = 0;
// ���ù��λ�ӵ� x,y
void gotoXY(int x,int y)
{
	COORD c;
	c.X = x, c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

// ������ɫ windows���е�api
void SetColor(unsigned short ForeColor = 7,unsigned short BackGroundColor = 0) 
{
	// ��ȡ��ǰ���ڵ�
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	// ��ɫ
	SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);
}

// ��Ϸ�������ģ�飬�Ѻ���װ��һ�������棬��������Ϊstatic��̬��Ա��������ʵ��Ҳ����ֱ�ӵ���
class GameSetting
{
public:
	// ��Ϸ���ڵĳ���
	static const int window_height = 40;
	static const int window_width = 80;
public:
	// ��ʼ��
	static void GameInit()
	{
		// ���ô�����Ϸ��С
		char buffer[32];
		sprintf_s(buffer,"mode con cols=%d lines=%d",window_width,window_height);
		system(buffer);

		// ���ع��
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO CursorInfo; // api ���ɶ���
		GetConsoleCursorInfo(handle,&CursorInfo); // ��ȡ����̨���
		CursorInfo.bVisible = false; // ���ع��
		SetConsoleCursorInfo(handle, &CursorInfo); // ���ù����Ϣ
		// ��ʼ�����������
		srand((unsigned int)time(0));
	}
};

// ��ӡ��Ϣ�� -> ��ӭ������ ��˵���� ���� ��
class PrintInfo
{
public:
	// �ֶ�ģʽ or AIģʽ
	static void DrawChoicInfo()
	{
		gotoXY(GameSetting::window_width/2 - 10,GameSetting::window_height/2 - 5);
		cout << "��ѡ����Ϸģʽ��" << endl;
		gotoXY(GameSetting::window_width/2 - 10,GameSetting::window_height/2 - 3);
		cout << "1 ->  �ֶ�ģʽ��" << endl;
		gotoXY(GameSetting::window_width / 2 - 10, GameSetting::window_height / 2 - 1);
		cout << "2 ->AI�Զ�ģʽ��" << endl;
		gotoXY(GameSetting::window_width / 2 - 10, GameSetting::window_height / 2 + 1);
		cout << "����������ѡ��" << endl;
	}
	// ���Ƶ�ͼ
	static void DrawMap()
	{
		// �Ȱ���������
		system("cls");
		int i, j;
		for (int i = 0; i < GameSetting::window_width; i++)
			cout << "#";
		cout << endl;
		for (int i = 0; i < GameSetting::window_height - 2; i++)
		{
			for (int j = 0; j < GameSetting::window_width; j++)
			{
				if (i == 13 && j >= GameSetting::window_width - 29)
				{
					cout << "#";
					continue;
				}
				if (j == 0 || j == GameSetting::window_width - 29 || j == GameSetting::window_width - 1)
					cout << "#";
				else
					cout << " ";
			}
			cout << endl;
		}
		for (int i = 0; i < GameSetting::window_width; i++)
			cout << "#";
	}
	// ��Ϸ����ʱ��
	static void GameOver(int score)
	{
		SetColor(12,0);
		gotoXY(GameSetting::window_width/2-20,GameSetting::window_height/2 - 5);
		cout << "��Ϸ�������ݰ���!" << endl;
		gotoXY(GameSetting::window_width/2 - 20,GameSetting::window_height/2 - 3);
		cout << "�����յ÷�: "<<score << endl;
	}
	// ��������
	static void DrawScore(int score) 
	{
		gotoXY(GameSetting::window_width - 22 + 14, 6);
		cout << "  ";
		gotoXY(GameSetting::window_width - 22 + 14, 4);
		cout << "  ";

		gotoXY(GameSetting::window_width - 22, 6);
		cout << "��ǰ��ҷ���: " << score << endl;
		gotoXY(GameSetting::window_width - 22, 4);
		cout << "��ǰ��Ϸ�ٶ�: " << 10 - speed / 25 << endl;
	}
	// ������Ϸ��������
	static void DrawGameInfo(bool model)
	{
		gotoXY(GameSetting::window_width - 22, 8);

		if (model)
		{
			cout << "��ǰģʽ:" << "�˻�" << endl;
		}
		else 
		{
			cout << "��ǰģʽ:"<<"AI"<<endl;
		}
		gotoXY(GameSetting::window_width - 22 ,10);
		cout << "��ʷ���ŷ���:" << 0 << endl;

		gotoXY(GameSetting::window_width - 22,18);
		cout << "��Ϸ����˵���� " << endl;
		gotoXY(GameSetting::window_width - 22, 20);
		cout << "W:��     S:��  " << endl;
		gotoXY(GameSetting::window_width - 22, 22);
		cout << "A:��     D:��  " << endl;

		gotoXY(GameSetting::window_width - 22, 24);
		cout << "������Ϸ�ٶȣ� " << endl;
		gotoXY(GameSetting::window_width - 22, 26);
		cout << "����i :���ٶ�  " << endl;
		gotoXY(GameSetting::window_width - 22, 28);
		cout << "����o :���ٶ�  " << endl;
		gotoXY(GameSetting::window_width - 22, 30);
		cout << "E S C :  �˳�  " << endl;

		gotoXY(GameSetting::window_width - 22, 34);
		cout << "����: by@Lian  " << endl;
		gotoXY(GameSetting::window_width - 22, 36);
		cout << "�汾: 1.1.0    " << endl;

	}

};

// ʳ����
class Food
{
private:
	// ʳ������x,y
	COORDINATE m_coordinate;
public:
	// ���귶Χ
	// x: [1,GameSetting::window_width - 30]
	// y: [1,GameSetting::window_height - 2]
	void RandomXY(vector<COORDINATE> &coord) 
	{
		m_coordinate.x = rand() % (GameSetting::window_width - 30) + 1;
		m_coordinate.y = rand() % (GameSetting::window_height - 2) + 1;
		unsigned int i;
		// ������ʳ��������ߵ�λ���ϣ���������ˣ���������
		for (i = 0; i < coord.size(); i++)
		{
			// �ж�ʳ��λ���Ƿ��������ϣ�������������
			if (coord[i].x == m_coordinate.x && coord[i].y == m_coordinate.y)
			{
				m_coordinate.x = rand() % (GameSetting::window_width - 30) + 1;
				m_coordinate.y = rand() % (GameSetting::window_height - 2) + 1;
				i = 0;
			}
		}
	}
	// Ĭ�Ϲ��캯��
	Food() {}
	// ���캯�������������ʳ������
	Food(vector<COORDINATE> &coord) 
	{
		RandomXY(coord);
	}
	// ����ʳ��
	void DrawFood()
	{
		SetColor(12,0);
		gotoXY(m_coordinate.x,m_coordinate.y);
		cout << "$";
		SetColor(7,0);
	}
	
	// ʳ��ӿ�,��ȡʳ���λ��
	COORDINATE GetFoodCoordinate() 
	{
		return m_coordinate;
	}

};

// ���ࣺ�ߵ��ƶ�����ӡ����ʳ��
// ��ͼ��С width [2, width -2] height [2,height -2]
class Snake 
{
private:
	// ģʽ�ж� true �˻� false AI
	bool m_model;
	// ����
	int m_direction;
	// �Ƿ���
	bool m_is_alive;
private:
	// AI����
	bool m_chess[GameSetting::window_width - 29 +1][GameSetting::window_height];
	FindPathBFS m_AISnake;
	COORDINATE map_size;
public:
	// ������
	vector<COORDINATE> m_coordinate;

public:
	// Ĭ�Ϲ��캯�� Ĭ���˻�ģʽ
	Snake(bool model= false):m_model(model)
	{
		map_size.x = GameSetting::window_width - 29 + 1;
		map_size.y = GameSetting::window_height;
		// �ƶ�����
		m_direction = 1;
		m_is_alive = true;
		COORDINATE snake_head;
		snake_head.x = GameSetting::window_width / 2 - 15;
		snake_head.y = GameSetting::window_height / 2;

		// ����������Ϊ 3��
		this->m_coordinate.push_back(snake_head);
		snake_head.y++;
		this->m_coordinate.push_back(snake_head);
		snake_head.y++;
		this->m_coordinate.push_back(snake_head);

		// Χǽ���ϰ�
		for (int i = 0; i < GameSetting::window_width - 29 + 1; i++)
		{
			m_chess[i][0] = true;
			m_chess[i][GameSetting::window_height - 1] = true;
		}
		for (int i = 0; i < GameSetting::window_height - 1; i++)
		{
			m_chess[0][i] = true;
			m_chess[GameSetting::window_width - 29][i] = true;
		}
	}
	// ������Ϸģʽ
	void set_model(bool m)
	{
		m_model = m;
	}
	// ��ȡ��������
	void listen_key_board() 
	{
		char ch;
		// _kbhit ����������
		if (_kbhit)
		{
			ch = _getch(); // getch() -> ����int
			switch (ch) 
			{
			case 'w':
			case 'W':
				if (this->m_direction == DOWN)
					break;
				this->m_direction = UP;
				break;
			case 's':
			case 'S':
				if (this->m_direction == UP)
					break;
				this->m_direction = DOWN;
				break;
			case 'a':
			case 'A':
				if (this->m_direction == RIGHT)
					break;
				this->m_direction = LEFT;
				break;
			case 'd':
			case 'D':
				if (this->m_direction == LEFT)
					break;
				this->m_direction = RIGHT;
				break;
			case 'i':
			case 'I':
				if (speed >= 25)
					speed -= 25;
				break;
			case 'o':
			case 'O':
				if (speed < 250)
					speed += 25;
				break;
			}

		}
	}
	// AI �ٶ�
	void AI_speed()
	{
		char ch;
		if (_kbhit)
		{
			ch = _getch();
			switch (ch)
			{
			case 'i':
			case 'I':
				if (speed >= 25)
					speed -= 25;
				break;
			case 'o':
			case 'O':
				if (speed < 250)
					speed += 25;
				break;
			}
		}
	}

	// AI�Զ�Ѱ·
	void AI_find_path(Food &f)
	{
		static int not_found = 1;
		COORDINATE fpoint = f.GetFoodCoordinate();

		for (unsigned int i = 0; i < m_coordinate.size(); i++)
		{
			m_chess[m_coordinate[i].x][m_coordinate[i].y] = true;
		}
		COORDINATE begin_point, end_point;
		begin_point = m_coordinate[HEAD];
		end_point = fpoint;

		m_AISnake.InitMap((bool**)m_chess);
		m_AISnake.GetPath(begin_point,end_point);

	}
	// ����Ƿ������Լ�
	bool self_collision(COORDINATE head)
	{
		for (unsigned int i = 1; i < m_coordinate.size(); i++)
		{
			if (head.x == m_coordinate[i].x && head.y == m_coordinate[i].y)
				return true;
		}
		return false;
	}
	
	// AI�ƶ�·������
	void AI_move_snake() 
	{
		static int cot = 0;
		AI_speed();
		COORDINATE head, temp;
		if (!m_AISnake.m_paths_queue.empty())
		{
			head = m_AISnake.m_paths_queue.front();
			m_AISnake.m_paths_queue.pop();
		}
		else
		{
			// ʹ��dir����ķ���
			for (int i = 0; i < 4; i++)
			{
				int break_num = rand() % 4;
				temp = m_coordinate[HEAD];
				temp.x = temp.x + dir[i][0];
				temp.y = temp.y + dir[i][1];
				// �ж�·���Ƿ����
				if (temp.x <= 0 || temp.x >= (map_size.x - 1) ||
					temp.y <= 0 || temp.y >= (map_size.y - 1) || self_collision(temp))
				{
					continue;
				}
				head = temp;
				if (break_num == i)
					break;

			}
		}
		m_coordinate.insert(m_coordinate.begin(),head);
	}

	// �ƶ�̰����
	void move_snake()
	{
		// ��ȡ����
		listen_key_board();
		// ͷ��
		COORDINATE head = m_coordinate[0];
		// ���� �� �� �� ��
		switch (this->m_direction)
		{
		case UP:
			head.y--;
			break;
		case DOWN:
			head.y++;
			break;
		case LEFT:
			head.x--;
			break;
		case RIGHT:
			head.x++;
			break;
		}
		// ���µ�ʳ�������ƶ����µ���ͷ
		m_coordinate.insert(m_coordinate.begin(),head);
	}

	// �ж��Ƿ�Ե�ʳ��
	bool is_eat_food(Food &f)
	{
		// ��ȡʳ������
		COORDINATE food_coordinate = f.GetFoodCoordinate();
		// �Ե�ʳ��������ɣ���ɾ����β
		if (m_coordinate[HEAD].x == food_coordinate.x && m_coordinate[HEAD].y == food_coordinate.y)
		{
			f.RandomXY(m_coordinate);
			return true;
		}
		else {
			// û�Ե�ʳ�ɾ����β
			m_coordinate.erase(m_coordinate.end() - 1);
			return false;
		}
	}
	// �ж�������û��
	bool snake_is_alive() 
	{
		if (m_coordinate[HEAD].x <= 0 ||
			m_coordinate[HEAD].x >= GameSetting::window_width - 29 ||
			m_coordinate[HEAD].y <= 0 ||
			m_coordinate[HEAD].y >= GameSetting::window_height - 1)
		{
			// �����߽�
			m_is_alive = false;
			return m_is_alive;
		}

		// �Ƿ������Լ�
		for (unsigned int i = 1; i < m_coordinate.size(); i++)
		{
			if (m_coordinate[i].x == m_coordinate[HEAD].x && m_coordinate[i].y == m_coordinate[HEAD].y)
			{
				m_is_alive = false;
				return m_is_alive;
			}
		}
		m_is_alive = true;
		return m_is_alive;
	}

	// ��������
	void draw_snake()
	{
		// ������ɫ
		SetColor(10, 0);
		for (unsigned int i = 0; i < this->m_coordinate.size(); i++)
		{
			gotoXY(m_coordinate[i].x,m_coordinate[i].y);
			cout << "*";
		}
		// �ָ���ɫ
		SetColor(7, 0);
	}
	// �����Ļ�ϵ�̰����
	void ClearSnake()
	{
		for (unsigned int i = 0; i < m_coordinate.size(); i++)
		{
			m_chess[m_coordinate[i].x][m_coordinate[i].y] = false;
		}
		gotoXY(m_coordinate[this->m_coordinate.size()-1].x,m_coordinate[this->m_coordinate.size()-1].y);
		cout << " ";
	}

	// ��ȡ̰���߳���
	int GetSnakeSize()
	{
		return m_coordinate.size();
	}
	// ��ȡ��ǰ��Ϸģʽ
	bool GetModel()
	{
		return m_model;
	}
};

// ���������������������ϸ��������Դ
int main()
{
	// ʵ����
	GameSetting setting;
	PrintInfo print_info;
	Snake snake;
	// ��ʼ����Ϸ
	setting.GameInit();
	// ѡ��ģʽ
	print_info.DrawChoicInfo();
	char ch = _getch();
	switch (ch)
	{
	case '1':
		snake.set_model(true);
		speed = 50;
		break;
	case '2':
		snake.set_model(false);
		break;
	default:
		gotoXY(GameSetting::window_width/2 - 10,GameSetting::window_height/2 + 3);
		cout << " ������� ,bye!" << endl;
		cin.get();
		cin.get();
		return 0;
	}
	gotoXY(GameSetting::window_width/2 - 10,GameSetting::window_height/2 +3);
	system("pause");
	// ����ͼ
	print_info.DrawMap();
	print_info.DrawGameInfo(snake.GetModel());
	// ����ʳ��
	Food food(snake.m_coordinate);
	// ��Ϸ��ѭ��
	while (true)
	{
		// ��ӡ�ɼ�
		print_info.DrawScore(snake.GetSnakeSize());
		// ����ʳ��
		food.DrawFood();
		// ������β��ÿ�λ���ǰ����Ҫ���Ĳ���
		snake.ClearSnake();
		// �ж��Ƿ�Ե�ʳ��
		snake.is_eat_food(food);
		// �����û�ѡ��ͬģʽ -> ѡ��ͬ��ʽ
		if (snake.GetModel() == true)
		{
			snake.move_snake();
		}
		else
		{
			snake.AI_find_path(food);
			snake.AI_move_snake();
		}
		// ����
		snake.draw_snake();
		// �� �Ƿ񻹻���
		if (!snake.snake_is_alive())
		{
			print_info.GameOver(snake.GetSnakeSize());
			break;
		}
		// �����ٶ�
		Sleep(speed);
		
	}
	cin.get();
	cin.get();

	return 0;
}



