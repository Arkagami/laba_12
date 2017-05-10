#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>   // Needed for _wtoi

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

SOCKET Socket, Sub; //������ ������� � ������������� ������� 
WSADATA Winsock;
sockaddr_in Addr; //��������� ��� ������ ip-������ ������� 
int Addrlen = sizeof(sockaddr_in);
char Buffer[256];
char *Str;
char request[1001];
sockaddr_in IncomingAddress; //��������� ��� ������ ip-������ ������� 
int AddressLen = sizeof(IncomingAddress);

int main()
{

	// ��������� ���������� WinSock2 
	WSAStartup(MAKEWORD(2, 2), &Winsock);

	if (LOBYTE(Winsock.wVersion) != 2 || HIBYTE(Winsock.wVersion) != 2) // Check version 
	{
		WSACleanup();
		return 0;
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	ZeroMemory(&Addr, sizeof(Addr)); //�������� ip-����� �������
	Addr.sin_family = AF_INET; //�������� ipv4 
	Addr.sin_port = htons(80); // � ������� - ������� ����, �� ������� ������ ������� ���������� 
	bind(Socket, (sockaddr*)&Addr, sizeof(Addr));


	while (1) {
		if (listen(Socket, 1) == SOCKET_ERROR)
		{
			//���� �� 
			printf("listening error\n");
		}
		else
		{
			printf("listening ok\n");
		}
		if (Sub = accept(Socket, (sockaddr*)&IncomingAddress, &AddressLen)) //���� �������� ���������� 
		{
			// ���������� ������������ 
			char *ClientIP = inet_ntoa(IncomingAddress.sin_addr);
			int ClientPort = ntohs(IncomingAddress.sin_port);
			printf("Client connected!\n");
			printf("IP: %s:%d\n", ClientIP, ClientPort);
			printf("Input name of file:");
			scanf(" %s", &request);
				send(Sub, request, 1000, MSG_OOB);

		}
	}

	closesocket(Sub);
	closesocket(Socket);
	WSACleanup();

	getchar();
	return 0;
}