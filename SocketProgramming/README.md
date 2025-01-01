# Socket Programming

**Socket programming** is a way to enable communication between two nodes on a network, typically a client and a server. It is a fundamental concept in network programming and is used to send and receive data over a network. Sockets are endpoints of communication, and they provide an abstraction for using network services in a programmatic way.

### How It Works:
1. **Creating a Socket**: A socket is created using system calls. It acts as an endpoint for sending and receiving data.
2. **Binding the Socket**: For a server, the socket is bound to a specific IP address and port number.
3. **Listening for Connections**: A server socket listens for incoming connection requests from clients.
4. **Accepting a Connection**: Once a connection request is received, the server accepts it and establishes a communication channel with the client.
5. **Sending and Receiving Data**: Both the client and server use the socket to exchange data in the form of byte streams.
6. **Closing the Socket**: When the communication is complete, the socket is closed to release resources.

---

### Components in Socket Programming:
- **IP Address**: Identifies a host in a network.
- **Port Number**: Identifies a specific application or process on the host.
- **Protocols**: Defines the rules of communication. Common protocols include:
  - **TCP (Transmission Control Protocol)**: Reliable, connection-oriented.
  - **UDP (User Datagram Protocol)**: Faster, connectionless, less reliable.

---

### Steps for Socket Programming in C++:
C++ uses the **Berkeley sockets** API, which is platform-dependent (Windows uses Winsock, while Linux/Unix follows POSIX standards).

---


### Key Functions in C++ for sockets:
- `socket()`: Creates a socket.
- `bind()`: Binds the socket to an address/port (server side).
- `listen()`: Listens for incoming connections.
- `accept()`: Accepts an incoming connection.
- `connect()`: Connects to a server (client side).
- `send()`: Sends data through the socket.
- `recv()`/`read()`: Receives data through the socket.
- `close()`: Closes the socket.

---

### Practical Tips:
1. **Test Locally**: Use `127.0.0.1` or `localhost` for testing client-server communication on the same machine.
2. **Use Threads**: To handle multiple clients simultaneously, consider multithreading or asynchronous programming.
3. **Handle Errors**: Always check return values for errors.

Would you like guidance on specific socket programming concepts, such as multithreading or UDP communication?