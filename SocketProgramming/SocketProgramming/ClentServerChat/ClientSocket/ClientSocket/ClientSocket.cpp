// ClientSocket.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Client.h"



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

    Client client;
    client.initiateClientSetup();

}