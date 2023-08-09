#ifndef MAINMANAGER_H
#define MAINMANAGER_H

#include <vector>
#include <conio.h>
#include <fstream>
#include <sstream>

#include "Shop.h"
#include "Player.h"

class MainManager
{
    public:
        MainManager();
        bool init(string shopFileLocation, string playerFileLocation);
        void start();
        void close(string shopFileLocation, string playerFileLocation);

    private:
        vector<Shop> shopList;
        Player player;

        bool loadShops(string filePath);
        bool loadPlayer(string filePath);
        bool saveShops(string filePath);
        bool savePlayer(string filePath);

        void printShops();
        void inputError();
};

#endif // MAINMANAGER_H
