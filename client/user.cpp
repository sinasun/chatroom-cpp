#include "user.h"

User::User(){
    isLogged = false;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    std::memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
}
void User::connect(std::string ip, int port){
    serv_addr.sin_port = htons(port);

    std::cout << "Connecting to " << ip << "Port:" << port << std::endl;

    if(inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0){
        std::cout << "Invalid address/ Address not supported" << std::endl;
        return;
    }
    if(::connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        std::cout << "Connection Failed" << std::endl;
        return;
    }
    std::cout << "Connected" << std::endl;

}

void User::disconnect(){
    close(sockfd);
    isLogged = false;
}

void User::send(std::string message){
    ::send(sockfd, message.c_str(), message.length(), 0);
}

std::string User::receive(){
    char buffer[1024];
    int bytes_received = recv(sockfd, buffer, sizeof(buffer), 0);
    if (bytes_received == -1) {
        std::cerr << "Error receiving data from server" << std::endl;
        return "";
    }
    std::string received_str(buffer, bytes_received);
    return received_str;
}

void User::sentToRoom(std::string message){
    send("send_message " + message);
}

void User::receiveFromRoom(){
    std::string message = receive();
    std::cout << message << std::endl;
}



bool User::getIsLogged(){
    return isLogged;
}

void User::registerUser(std::string username, std::string password){
    
    std::string message = "register " + username + " " + password;
    send(message);
    if(receive() == "registered"){
        this->username = username;
        isLogged = true;
    }else{
        std::cout << "Cannot Register the User" << std::endl;
    };
}

void User::loginUser(std::string username, std::string password){
    std::string message = "login " + username + " " + password;
    send(message);
    if(receive() == "logged_in"){
        this->username = username;
        isLogged = true;
    }else{
        std::cout << "Cannot Login the User" << std::endl;
    };
}

void User::logoutUser(){
    send("logout");
    if(receive() == "logged_out"){
        this -> username = "";
        isLogged = false;
    }else{
        std::cout << "Cannot Logout the User" << std::endl;
    };
}

void User::createRoom(std::string roomName){
    send("create_room " + roomName);
    if(receive() == "room_created"){
        this -> roomName = roomName;
        std::cout << "Room created" << std::endl;
    }else{
        std::cout << "Cannot create the room" << std::endl;
    };
}

void User::joinRoom(std::string roomName){
    send("join_room " + roomName);
    if(receive() == "room_joined"){
        this -> roomName = roomName;
        std::cout << "Room joined" << std::endl;
    }else{
        std::cout << "Cannot join the room" << std::endl;
    };
}

void User::leaveRoom(){
    send("leave_room");
    if(receive() == "room_left"){
        this -> roomName = "";

        std::cout << "Room left" << std::endl;
    }else{
        std::cout << "Cannot leave the room" << std::endl;
    };
}

void User::deleteRoom(){
    send("delete_room");
    if(receive() == "room_deleted"){
        this -> roomName = "";
        std::cout << "Room deleted" << std::endl;
    }else{
        std::cout << "Cannot delete the room" << std::endl;
    };
}

void User::printAllRooms(){
    send("get_all_rooms");
    std::string rooms = receive();
    std::cout << rooms << std::endl;
}

void User::printAllUsers(){
    send("get_all_users");
    std::string users = receive();
    std::cout << users << std::endl;
}

void User::printAllConnectedUsers(){
    send("get_all_connected_users");
    std::string users = receive();
    std::cout << users << std::endl;

}

User::~User(){
    close(sockfd);
}