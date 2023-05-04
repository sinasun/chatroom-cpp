#include "user.h"


UserManager::UserManager(int new_socket): socketfd(new_socket){
}

void UserManager::receiveMessage(){

    bool is_connected = true;
    while(is_connected){
        char buffer[1024] = {0};
        int bytes_read = read(socketfd, buffer, 1024);
        if (bytes_read == -1) {
            std::cerr << "Error reading from client socket" << std::endl;
        } else if (bytes_read == 0) {
            std::cout << "Client with socket fd " << socketfd << " disconnected" << std::endl;
            close(socketfd);
            is_connected = false;
        } else {
            std::cout << "Received message from client with socket fd " << socketfd << ": " << buffer << std::endl;
            std::string message = buffer;
            //register user
            if(message.substr(0, 8) == "register"){
                std::string username = message.substr(9, message.find(" ", 9) - 9);
                std::string password = message.substr(message.find(" ", 9) + 1, message.length() - 1);
                std::lock_guard<std::mutex> lock(m_mutex);

                registerUser(username, password);
            }

            //login user
            if(message.substr(0, 5) == "login"){
                std::string username = message.substr(6, message.find(" ", 6) - 6);
                std::string password = message.substr(message.find(" ", 6) + 1, message.length() - 1);
                std::lock_guard<std::mutex> lock(m_mutex);

                loginUser(username, password);
            }

            //logout user
            if(message == "logout"){
                logoutUser();
            }

            //print all users
            if(message == "get_all_users"){
                getAllUsers();
            }

            //print all connected users
            if(message == "get_all_connected_users"){
                getAllConnectedUsers();
            }
            
            //create room
            if(message.substr(0, 12) == "create_room "){
                std::string roomName = message.substr(12, message.length() - 1);
                Room room;
                room.createRoom(roomName);
                std::cout << "Room created" << std::endl;
                sendMessage("room_created");
                
            }

            //join room
            if(message.substr(0, 10) == "join_room "){
                std::string roomName = message.substr(10, message.length() - 1);
                Room room;
                room.addUser(roomName, username, socketfd);
                std::cout << "User joined room" << std::endl;
                sendMessage("room_joined");
                userRoomName = roomName;
            }

            //leave room
            if(message.substr(0, 10) == "leave_room"){
                Room room;
                room.removeUser(userRoomName, username, socketfd);
                std::cout << "User left room" << std::endl;

                sendMessage("room_left");

            }

            //delete room
            if(message.substr(0, 12) == "delete_room "){
                std::string roomName = message.substr(12, message.length() - 1);
                Room room;
                room.deleteRoom(roomName);
                std::cout << "Room deleted" << std::endl;
                sendMessage("room_deleted");
            }

            //send message to room "send_message hiii"
            if(message.substr(0, 13) == "send_message "){
                std::string messageContent = message.substr(13, message.length() - 1);
                Room room;

                room.sendMessage(userRoomName, username, messageContent);
                std::cout << "Message sent" << std::endl;
            }

            //get all rooms
            if(message == "get_all_rooms"){
                Room room;
                std::string allRooms = room.getAllRooms();
                sendMessage(allRooms);
            }

            //get room users
            if(message.substr(0, 13) == "get_room_users"){
                Room room;
                std::string roomUsers = room.getRoomUsers(userRoomName);
                sendMessage(roomUsers);
            }
        }
    }
    close(socketfd);

}

void UserManager::sendMessage(std::string message){
    send(socketfd, message.c_str(), message.length(), 0);
}

void UserManager::registerUser(std::string username, std::string password){
    std::string fileName = "users.txt";
    File file;
    std::string content = username + " " + password;
    if(file.appendFile(fileName, content)){
        file.appendFile("connectedusers.txt", username);
        std::cout << "User registered" << std::endl;
        this -> username = username;
        sendMessage("registered");
    }
}


void UserManager::loginUser(std::string username, std::string password){
    std::string fileName = "users.txt";
    File file;
    if(file.lineExist(fileName, username + " " + password)){
        std::cout << "User logged in" << std::endl;
        file.appendFile("connectedusers.txt", username);
        this -> username = username;
        sendMessage("logged_in");
    }
}

void UserManager::logoutUser(){
    std::string fileName = "connectedusers.txt";
    File file;
    file.deleteLine(fileName, username);

    std::cout << "User logged out" << std::endl;
    sendMessage("logged_out");
}

void UserManager::getAllUsers(){
    std::string fileName = "users.txt";
    File file;
    std::string content = file.readFile(fileName);
    
    sendMessage(content);
}

void UserManager::getAllConnectedUsers(){
    std::string fileName = "connectedusers.txt";
    File file;
    std::string content = file.readFile(fileName);
    sendMessage(content);
}




