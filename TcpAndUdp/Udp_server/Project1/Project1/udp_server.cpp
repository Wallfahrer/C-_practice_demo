//������һ����򵥵� UDP ���������� UDPServer. ������֮�󣬽�������ѭ��������
//4567 �˿ڵ����� UDP �����������־ͽ��û��������ַ�����ʽ��ӡ��������ش������¡�

#include "stdafx.h"
#pragma comment(lib, "WS2_32")

int main()
{
	system("title UDP_Server ");
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2),&wsaData);

	// �����׽���
	SOCKET sockServer = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	
	if (sockServer == INVALID_SOCKET)
	{
		printf("Failed socket()\n");
	}

	// ���sockaddr_in �ṹ
	SOCKADDR_IN addrServer;
	addrServer.sin_addr.S_un.S_addr = INADDR_ANY;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(3456);

	// ��һ���׽��ֵ�ַ
	if (SOCKET_ERROR == bind(sockServer,(SOCKADDR *)&addrServer,sizeof(SOCKADDR_IN)))
	{
		printf("Failed bin()\n");
		return 0;
	}
	// ��������
	char szRecBuff[1024] = "";
	SOCKADDR_IN addrClient;
	// SOCKET sockClient udp û�����
	int len = sizeof(SOCKADDR_IN);

	while (true)
	{
		int nRecv = recvfrom(sockServer, szRecBuff, 1024, 0, (SOCKADDR *)&addrClient, &len); //���շ����ܵ��ֽ���
		if (nRecv > 0)
		{
			szRecBuff[nRecv] = '\0';
			printf("���յ�����(%s):%s\n", inet_ntoa(addrClient.sin_addr), szRecBuff);
		}
	}

	// �ر��׽���
	closesocket(sockServer);
	WSACleanup();
	return 0;

}

