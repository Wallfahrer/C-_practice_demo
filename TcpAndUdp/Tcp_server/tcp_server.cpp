// Tcp �����
#include "stdafx.h"
#pragma comment(lib, "WS2_32")

int main()
{
	system("title: TCP ������");

	// ���Э���Ƿ����
	WSADATA wsaData;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("error:  WSAStartup() faile...\n");
		return -1;
	}
	printf("�������Ѿ�����...\n");

	// �����������˿��׽���
	SOCKET SockSever = socket(AF_INET,SOCK_STREAM,0);

	// ��������˵�ַ
	SOCKADDR_IN addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrServer.sin_port = htons(2000);

	// ���׽���
	if (SOCKET_ERROR == bind(SockSever,(SOCKADDR *)&addrServer,sizeof(SOCKADDR)))
	{
		printf("error: bind() fail...%d\n",WSAGetLastError());
		return -1;
	}

	// ����
	if (SOCKET_ERROR == listen(SockSever,5))
	{
		printf("error: listen() faile ...%d\n",WSAGetLastError());
		return -1;
	}
	printf("������������...\n");

	// ��ʼ���ͻ���ַ���Ȳ���
	int len = sizeof(SOCKADDR);
	SOCKADDR_IN addrClient;
	char szSendBuf[2048] = "�Ѿ����ӷ������ɹ�";
	char szRecvBuf[2048] = "";

	// �ȴ��ͻ��������󣬽�����������
	SOCKET sockAccept = accept(SockSever,(SOCKADDR *)&addrClient,&len);
	if (INVALID_SOCKET == sockAccept)
	{
		printf("error:  accept() faile...:%d\n", WSAGetLastError());
		return -1;
	}
	// ������ӳɹ��Ŀͻ���IP�Ͷ˿ں�
	printf("Aeccpt client IP:[%s], port[%d]\n",inet_ntoa(addrClient.sin_addr),ntohs(addrClient.sin_port));

	// ��ѭ������
	while (true)
	{
		recv(sockAccept,szRecvBuf,sizeof(szRecvBuf),0);
		printf("�ͻ���:%s \n",szRecvBuf);
	}

	// �ر��׽��֣��ر�Э��
	closesocket(SockSever);
	WSACleanup();
	return 0;
}

