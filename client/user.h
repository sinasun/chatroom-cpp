#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

class User{
    bool isLogged;
    std::string username;
    std::string roomName;

    int sockfd;
    struct sockaddr_in serv_addr;

    public:
        User();
        ~User();
        void connect(std::string ip, int port);
        void disconnect();
        void send(std::string message);
        std::string receive();

        void sentToRoom(std::string message);
        void receiveFromRoom();

        bool getIsLogged();
        void registerUser(std::string username, std::string password);
        void loginUser(std::string username, std::string password);
        void logoutUser();

        void createRoom(std::string roomName);
        void joinRoom(std::string roomName);
        void leaveRoom();
        void deleteRoom();

        void printAllRooms();
        void printAllUsers();
        void printAllConnectedUsers();
};

#endif