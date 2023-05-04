# Multithread Chatroom in C++

This is a multithread chatroom project built with C++ using sockets and mutexes.


## Table of Contents

- [Client](#client)
- [Server](#server)
- [Getting Started](#getting-started)
- [Contributing](#contributing)
- [License](#license)

## Client

The client application is located in the /client directory and can be run using the following command:


```bash

make && ./client

```

The client supports the following options:

 - Connect to a server with IP address
 - Login with a username and password
 - Register an account on the server
 - Print all rooms
 - Print all users in the server
 - Print all connected users in the server
 - Create a room
 - Join a room


After joining a room, the client is presented with the following menu:

 - Send a message
 - Receive messages
 - Leave the room
 - Delete the room


## Server

The server application is located in the /server directory and can be run using the following command:

```bash

make && ./server

```


## Getting Started

1. Clone the repository:

```bash

git clone https://github.com/sinasun/chatroom-cpp.git

```

2. Compile the client and server applications:

```bash

cd chatroom-cpp/client
make

cd ../server
make

```

3. Run the client and server applications:

```bash
##for client:
./client

##for server:
./server

```

## Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.


## License

This repository is licensed under the MIT License. See the `LICENSE` file for more information.