#include "include/MainManager.h"

int main() {
    MainManager manager;

    if (manager.init("files/shops.txt", "files/player.txt")) // pass default files then immediately close the program with 0 reset items.
    {
        manager.start();
        manager.close("files/shops.txt", "files/player.txt"); // never change this line
    }
    return 0;
}
