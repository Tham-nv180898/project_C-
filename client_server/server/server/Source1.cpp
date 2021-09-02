#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

using namespace std;
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 30
#define DEFAULT_PORT "27018"

int __cdecl main(void)
{
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        cout << "WSAStartup failed with error: " << iResult << endl;
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        cout << "getaddrinfo failed with error: " << iResult;
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        cout << "socket failed with error: " << WSAGetLastError() << endl;
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        cout << "bind failed with error: " << WSAGetLastError() << endl;
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        cout << "listen failed with error: " << WSAGetLastError();
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    
    fd_set master;
    FD_ZERO(&master);
    FD_SET(ListenSocket, &master);
    SOCKET A = 350;
    FD_SET(A, &master);
    cout << "master: " << master.fd_count << endl;

    //fd_set coppy = master;
    //cout << "coppy: " << coppy.fd_count << endl;
    //while (true)
    //{
    //    fd_set copy = master;
    //    int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
    //    for (int i = 0; i < socketCount; i++)
    //    {
    //        SOCKET sock = copy.fd_array[i];
    //        if (sock == ListenSocket)
    //        {
    //            // accept a new connection 
    //            SOCKET client = accept(ListenSocket, NULL, NULL);
    //            // add the new connection to the list of connection clients
    //            FD_SET(client, &master);
    //            // send a welcome message to the connection client
    //            string welcomMsg = "welcome to the awesome chat server!";
    //            send(client, welcomMsg.c_str(), welcomMsg.size()+1, 0);
    //        }
    //        else
    //        {
    //            char buf[4096];
    //            ZeroMemory(buf, 4096);
    //            // recieve message
    //            int byteIn = recv(sock, buf, 4096, 0);
    //            if (byteIn <= 0)
    //            {
    //                //drop client
    //                closesocket(sock);
    //                FD_CLR(sock, &master);
    //            }
    //            else {

    //                // send message to other clients, and definiately NOt the listening socket
    //                for (int i = 0; i < master.fd_count; i++)
    //                {
    //                    SOCKET outsock = master.fd_array[i];
    //                    if (outsock != ListenSocket && outsock != sock)
    //                    {
    //                        send(outsock, buf, byteIn, 0);
    //                    }
    //                }
    //            }
    //        }
    //    }
    //}

    return 0;
}
