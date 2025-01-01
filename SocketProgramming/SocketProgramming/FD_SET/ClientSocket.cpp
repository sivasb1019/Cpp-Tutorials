// ClientSocket.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <winsock.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8027

int main()
{
    int returnValue = 0;
    WSAData wsaData;

    
    // to working with sockets in windows, we need to initialize WSA library.
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return 1;
    }
    else {
        std::cout << "WSAStartup successfully initialized" << std::endl;
    }

    // Initializing a socket connection with connection oriented socket and machine undelying protocol(address family, stream type, protocol)
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return EXIT_FAILURE;
    }
    else {
        std::cout << "Socket opened successfully: " << clientSocket << std::endl;
    }

    // Initializing the environment for socket address structure
    sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(PORT);
    clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    memset(&(clientAddr.sin_zero), 0, 8);

    // connect the socket to the server
    if (connect(clientSocket, (struct sockaddr*)&clientAddr, sizeof(clientAddr)) == SOCKET_ERROR){
        std::cerr << "Connection to the server failed: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return EXIT_FAILURE;
    }
    else {
        std::cout << "Connection to the server success" << std::endl;
        char buffer[255] = { 0, };
        recv(clientSocket, buffer, 255, 0);
        std::cout << "Reponse from the server:";
        std::cout << buffer << std::endl;

        std::cout << "Now send the messages to the server..." << std::endl;

        while (1) {
            fgets(buffer, 255, stdin);
            send(clientSocket, buffer, 255, 0);
            std::cout << "Reponse from the server:";
            recv(clientSocket, buffer, 256, 0);
            std::cout << buffer << std::endl << "Now you can send the next message.." << std::endl;

        }
    }

}
