#include "client.h"

int main(){
    Menu menu;
    std::cout << "Welcome to the chatroom!" << std::endl;
    User user;
    menu.printIntroMenu(user);
    std::cout << "Good Bye!" << std::endl;
    return 0;
}