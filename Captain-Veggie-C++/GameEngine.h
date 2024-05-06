#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>
#include "FieldInhabitant.h" 
#include "Veggie.h"           
#include "Rabbit.h"           
#include "Captain.h"

class GameEngine {
private:
  FieldInhabitant*** field;
  int width;
  int height;
  int score;
  int timer;
  static const int NUMBEROFVEGGIES = 30;
  static const int NUMBEROFRABBITS = 5;
  static const int RABBITPOINTS = 5;
  Captain* captain;
  vector<Rabbit*> rabbits;
  vector<Veggie*> possibleVeggies;

  void initVeggies();
  void initCaptain();
  void spawnRabbits();

  void moveCptVertical(int movement);
  void moveCptHorizontal(int movement);

public:
  void initializeGame();
  void intro();
  void printField();
  void moveRabbits();
  void moveCaptain();
  int getScore();
  int remainingVeggies();
  void gameOver();
  void timerTick();

  GameEngine();
  ~GameEngine();

};

#endif
