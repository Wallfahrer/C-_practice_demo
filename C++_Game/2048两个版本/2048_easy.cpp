/*
	title : 2048 �ֶ��� v1.0
	auther : @By Lian
	time : 2020/2/13
	core : ������̵�˼��
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// panel ��һ����άƽ�����
int panel[4][4];
int score = 0;

// ��ʼ��
void init()
{
	// ��������� , ��ʼ��
	srand((unsigned int)time(0));

	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 4; a++)
			panel[i][a] = 0;
	}
}

// ����
int canMoveUp()
{
	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 4; a++)
		{
			// ��һ�� ���� ��0��λ��
			if (i == 0 || panel[i][a] == 0)
			{
				continue;
			}
			// �����Ϸ��пյ� �����߿�����ϵ�
			if (panel[i - 1][a] == 0 || panel[i - 1][a] == panel[i][a])
				return 1;
		}
	}
	return 0;
}

void moveUp()
{
	// һ��һ�� һֱ�ƶ���ֱ�������ƶ�Ϊֹ
	while (canMoveUp())
	{
		for (int i = 0; i < 4; i++)
		{
			for (int a = 0; a < 4; a++)
			{
				// ��λ��
				if (i == 0 || panel[i][a] == 0)
				{
					continue;
				}
				// �Ϸ�Ϊ�յ�
				if (panel[i - 1][a] == 0)
				{
					panel[i - 1][a] = panel[i][a];
					panel[i][a] = 0;
					continue;
				}
				// ���Ժϲ�
				if(panel[i-1][a] == panel[i][a])
				{
					score += panel[i][a] * 3;
					panel[i - 1][a] = panel[i][a] * 2;
					panel[i][a] = 0;
				}
			}
		}
	}
}

// ����
int canMoveDown()
{
	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 4; a++)
		{
			// ͬ��
			if (i == 3 || panel[i][a] == 0)
			{
				continue;
			}
			if (panel[i + 1][a] == 0 || panel[i + 1][a] == panel[i][a])
				return 1;
		}
	}
	return 0;
}

void moveDown()
{
	while (canMoveDown())
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (i == 3 || panel[i][j] == 0)
				{
					continue;
				}
				if (panel[i + 1][j] == 0)
				{
					panel[i + 1][j] = panel[i][j];
					panel[i][j] = 0;
					continue;
				}
				if (panel[i + 1][j] == panel[i][j])
				{
					score += panel[i][j] * 3;
					panel[i + 1][j] = panel[i][j] * 2;
					panel[i][j] = 0;
				}

			}
		}
	}
}

// ����
int canMoveLeft()
{
	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 4; a++)
		{
			// ��һ�� ���� ��0��λ��
			if (a == 0 || panel[i][a] == 0)
			{
				continue;
			}
			// �����Ϸ��пյ� �����߿�����ϵ�
			if (panel[i][a - 1] == 0 || panel[i][a - 1] == panel[i][a])
				return 1;
		}
	}
	return 0;
}

void moveLeft()
{
	while (canMoveLeft())
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (j == 0 || panel[i][j] == 0)
				{
					continue;
				}
				if (panel[i][j-1] == 0)
				{
					panel[i][j-1] = panel[i][j];
					panel[i][j] = 0;
					continue;
				}
				if (panel[i][j-1] == panel[i][j])
				{
					score += panel[i][j] * 3;
					panel[i][j-1] = panel[i][j] * 2;
					panel[i][j] = 0;
				}

			}
		}
	}
}

// ����
int canMoveRight()
{
	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 4; a++)
		{
			// ��һ�� ���� ��0��λ��
			if (a == 3 || panel[i][a] == 0)
			{
				continue;
			}
			// �����Ϸ��пյ� �����߿�����ϵ�
			if (panel[i][a + 1] == 0 || panel[i][a + 1] == panel[i][a])
				return 1;
		}
	}
	return 0;
}

void moveRight()
{
	while (canMoveRight())
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (j == 3 || panel[i][j] == 0)
				{
					continue;
				}
				if (panel[i][j + 1] == 0)
				{
					panel[i][j + 1] = panel[i][j];
					panel[i][j] = 0;
					continue;
				}
				if (panel[i][j + 1] == panel[i][j])
				{
					score += panel[i][j] * 3;
					panel[i][j + 1] = panel[i][j] * 2;
					panel[i][j] = 0;
				}

			}
		}
	}
}

// ÿһ����������µĿ�
int spawnNewBlock()
{
	int i, a;
	int haveBlank = 0;
	for (int i = 0; i < 4; i++)
	{
		for (a = 0; a < 4; a++)
		{
			if (panel[i][a] == 0)
			{
				haveBlank += 1;
			}
		}
	}
	if (haveBlank == 0)
	{
		// û����λ������
		return 0;
	}
	do
	{
		// ������ɵ�
		i = rand() % 4;
		a = rand() % 4;
	} while (panel[i][a] != 0);
	panel[i][a] = 2;
	return 1;
}

// ��ӡ������ɫ 0 2 4 8 16 32..
void printNumber(int number)
{
	int color;
	switch (number)
	{

	case 2:
		color = 32;
		break;
	case 4:
		color = 33;
		break;
	case 8:
		color = 31;
		break;
	case 16:
		color = 34;
		break;
	case 32:
		color = 35;
		break;
	case 64:
		color = 36;
		break;
	case 128:
		color = 31;
		break;
	case 256:
		color = 32;
		break;
	case 512:
		color = 33;
		break;
	case 1024:
		color = 34;
		break;
	case 2048:
		color = 35;
		break;
	case 0:
	default:
		color = 37;
		break;
	}
	printf("\033[%d;1m %5d\033[0m", color, number);
}

// ��ӡ���
void printPanel()
{
	system("cls");
	printf("�� ǰ �� �� �� ��-v1.0 By@Lian \n");
	printf("���������� �����(W A S D) ��س�ȷ�ϲ���\n");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printNumber(panel[i][j]);
		}
		printf("\n\n");
	}
	printf("score��%d\n", score);

}

// ��ȡ��������
void play()
{
	char ch;
	int re = scanf("%c",&ch);
	if (re == 0)
	{
		printf("������������������! \n");
		play();
		return;
	}
	switch (ch)
	{
	case 'W':
	case 'w':
		moveUp();
		break;
	case 'S':
	case 's':
		moveDown();
		break;
	case 'A':
	case 'a':
		moveLeft();
		break;
	case 'D':
	case 'd':
		moveRight();
		break;
	case 'exit':
		exit(0);
	default:
		play();
		break;
	}
}

// ������ڣ�������
int main()
{
	init();
	while (spawnNewBlock())
	{
		printPanel();
		play();
	}
	printf("Sorry,Game over!\n");
	printf("���÷֣�%d\n", score);
	system("pause");
	return 0;
}
