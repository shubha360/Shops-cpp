#include "MainManager.h"

MainManager::MainManager() {}

bool MainManager::init(string shopFileLocation, string playerFileLocation) {
    return loadShops(shopFileLocation) && loadPlayer(playerFileLocation);
}

void MainManager::close(string shopFileLocation, string playerFileLocation) {
    if (!saveShops(shopFileLocation)) {
        cout << "Error saving shops!\n\n";
    }

    if (!savePlayer(playerFileLocation)) {
        cout << "Error saving player!\n\n";
    }
}

void MainManager::start() {
    bool mainLoop = true;

    do {
        printShops();
        cout << "Which shop do you want to enter? Enter 0 to quit. <1-3>: ";

        int shopInput = _getch() - 48;
        cout << shopInput;
        cout << endl << endl;

        switch (shopInput) {
            case 0:
                mainLoop = false;
                break;

            case 1:
            case 2:
            case 3: {
                Shop& currentShop = shopList[shopInput - 1];
                bool insideShop = true;

                do {
                    cout << endl << endl;
                    currentShop.printShop();
                    player.printInventory();

                    cout << "Would you like to buy or sell an item? Enter 0 to visit another shop. B/S: ";

                    char buySell = _getch();
                    cout << buySell;
                    cout << endl << endl;

                    switch (buySell) {
                        case '0':
                            insideShop = false;
                            break;

                        case 'b':
                        case 'B': {
                            cout << "Please enter the serial number of the item you want to buy: ";

                            int buySerialNo = _getch() - 48;
                            cout << buySerialNo;
                            cout << endl << endl;

                            if (buySerialNo < 1 || buySerialNo >= currentShop.getSerialNo()) {
                                inputError();
                            }
                            else {
                                int buyItemPrice = currentShop.getItem(buySerialNo).getPrice();

                                if (buyItemPrice > player.getMoney()) {
                                    cout << "Not enough money available to buy this item!\n\n";
                                }
                                else {
                                    Item buyItem = currentShop.sellItem(buySerialNo);
                                    player.buyItem(buyItem);
                                }
                            }
                            break;
                        }

                        case 's':
                        case 'S': {
                            cout << "Please enter the serial number of the item you want to sell: ";

                            int sellSerialNo = _getch() - 48;
                            cout << sellSerialNo;
                            cout << endl << endl;

                            if (sellSerialNo < 1 || sellSerialNo >= player.getSerialNo()) {
                                inputError();
                            }
                            else {
                                int sellItemPrice = player.getItem(sellSerialNo).getPrice();

                                if (sellItemPrice > currentShop.getMoney()) {
                                    cout << "Not enough money available to buy this item!\n\n";
                                }
                                else {
                                    Item sellItem = player.sellItem(sellSerialNo);
                                    currentShop.buyItem(sellItem);
                                }
                            }
                            break;
                        }

                        default: {
                            inputError();
                            break;
                        }
                    }
                } while (insideShop);

                break;
            }

            default: {
                    inputError();
                    break;
                }
        }
    } while (mainLoop);

    cout << "Bye!\n";
}

bool MainManager::loadShops(string filePath) {
    bool success = true;

    shopList.push_back(Shop("Animal Shop", 1425));
    shopList.back().addItem("Crocodile", 300, 3);
    shopList.back().addItem("Gorilla", 210, 5);
    shopList.back().addItem("Goat", 125, 8);
    shopList.back().addItem("Donkey", 140, 4);
    shopList.back().addItem("Hippopotamus", 250, 2);
    shopList.back().addItem("Ostrich", 165, 4);
    shopList.back().addItem("Rooster", 35, 16);

    shopList.push_back(Shop("Fruit Shop", 980));
    shopList.back().addItem("Jack Fruit", 120, 7);
    shopList.back().addItem("Pineapple", 75, 6);
    shopList.back().addItem("Watermelon", 95, 4);
    shopList.back().addItem("Mango", 40, 13);
    shopList.back().addItem("Apple", 25, 27);
    shopList.back().addItem("Guava", 20, 19);

    shopList.push_back(Shop("Magic Shop", 3700));
    shopList.back().addItem("10 min Invincibility", 3400, 3);
    shopList.back().addItem("10 min Super Speed", 1350, 6);
    shopList.back().addItem("10 min Super Strength", 2400, 4);
    shopList.back().addItem("10 min Fly", 1750, 11);
    shopList.back().addItem("5 min Immorality", 4500, 1);

    return success;
}

bool MainManager::loadPlayer(string filePath) {
    ifstream playerLoader;
    playerLoader.open(filePath);

    if (playerLoader.fail()) {
        perror(filePath.c_str());
        return false;
    }

    int intInput;
    playerLoader >> intInput;
    player = Player(intInput);

    string strInput;
    getline(playerLoader, strInput);

    while (getline(playerLoader, strInput)) {
        string itemName;
        getline(playerLoader, itemName);

        int price;
        playerLoader >> price;

        int quantity;
        playerLoader >> quantity;

        player.addItem(itemName, price, quantity);
        getline(playerLoader, strInput);
    }

    /*
    player.addItem("10 min Fly", 1750, 1);
    player.addItem("10 min Super Speed", 1350, 1);
    player.addItem("Goat", 125, 1);
    player.addItem("Rooster", 35, 6);
    player.addItem("Crocodile", 300, 1);
    player.addItem("Guava", 20, 4);
    player.addItem("Pineapple", 75, 1);
    player.addItem("Mango", 40, 3);
    */

    return true;
}

bool MainManager::saveShops(string filePath) {
    return true;
}

bool MainManager::savePlayer(string filePath) {
    ofstream playerSaver;
    playerSaver.open(filePath);

    if (playerSaver.fail()) {
        perror(filePath.c_str());
        return false;
    }

    playerSaver << player.getMoney() << endl << endl;

    for (int i = 1; i < player.getSerialNo(); i++) {
        Item currentItem = player.getItem(i);
        stringstream itemStr;
        itemStr << currentItem.getName() << endl << currentItem.getPrice() << endl << currentItem.getQuantity();

        if (i < player.getSerialNo() - 1) {
            itemStr << endl << endl;
        }
        playerSaver << itemStr.str();
    }

    return true;
}

void MainManager::printShops() {
    for (unsigned int i = 0; i < shopList.size(); i++) {
        cout << (i + 1) << ". " << shopList[i].getName() << endl;
    }
    cout << endl;
}

void MainManager::inputError() {
    cout << "Unrecognized input!\n\n";
}
