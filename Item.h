#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <list>

using namespace std;

class Item {
    public:
        Item();
        Item(string name, int price, int quantity, int serial);
        void print();

        string getName() { return _name; };
        int getPrice() { return _price; };
        int getQuantity() { return _quantity; };
        int getSerialNo() { return _serialNo; };

        void setQuantity(int quantity) { _quantity = quantity; }
        void changeSerialNo();

    private:
        string _name;
        int _price;
        int _quantity;
        int _serialNo;
};

#endif // ITEM_H
