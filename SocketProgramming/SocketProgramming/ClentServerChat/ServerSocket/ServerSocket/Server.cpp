#include "Server.h"


// Server default constructor
Server::Server(int maxClients, int retryCount) {
    if (maxClients > 0) {
        this->maxClients = maxClients;
        clientList.resize(maxClients);
    }
    this->retryCount = retryCount;
    this->mSeconds = std::chrono::milliseconds(1000);
}

void Server::createServerSocket() {

    for (int attempt = 0; attempt < retryCount; attempt++) {
        // Socket creation
        serverSocket = socket(ADDR_FAMILY, STREAM_TYPE, DEFAULT_PROTOCOL);
        if (serverSocket < 0) {
            std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
            std::cout << "Socket creation retry attempt: " << attempt << std::endl;
            // Make thread sleep for 1 seconds untill the last attempt
            if (attempt < retryCount - 1) {
                std::this_thread::sleep_for(mSeconds);
            }
        }
        else {
            std::cout << "Socket opened successfully: " << serverSocket << std::endl;
            return;
        }
    }
    std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
    closeServer(EXIT_FAILURE);
}

void Server::defineServerAddress() {
    serverAddress.sin_family = ADDR_FAMILY;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
}

void Server::bindServerSocket() {
    int bindResult = bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
    if (bindResult == SOCKET_ERROR) {
        std::cerr << "Binding failed: " << WSAGetLastError() << std::endl;
        closeServer(EXIT_FAILURE);
    }
    else {
        std::cout << "Biniding success: " << bindResult << std::endl;
    }
}

void Server::listenForConnections() {
    int listenResult = listen(serverSocket, SOMAXCONN);
    if (listenResult == SOCKET_ERROR) {
        std::cerr << "Listening failed: " << WSAGetLastError() << std::endl;
        closeServer(EXIT_FAILURE);
    }
    else {
        std::cout << "Listening for connections... " << std::endl;
    }
}

SOCKET Server::acceptClientConnections() {
    int clientSize = sizeof(clientAddress);
    SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddress, &clientSize);

    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Client acceptance failed: " << WSAGetLastError() << std::endl;
        //continue;
    }
    else {
        std::cout << "Client connected:" << clientSocket << std::endl;
        clientList.push_back(clientSocket);
    }
    return clientSocket;
}

void Server::sendMessages(SOCKET clientSocket) {
    while (1) {
        std::string msg;
        getline(std::cin, msg);

        int bytesSent = send(clientSocket, msg.c_str(), msg.length(), 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "Message sent failed: " << WSAGetLastError() << std::endl;
            continue;
        }
    }
}

void Server::receiveMessages(SOCKET clientSocket) {
    /*
    std::vector<char> buffer;
    while ((bytesReceived = recv(clientSocket, buffer.data(), buffer.size(), 0)) > 0) {
        msg.append(buffer.begin(), buffer.begin() + bytesReceived);
    }
    */
    char buffer[1024] = { 0 };
    while (1) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived == SOCKET_ERROR) {
            std::cout << "Connection was closed by client: " << clientSocket << std::endl;
            auto itr = find(clientList.begin(), clientList.end(), clientSocket);
            std::cout << *itr << std::endl;
            if (itr != clientList.end()) {
                clientList.erase(itr);
            }
            closesocket(clientSocket);
            return;
            //WSACleanup();
        }
        buffer[bytesReceived] = '\0';

        std::cout << buffer << std::endl;
        //std::cout << clientSocket << ": " << buffer << std::endl;
    }
}


void Server::startServer() {
    createServerSocket();
    defineServerAddress();
    bindServerSocket();
    int i = 0;
    listenForConnections();
    while (1) {
        SOCKET clientSocket = acceptClientConnections();
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Client acceptance failed: " << WSAGetLastError() << std::endl;
            continue;
        }
        //std::cout << "Client connected: " << clientSocket << std::endl;
        std::thread sendThread(&Server::sendMessages, this, clientSocket);
        std::thread receiveThread(&Server::receiveMessages, this, clientSocket);

        sendThread.detach();
        receiveThread.detach();
    }
}

void Server::closeServer(int exitStatus) {
    // CLose the socket if available
    if (serverSocket >= 0) {
        closesocket(serverSocket);
        std::cout << "Socket closed." << std::endl;
    }

    // Clean up Winsock
    WSACleanup();
    std::cout << "Winsock cleanup done." << std::endl;

    // Exit the program
    std::cout << "Server terminating." << std::endl;
    exit(exitStatus);
}

void Server::initiateServerSetup() {
    std::thread startThread(&Server::startServer, this);
    startThread.join();
    closeServer();
}