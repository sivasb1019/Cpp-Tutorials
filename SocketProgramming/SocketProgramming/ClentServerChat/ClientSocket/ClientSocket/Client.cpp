#include "Client.h"


// Client default constructor
Client::Client(int maxClients, int retryCount) {
    if (maxClients > 0) {
        this->maxClients = maxClients;
        clientList.resize(maxClients);
    }
    this->retryCount = retryCount;
    this->mSeconds = std::chrono::milliseconds(1000);
}

void Client::setServerIP() {
    static std::string server_ip;
    std::cout << "Enter server IP to connect: ";
    getline(std::cin, server_ip);
    std::cout << "Connection in progress...." << std::endl;
    serverIP = std::make_unique<const char*>(server_ip.c_str());
}

void Client::createClientSocket() {

    for (int attempt = 0; attempt < retryCount; attempt++) {
        // Socket creation
        clientSocket = socket(ADDR_FAMILY, STREAM_TYPE, DEFAULT_PROTOCOL);
        if (clientSocket < 0) {
            std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
            std::cout << "Socket creation retry attempt: " << attempt << std::endl;
            // Make thread sleep for 1 seconds untill the last retry attempt
            if (attempt < retryCount - 1) {
                std::this_thread::sleep_for(mSeconds);
            }
        }
        else {
            std::cout << "Socket opened successfully: " << clientSocket << std::endl;
            return;
        }
    }
    std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
    closeClient(EXIT_FAILURE);
}

void Client::defineServerAddress() {
    setServerIP();
    serverAddress.sin_family = ADDR_FAMILY;
    serverAddress.sin_port = htons(PORT);
    //int isConverted = inet_pton(ADDR_FAMILY, *serverIP, &(serverAddress.sin_addr));
    if (inet_pton(ADDR_FAMILY, *serverIP, &(serverAddress.sin_addr)) != 1) {
        std::cerr << "Failed to convert address." << WSAGetLastError() << std::endl;
        return;
    }
    /*clientAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(&(clientAddress.sin_zero), 0, 8);*/
}

void Client::connectToServer() {
    for (int attempt = 0; attempt < retryCount; attempt++) {
        // Socket creation
        int connectionStatus = connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
        //int connectionStatus = connect(clientSocket, nullptr, sizeof(serverAddress));
        if (connectionStatus < 0) {
            std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
            std::cout << "Connection to server retry attempt: " << attempt << std::endl;
            // Make thread sleep for 1 seconds untill the last attempt
            defineServerAddress();
            if (attempt < retryCount - 1) {
                std::this_thread::sleep_for(mSeconds);
            }
        }
        else {
            std::cout << "Client socket connected to server: " << clientSocket << std::endl;
            return;
        }
    }
    std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
    closeClient(EXIT_FAILURE);
}

void Client::sendMessages() {
    while (1) {
        std::string msg;
        getline(std::cin, msg);
        msg = name + ": " + msg;

        int bytesSent = send(clientSocket, msg.c_str(), msg.length(), 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "Message sent failed: " << WSAGetLastError() << std::endl;
            continue;
        }
    }
}

void Client::receiveMessages() {
    char buffer[1024] = { 0 };
    while (1) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "Unable to receive message: " << WSAGetLastError() << std::endl;
            return;
        }
        else if (bytesReceived == 0) {
            std::cout << "Connection was closed by server: " << clientSocket << std::endl;
            closeClient();
        }
        //std::string msg(buffer);
        buffer[bytesReceived] = '\0';

        std::cout << "server: " << buffer << std::endl;

    }

}

void Client::startClient() {
    createClientSocket();
    defineServerAddress();
    connectToServer();
    std::cout << "Client setup completed..." << std::endl;
    std::cout << "Enter your name: ";
    getline(std::cin, name);
    std::cout << "You can now send and receive messages from the server" << std::endl;

    std::thread sendThread(&Client::sendMessages, this);
    std::thread receiveThread(&Client::receiveMessages, this);

    sendThread.join();
    receiveThread.join();

}

void Client::closeClient(int exitStatus) {
    // CLose the socket if available
    if (clientSocket >= 0) {
        closesocket(clientSocket);
        std::cout << "Socket closed." << std::endl;
    }

    // Clean up Winsock
    WSACleanup();
    std::cout << "Winsock cleanup done." << std::endl;

    // Exit the program
    std::cout << "Client terminating." << std::endl;
    exit(exitStatus);
}

void Client::initiateClientSetup() {
    std::thread startThread(&Client::startClient, this);
    startThread.join();
    closeClient();
}