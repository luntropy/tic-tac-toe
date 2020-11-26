#include <iostream>

#include <random>

#include "Game.h"

int main() {
    srand(time(NULL));
    Game game;

    game.play();

    return 0;
}
