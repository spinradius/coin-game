#include <iostream>
#include "game.hpp"

int main() {
    Game game;

    // Initialize the game
    if (!game.initialize()) {
        std::cerr << "Failed to initialize the game." << std::endl;
        return -1;
    }

    // Main game loop
    while (game.isRunning()) {
        game.handleInput();
        game.update();
        game.render();
    }

    // Clean up and exit
    game.cleanup();
    return 0;
}