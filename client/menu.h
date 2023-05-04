#ifndef MENU_H
#define MENU_H

#include "user.h"


class Menu{
    public:
    int getOption(int min, int max);
    void printIntroMenu(User& user);
    void printEnterMenu(User& user);
    void printServerMenu(User& user);
    void printRoomMenu(User& user);

};

#endif