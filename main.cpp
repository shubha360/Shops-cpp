#include "MainManager.h"

int main() {
    MainManager manager;

    if (manager.init("", "player.txt")) // pass default files then immidietly close the program with 0 reset items.
    {
        manager.start();
        manager.close("", "player.txt"); // never change this line
    }
    return 0;
}
