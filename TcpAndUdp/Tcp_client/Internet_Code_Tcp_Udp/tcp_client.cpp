// Tcp Ӧ�ó������

#include "stdafx.h"
#pragma comment(lib, "WS2_32")

int main()
{
	system("title Tcp�ͻ���");

	// ���Э���Ƿ��ʹ��
	WSADATA wasData;
	if (WSAStartup(MAKEWORD(2,2),&wasData))
	{
		printf("error : WSAStartup() false...\n");
		return -1;
	}

	// �����ͻ����׽���
	SOCKET socketClient = socket(AF_INET,SOCK_STREAM,0);
	if (INVALID_SOCKET == socketClient)
	{
		printf("error: socket() false ...%d \n",WSAGetLastError());
		return -1;
	}

	SOCKADDR_IN addServer;
	addServer.sin_family = AF_INET;
	char szInIp[30] = "";
	printf("������Է���IP��ַ��ͬ��������:eg:127.0.0.1\n");
	scanf("%s", szInIp);
	addServer.sin_addr.S_un.S_addr = inet_addr(szInIp);
	addServer.sin_port = htons(2000);

	// ���������������TCP����
	if (INVALID_SOCKET == connect(socketClient,(SOCKADDR *)&addServer,sizeof(SOCKADDR)))
	{
		printf("error: connect() false ...%d \n",WSAGetLastError());
		return -1;
	}

	char szRecvBuff[2048] = "";
	char szSendBuff[2048] = "�ͻ����Ѿ����ӳɹ�";

	while (true)
	{
		printf(">>");
		scanf("%s",szSendBuff);
		send(socketClient,szSendBuff,strlen(szSendBuff)+1,0);
		// recv(socketClient, szRecvBuff, sizeof(szRecvBuff), 0);
		// printf("�ͻ��ˣ�%s \n",szRecvBuff);
	}

	// �ر�
	closesocket(socketClient);
	WSACleanup();

	return 0;
}

