#include "GameEngine.h"
#include <iostream>

int main() {
  // Instantiate a GameEngine object
  GameEngine gameEngine;

  // Initialize the game
  gameEngine.initializeGame();

  // Print field
  gameEngine.printField();

  // Display game introduction
  gameEngine.intro();

  // Number of remaining vegetables
  int remainingVeggies = gameEngine.remainingVeggies();

  // Game loop continues while there are vegetables remaining
  while (remainingVeggies > 0) {
    // Display remaining vegetables and score
    cout << remainingVeggies << " veggies remaining. Current score: " << gameEngine.getScore() << endl;

    // Print the game field
    gameEngine.printField();

    // Move the rabbits
    gameEngine.moveRabbits();

    // Move the captain
    gameEngine.moveCaptain();

    // Update remaining vegetables after captain's move
    remainingVeggies = gameEngine.remainingVeggies();

    gameEngine.timerTick();
  }

  // Display game over information
  gameEngine.gameOver();

  return 0;
}
