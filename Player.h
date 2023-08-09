#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"

class Player {
    public:
        Player();
        Player(int money);
        void addItem(string name, int price, int quantity);
        Item& getItem(int serialNo);
        void buyItem(Item& item);
        Item sellItem(int serialNo);

        void printInventory();

        int getSerialNo() { return _serialNo; };
        int getMoney() { return _money; };

    private:
        int _money;
        int _serialNo;
        list<Item> _inventory;
};

#endif // PLAYER_H
