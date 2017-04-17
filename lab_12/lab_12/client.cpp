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

SOCKET Socket;
WSADATA Winsock;
sockaddr_in Addr;
int Addrlen = sizeof(Addr);
char resp[17];

int main()
{

	WSAStartup(MAKEWORD(2, 2), &Winsock); // Start Winsock 

	if (LOBYTE(Winsock.wVersion) != 2 || HIBYTE(Winsock.wVersion) != 2) // Check version 
	{
		WSACleanup();
		return 0;
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	ZeroMemory(&Addr, sizeof(Addr)); // clear the struct 
	Addr.sin_family = AF_INET; // протокол ipv4 
	char ss[100];
	printf("Input ip:");
	scanf(" %s", &ss);
	Addr.sin_addr.s_addr = inet_addr(ss); //ip-адрес сервера. ≈го нужно спрашивать в меню у пользовател€. —ейчас - это наш же компьютер 
	Addr.sin_port = htons(8888); // порт сервера, к которому хотим подсоединитьс€ 



	if (connect(Socket, (sockaddr*)&Addr, sizeof(Addr)) < 0)
	{
		printf("Connection failed !\n");
		getchar();
		return 0;
	}

	printf("Connection successful !\n");

		recv(Socket, resp, 17, 0);
		printf("Message from server: %s\n", resp);
			send(Socket, "-", 3, MSG_OOB);


	closesocket(Socket); // после работы закрыть сокет 
	WSACleanup();
	getchar();
	return 0;
}