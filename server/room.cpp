#include "room.h"


void Room::createRoom(std::string roomName){
    File file;
    file.appendFile("room.txt", roomName);
    file.createFile(roomName + ".txt");
}
void Room::addUser(std::string roomName, std::string username, int userfd) {
    File file;
    file.appendFile(roomName + ".txt", username + " " + std::to_string(userfd));
}

void Room::removeUser(std::string roomName, std::string username, int userfd){
    File file;
    file.deleteLine(roomName + ".txt", username + " " + std::to_string(userfd));
}

void Room::sendMessage(std::string roomName,std::string username, std::string message){
    File file;
    std::string content = file.readFile(roomName + ".txt");
    std::istringstream iss(content);
    std::string line;
    std::cout << line << std::endl;
    while(std::getline(iss, line)){
        std::istringstream iss2(line);
        std::string word;
        std::vector<std::string> words;
        while(std::getline(iss2, word, ' ')){
            words.push_back(word);
        }
        if(words[0] != username){
            message = username + ": " + message;
            send(std::stoi(words[1]), message.c_str(), message.length(), 0);
        }
    }
}

void Room::deleteRoom(std::string roomName){
    File file;
    file.deleteFile(roomName + ".txt");
    file.deleteLine("room.txt", roomName);
}


std::string Room::getRoomUsers(std::string roomName){
    File file;
    std::string content = file.readFile(roomName + ".txt");
    return content;
}

std::string Room::getAllRooms(){
    File file;
    std::string content = file.readFile("room.txt");
    return content;
}