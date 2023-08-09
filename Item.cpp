#include "Item.h"

Item::Item() {
    _name = "NULL";
    _price = 0;
    _quantity = 0;
    _serialNo = 0;
}

Item::Item(string name, int price, int quantity, int serial) {
    _name = name;
    _price = price;
    _quantity = quantity;
    _serialNo = serial;
}

void Item::changeSerialNo() {
    _serialNo--;
}


void Item::print() {
    cout << _serialNo << ". " << _name << " x " << _quantity << endl << "   Unit Price: " << _price << endl << endl;
}
