// SocketServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <winsock.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")


#define PORT 8027

int serverSocket, maxFD, maxClients = 5, returnValue = 0;
int clientArray[5];
fd_set readFD, writeFD, exceptFD;

void processNewMessage(int clientSocket) {
    std::cout << "Processing the new message for client socket: " << clientSocket << std::endl;
    char buffer[256 + 1];
    returnValue = recv(clientSocket, buffer, 255, 0);
    if (returnValue < 0) {
        std::cout << "Something wrong happened.. closing the connection... " << std::endl;
        closesocket(clientSocket);
        for (int index = 0; index < maxClients; index++) {
            if (clientArray[index] == clientSocket) {
                clientArray[index] = 0;
                break;
            }

        }
    }
    else {
        std::cout << "Send your message.." << std::endl;
        getchar();
        std::cout << buffer << std::endl;
        send(clientSocket, "Processed your request...", 26, 0);
        std::cout << "------------------------------------" << std::endl;
    }
}

void processNewRequest() {
    if (FD_ISSET(serverSocket, &exceptFD)) {
        std::cout << "There is an exception..." << std::endl;
    }
    if (FD_ISSET(serverSocket, &writeFD)) {
        std::cout << "Ready to write something..." << std::endl;
    }
    if (FD_ISSET(serverSocket, &readFD)) {
        int addrSize = sizeof(struct sockaddr);
        int clientSocket = accept(serverSocket, NULL, &addrSize);
        if (clientSocket > 0) {
            int index;
            for (index = 0; index < maxClients; index++) {
                if(clientArray[index] == 0){
                    clientArray[index] = clientSocket;
                    send(clientSocket, "Got the connection done successfully", 37, 0);
                }
                
            }
            if (index == maxClients) {
                std::cout << "Maximum client connection reached" << std::endl;
            }
        }
    }
    else {
        for(int index = 0; index < maxClients; index++) {
            if (FD_ISSET(clientArray[index], &readFD)) {
                // Got the new message for the client
                // Just reveive the new message and queue that for new workers of your server to fulfill
                processNewMessage(clientArray[index]);
            }
        }
    }
}

int main()
{

    // to working with sockets in windows, we need to initialize WSA library.
    WSADATA ws;

    if (WSAStartup(MAKEWORD(2, 2), &ws) != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return 1;
    }
    else {
        std::cout << "WSAStartup successfully initialized" << std::endl;
    }

    // Initializing a socket connection with connection oriented socket and tcp protocol(address family, stream type, protocol)
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    else {
        std::cout << "Socket opened successfully: " << serverSocket << std::endl;
    }

    // Initializing the environment for socket address structure
    struct sockaddr_in serverAddr; //used to store the address of the socket
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT); // htons - host to network start
    //serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // inet_addr, convert the ip string byte order
    serverAddr.sin_addr.s_addr = INADDR_ANY; // make it listen to all the available IPs.
    memset(&(serverAddr.sin_zero), 0, 8);

    // setsocopt
    int optValue = 0, optLen = sizeof(optValue);

    // if same address need to be used for another port, SO_REUSEADDR else, SO_EXCLUSIVEADDRUSE
    returnValue = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&optValue, optLen);
    if (returnValue == SOCKET_ERROR) {
        std::cout << "Setsocopt call failed" << std::endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    else {
        std::cout << "Setsockopt call successful" << std::endl;
    }

    // Bind the socket to the port
    returnValue = bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (returnValue == SOCKET_ERROR) {
        std::cerr << "binding failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    else {
        std::cout << "Biniding success" << std::endl;
    }

    // Listen the request from client (queues the request)
    returnValue = listen(serverSocket, SOMAXCONN); // (socket name, backlog), backlog means how many request can the server handle at a time
    if (returnValue == SOCKET_ERROR) {
        std::cerr << "Listening failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    else {
        std::cout << "Listening to the assigned socket" << std::endl;
    }

    maxFD = serverSocket;
    struct timeval timeout;
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    while (1) {
        // FD_ZERO - clear all file descriptors from the set
        FD_ZERO(&writeFD);
        FD_ZERO(&readFD);
        FD_ZERO(&exceptFD);

        // FD_SET - set all file descriptors to the set
        FD_SET(serverSocket, &readFD);
        FD_SET(serverSocket, &exceptFD);

        for (int index = 0; index < maxClients; index++) {
            if (clientArray[index] != 0) {
                FD_SET(clientArray[index], &readFD);
                FD_SET(clientArray[index], &exceptFD);
            }

        }
        //std::cout << "Before select call r: " << readFD.fd_count << std::endl;

        // Keep waiting for new requests and proceed as per the request
        returnValue = select(maxFD + 1, &readFD, &writeFD, &exceptFD, &timeout);

        //std::cout << "After select call r: " << readFD.fd_count << std::endl;

    
        if (returnValue > 0) {
            // When someone connects or communicates with the message over a
            // dedicated connection

            /* Note:
            * Socket listening to the new clients and then communicating with the
              same client are not the same.
            * After connection, you get one more socket to communicate with client.
            * You need to send/receive message over the network using that new socket.
            */

            std::cout << "Data on port.. processing now" << std::endl;

            processNewRequest();

        }
        else if (returnValue == 0) {
            // No connection or any communication request made or none of the 
            // sockets are ready
            
            //WSACleanup();
            //return EXIT_FAILURE;
        }
        else {
            // It failed and your applicationshould show some usefull message.
            WSACleanup();
            //return EXIT_FAILURE;
        }
    }



}
