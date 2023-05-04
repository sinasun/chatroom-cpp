#include "menu.h"

int Menu::getOption(int min, int max){
    int option;
    std::cout << "Enter your option: ";
    if(!(std::cin >> option)){
        std::cin.clear();
        std::cin.ignore(100, '\n');
        std::cout << "Invalid option. Try again." << std::endl;
        return getOption(min, max);
    }
    if(option < min || option > max){
        std::cout << "Invalid option. Try again." << std::endl;
        return getOption(min, max);
    }
    return option;
}

void Menu::printIntroMenu(User& user){
    std::cout << "1. connect to a server with ip" << std::endl;
    std::cout << "2. Exit" << std::endl;
    int option = getOption(1, 2);
    std::string ip;
    int port;
    switch(option){
        case 1:
            std::cout << "Enter the ip address: ";
            std::cin >> ip;
            std::cout << "Enter the port: ";
            std::cin >> port;
            user.connect(ip, port);
            printEnterMenu(user);
            break;
        case 2:
            exit(0);
            break;
    }
}

void Menu::printEnterMenu(User& user){
    std::cout << "1. Login - login with a username and password" << std::endl;
    std::cout << "2. Register - Register an account in the server" << std::endl;
    std::cout << "3. Disconnect from the server" << std::endl;

    int option = getOption(1, 3);
    std::string username;
    std::string password;
    switch(option){
        case 1:
            std::cout << "Enter your username: ";
            std::cin >> username;
            std::cout << "Enter your password: ";
            std::cin >> password;
            user.loginUser(username, password);
            if(user.getIsLogged())
                printServerMenu(user);
            else
                printEnterMenu(user);
            break;
        case 2:
            std::cout << "Enter your username: ";
            std::cin >> username;
            std::cout << "Enter your password: ";
            std::cin >> password;
            user.registerUser(username, password);
            if(user.getIsLogged())
                printServerMenu(user);
            else
                printEnterMenu(user);
            break;
        case 3:
            user.disconnect();
            printIntroMenu(user);
            break;
    }
}

void Menu::printServerMenu(User& user){
    std::cout << "1. Print all rooms" << std::endl;
    std::cout << "2. Print all users in the server" << std::endl;
    std::cout << "3. Print all connected users in the server" << std::endl;
    std::cout << "4. Create a room" << std::endl;
    std::cout << "5. Join a room" << std::endl;
    std::cout << "6. Disconnect from the server" << std::endl;
    int option = getOption(1, 6);
    std::string roomName;
    switch(option){
        case 1:
            user.printAllRooms();
            printServerMenu(user);
            break;
        case 2:
            user.printAllUsers();
            printServerMenu(user);
            break;
        case 3:
            user.printAllConnectedUsers();
            printServerMenu(user);
            break;
        case 4:
            std::cout << "Enter room name: ";
            std::cin >> roomName;
            user.createRoom(roomName);
            printServerMenu(user);
            break;
        case 5:
            std::cout << "Enter room name: ";
            std::cin >> roomName;
            user.joinRoom(roomName);
            printRoomMenu(user);
            break;
        case 6:
            user.logoutUser();
            user.disconnect();
            printIntroMenu(user);
            break;
    }
}

void Menu::printRoomMenu(User& user){
    std::cout << "1. Send a message" << std::endl;
    std::cout << "2. Receive messages" << std::endl;
    std::cout << "3. Leave the room" << std::endl;
    std::cout << "4. Delete the room" << std::endl;

    int option = getOption(1, 3);
    std::string message;
    switch(option){
        case 1:
            std::cout << "Enter your message: ";
            std::cin >> message;
            user.sentToRoom(message);
            printRoomMenu(user);
            break;
        case 2:
            user.receiveFromRoom();
            printRoomMenu(user);
            break;
        case 3:
            user.logoutUser();
            printServerMenu(user);
            break;
        case 4:
            user.deleteRoom();
            printServerMenu(user);
            break;
    }
}