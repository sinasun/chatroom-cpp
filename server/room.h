#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <sys/socket.h>



#include "file.h"


class Room{
    public:
        void createRoom(std::string roomName);
        void addUser(std::string roomName, std::string username, int userfd);
        void removeUser(std::string roomName, std::string username, int userfd);

        void sendMessage(std::string roomName,std::string username, std::string message);


        std::string getRoomUsers(std::string roomName);
        std::string getAllRooms();

        void deleteRoom(std::string roomName);

};

#endif