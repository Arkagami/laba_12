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

SOCKET Socket, Sub; //сокеты сервера и подключенного клиента 
WSADATA Winsock;
sockaddr_in Addr; //структура для записи ip-адреса сервера 
int Addrlen = sizeof(sockaddr_in);
char Buffer[256];
char *Str;
char request[1001];
sockaddr_in IncomingAddress; //структура для записи ip-адреса клиента 
int AddressLen = sizeof(IncomingAddress);

int main()
{

	// запускаем библиотеку WinSock2 
	WSAStartup(MAKEWORD(2, 2), &Winsock);

	if (LOBYTE(Winsock.wVersion) != 2 || HIBYTE(Winsock.wVersion) != 2) // Check version 
	{
		WSACleanup();
		return 0;
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	ZeroMemory(&Addr, sizeof(Addr)); //зануляем ip-адрес сервера
	Addr.sin_family = AF_INET; //протокол ipv4 
	Addr.sin_port = htons(80); // в скобках - сетевой порт, на котором сервер слушает соединение 
	bind(Socket, (sockaddr*)&Addr, sizeof(Addr));


	while (1) {
		if (listen(Socket, 1) == SOCKET_ERROR)
		{
			//если не 
			printf("listening error\n");
		}
		else
		{
			printf("listening ok\n");
		}
		if (Sub = accept(Socket, (sockaddr*)&IncomingAddress, &AddressLen)) //ждем входящие соединения 
		{
			// соединение осуществлено 
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