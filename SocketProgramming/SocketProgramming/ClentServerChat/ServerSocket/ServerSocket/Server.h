#pragma once

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <deque>
#include <string>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

class Server {
    static constexpr int PORT = 8027;
    static constexpr int ADDR_FAMILY = AF_INET;
    static constexpr int STREAM_TYPE = SOCK_STREAM;
    static constexpr int DEFAULT_PROTOCOL = 0;

    SOCKET serverSocket;
    int maxClients;
    int retryCount;

    std::chrono::milliseconds mSeconds;
    struct sockaddr_in serverAddress, clientAddress;

    std::deque<SOCKET> clientList;

    void createServerSocket();         // Create the server socket.
    void defineServerAddress();        // Set up the server address.
    void bindServerSocket();           // Bind the server socket to the address.
    void listenForConnections();       // Listen for connections from the clients.
    SOCKET acceptClientConnections();  // Accepts for connections listened from the clients.

    void sendMessages(SOCKET clientSocket);       // Send messages to the client;
    void receiveMessages(SOCKET clientSocket);    // Receive messages from the client;

    void startServer();              // Start the server.
    void closeServer(int exitStatus = EXIT_SUCCESS);           // Close the server and clean up.


public:
    // Constructor with default values for maxClients and retryCount.
    Server(int maxClients = 0, int retryCount = 5);

    void initiateServerSetup();   // Set up server initialization (starts server in a thread).
};
