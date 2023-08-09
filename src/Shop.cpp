#include "../include/Shop.h"

Shop::Shop(string name, int money) {
    _name = name;
    _money = money;
    _serialNo = 1;
}

void Shop::addItem(string name, int price, int quantity) {
    _itemList.push_back(Item(name, price, quantity, _serialNo));
    _serialNo++;
}

Item& Shop::getItem(int serialNo) {
    for (list<Item>::iterator it = _itemList.begin(); it != _itemList.end(); it++) {
        if ((*it).getSerialNo() == serialNo) {
            return (*it);
        }
    }
}

bool Shop::buyItem(Item& item) {
    bool found = false;

    for (list<Item>::iterator it = _itemList.begin(); it != _itemList.end(); it++) {
        if ((*it).getName() == item.getName()) {
            (*it).setQuantity((*it).getQuantity() + 1);
            found = true;
            break;
        }
    }

    if (!found) {
        addItem(item.getName(), item.getPrice(), 1);
    }
    _money -= item.getPrice();
    return true;
}

Item Shop::sellItem(int serialNo) {
    Item returnItem;
    bool erased = false;

    for (list<Item>::iterator it = _itemList.begin(); it != _itemList.end(); it++) {
        if (erased) {
            (*it).changeSerialNo();
        } else {
            if ((*it).getSerialNo() == serialNo) {
                returnItem = (*it);
                _money += (*it).getPrice();

                if ((*it).getQuantity() == 1) {
                    it = _itemList.erase(it);
                    erased = true;
                    // it--;
                    (*it).changeSerialNo();
                    _serialNo--;
                }
                else {
                    (*it).setQuantity((*it).getQuantity() - 1);
                }
            }
        }
    }
    return returnItem;
}

void Shop::printShop() {
    cout << _name << endl << endl;
    cout << "Money: " << _money << endl << endl;

    for (list<Item>::iterator it = _itemList.begin(); it != _itemList.end(); it++) {
        (*it).print();
    }
    cout << endl;
}
