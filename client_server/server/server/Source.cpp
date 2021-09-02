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

    cout << "listen socket" << ListenSocket << endl;
    fd_set master;
    FD_ZERO(&master);
    FD_SET(ListenSocket, &master);

    while (true)
    {
        cout << "=================================================" << endl;
        fd_set copy = master; 
        if (master.fd_count == 3)
        {
            FD_CLR(ListenSocket, &master);
            const char *first = "1";
            const char *second = "2";
            send(master.fd_array[0], first, 4096, 0);
            send(master.fd_array[1], second, 4096, 0);
        }
        else if (master.fd_count < 1 )
        {
            FD_SET(ListenSocket, &master);
        }



        int socketCount = select(0, &copy, nullptr, nullptr, nullptr);


        for (int i = 0; i < socketCount; i++)
        {

            SOCKET sock = copy.fd_array[i];
            if (sock == ListenSocket)
            {
                cout << " trong if " << endl;
                // accept a new connection 
                SOCKET client = accept(ListenSocket, NULL, NULL);
                

                if (client == INVALID_SOCKET) {
                    printf("accept failed with error: %d\n", WSAGetLastError());
                    closesocket(ListenSocket);
                    WSACleanup();
                    return 1;
                }
                // add the new connection to the list of connection clients
                FD_SET(client, &master);

                cout << "end if" << endl;
            }
            else
            {
                cout << "trong else" << endl;
                char buf[4096];
                ZeroMemory(buf, 4096);
                // recieve message
                int byteIn = recv(sock, buf, 4096, 0);


                cout << "byte in: " << byteIn << endl;
                if (byteIn <= 0)
                {
                    //drop client
                    closesocket(sock);
                    FD_CLR(sock, &master);
                }
                else {

                    // send message to other clients, and definiately NOt the listening socket
                    for (int i = 0; i < master.fd_count; i++)
                    {
                        SOCKET outsock = master.fd_array[i];
                        if (outsock != ListenSocket && outsock != sock)
                        {
                            send(outsock, buf, 4096, 0);
                        }
                    }
                }
            }
        }
    }

    return 0;
}
