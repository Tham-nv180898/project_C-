#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "caroGame.h"
#include <string>


// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

using namespace std;
#define DEFAULT_BUFLEN 4096
#define DEFAULT_PORT "27018"

int __cdecl main(int argc, char** argv)
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    string sendbuf;
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;


    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        cout << "WSAStartup failed with error: " << iResult << endl;
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo("127.0.0.1", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        cout << "getaddrinfo failed with error: " << iResult << endl;
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            cout << "socket failed with error: " << WSAGetLastError() << endl;
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        cout << "Unable to connect to server" << endl;
        WSACleanup();
        return 1;
    }

    int number = NULL;
    iResult = recv(ConnectSocket, recvbuf, 4096, 0);
    if (iResult > 0)
    {
        cout << recvbuf << endl;
        number =stoi(recvbuf);
    }
    

    int i = 0;
    unsigned int row = NULL;
    unsigned int col = NULL;
    viewPlay player;

    player.showChessboard();
    while (i < 50)
    {
        if (number == 1)
        {
            cout << "Player 1 turn:";
            cin >> row >> col;
            while (row > 9 or col > 9 or player.checkChessboard(row, col) or cin.fail())
            {
                cin.clear();
                cin.ignore(256, '\n');   // ignore the line change
                cout << "Player 1 turn:";
                cin >> row >> col;
            }

            send(ConnectSocket, to_string(row).c_str(), 4096, 0);
            send(ConnectSocket, to_string(col).c_str(), 4096, 0);

            int retX = player.putX(row, col);
            if (retX == 1) {
                break;
            }

            iResult = recv(ConnectSocket, recvbuf, 4096, 0);
            row = stoi(recvbuf);

            iResult = recv(ConnectSocket, recvbuf, 4096, 0);
            col = stoi(recvbuf);

            int retO = player.putO(row, col);
            if (retO == 1)
                break;
        }
        
        if (number == 2)
        {
            iResult = recv(ConnectSocket, recvbuf, 4096, 0);
            row = stoi(recvbuf);
            cout << "row" << row << endl;
            iResult = recv(ConnectSocket, recvbuf, 4096, 0);
            col = stoi(recvbuf);
            int retX = player.putX(row, col);
            if (retX == 1)
                break;


            cout << "Player 2 turn:";
            cin >> row >> col;
            while (row > 9 or col > 9 or player.checkChessboard(row, col) or cin.fail())
            {
                cin.clear();
                cin.ignore(256, '\n');   // ignore the line change
                cout << "Player 2 turn:";
                cin >> row >> col;
            }


            send(ConnectSocket, to_string(row).c_str(), 4096, 0);
            send(ConnectSocket, to_string(col).c_str(), 4096, 0);

            int retO = player.putO(row, col);
            if (retO == 1) {
                break;
            }
        }

        i++;
    }
    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}