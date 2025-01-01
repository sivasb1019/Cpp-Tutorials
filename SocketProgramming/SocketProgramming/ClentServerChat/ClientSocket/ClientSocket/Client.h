#pragma once

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <string>
//#include <cstring>
#include <vector>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

class Client {
    static constexpr int PORT = 8027;
    static constexpr int ADDR_FAMILY = AF_INET;
    static constexpr int STREAM_TYPE = SOCK_STREAM;
    static constexpr int DEFAULT_PROTOCOL = 0;

    SOCKET clientSocket;
    //int clientConnection;
    int maxClients;
    //int maxFD;
    int retryCount;

    //fd_set readFD, writeFD, exceptFD;
    sockaddr_in clientAddress, serverAddress;

    std::string name;
    std::unique_ptr<const char*> serverIP;
    std::vector<int> clientList;
    std::chrono::milliseconds mSeconds;

    //std::string getServerIP();   // Get Server IP to connect.
    void setServerIP();            // Set the Server IP to connect.

    void createClientSocket();     // Create the client socket.
    void defineServerAddress();    // Set up the server address.
    void connectToServer();        // Connect the client socket to the server.

    void sendMessages();           // Sending messages to the server.
    void receiveMessages();        // Receive messages to the server.

    void startClient();           // Start the client (to be called in a new thread).

    void closeClient(int exitStatus = EXIT_SUCCESS);         // Close the client and clean up.


public:
    // Constructor with default values for maxClients and retryCount.
    Client(int maxClients = 0, int retryCount = 5);

    void initiateClientSetup(); // Set up client initialization (starts client in a thread).
};
