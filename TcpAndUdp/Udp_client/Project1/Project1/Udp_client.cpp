// Udp��client��

#include "stdafx.h"
#pragma comment(lib,"WS2_32")


int main()
{
	system("title UDP_Client ");
	// ��ʼ��winsock��
	WSADATA wasData;
	WSAStartup(MAKEWORD(2,2), &wasData);

	// ����udp socket�׽���
	SOCKET sockClient = socket(AF_INET,SOCK_DGRAM, IPPROTO_UDP);

	// Ҳ���Ժ�tcpһ��ʹ��bind������һ�����ص�ַ
	// ����ϵͳҲ���Զ����ŵ�

	// ��дԶ�̵�ַ
	SOCKADDR_IN addrClient;
	//char szbuff[20] = "127.0.0.1";
	char szbuff[20] = "";
	printf("��ǰIP��ַ ��%s",szbuff);
	scanf("%s",szbuff);
	addrClient.sin_addr.S_un.S_addr = inet_addr(szbuff);
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(3456);

	// ������д������IP��ַ����������û��������ֱ��ʹ��127.0.0.1����
	// ��������
	char szSendBuff[1024] = "";
	while (true)
	{
		printf(">>");
		scanf("%s", szSendBuff);
		sendto(sockClient,szSendBuff,strlen(szSendBuff)+1, 0,(SOCKADDR *)&addrClient,sizeof(SOCKADDR_IN));
	}
	closesocket(sockClient);
	WSACleanup();

	return 0;

}
