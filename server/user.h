#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fstream>
#include <thread>
#include <mutex>



#include "file.h"
#include "room.h"


class UserManager{
    


    public:
        std::string userRoomName;
        std::string username;
        int socketfd;
        std::mutex m_mutex;
        UserManager(int socketfd);
        void receiveMessage();
        void sendMessage(std::string message);
        void registerUser(std::string username, std::string password);
        void loginUser(std::string username, std::string password);
        void logoutUser();
        void getAllUsers();
        void getAllConnectedUsers();
};

#endif