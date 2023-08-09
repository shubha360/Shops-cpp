#include "../include/Player.h"

Player::Player() {
    _money = -1;
    _serialNo = -1;
}

Player::Player(int money) {
    _money = money;
    _serialNo = 1;
}

void Player::addItem(string name, int price, int quantity) {
    _inventory.push_back(Item(name, price, quantity, _serialNo));
    _serialNo++;
}

Item& Player::getItem(int serialNo) {
    for (list<Item>::iterator it = _inventory.begin(); it != _inventory.end(); it++) {
        if ((*it).getSerialNo() == serialNo) {
            return (*it);
        }
    }
}

void Player::buyItem(Item& item) {
    bool found = false;

    for (list<Item>::iterator it = _inventory.begin(); it != _inventory.end(); it++) {
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
}

Item Player::sellItem(int serialNo) {
    Item returnItem;
    bool erased = false;

    for (list<Item>::iterator it = _inventory.begin(); it != _inventory.end(); it++) {
        if (erased) {
            (*it).changeSerialNo();
        } else {
            if ((*it).getSerialNo() == serialNo) {
                returnItem = (*it);
                _money += (*it).getPrice();

                if ((*it).getQuantity() == 1) {
                    it = _inventory.erase(it);
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

void Player::printInventory() {
    cout << "Your inventory:" << endl << endl;
    cout << "Money: " << _money << endl << endl;

    for (list<Item>::iterator it = _inventory.begin(); it != _inventory.end(); it++) {
        (*it).print();
    }
    cout << endl;
}
