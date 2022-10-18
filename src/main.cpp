#include <iostream>
#include <ctime>
#include "MinesweeperBoard.h"

int main() {
    srand(time(0));
    MinesweeperBoard w(6,6,GameMode::EASY);
    MsBoardTextView view{w};
    MsTextController Gramy{w,view};
    Gramy.play();

    return 0;
}

