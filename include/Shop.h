#ifndef SHOP_H
#define SHOP_H

#include "Item.h"

class Shop {
    public:
        Shop(string name, int money);
        void addItem(string name, int price, int quantity);
        Item& getItem(int serialNo);
        bool buyItem(Item& item);
        Item sellItem(int serialNo);

        void printShop();

        string getName() { return _name; };
        int getSerialNo() { return _serialNo; };
        int getMoney() { return _money; };

    private:
        string _name;
        int _money;
        int _serialNo;
        list<Item> _itemList;
};

#endif // SHOP_H
