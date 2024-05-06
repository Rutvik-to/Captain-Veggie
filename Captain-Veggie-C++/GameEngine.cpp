#include "GameEngine.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

GameEngine::GameEngine() {} // Empty constructor

GameEngine::~GameEngine() { // Destructor
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      delete field[i][j];
    }
    delete[] field[i];
  }
  delete[] field;
  for (Veggie* veggie : possibleVeggies) {
    delete veggie;
  }
  for (Rabbit* rabbit : rabbits) {
    delete rabbit;
  }
  delete captain;
}

// Function defination for initialiseGame()
void GameEngine::initializeGame() {
  initVeggies();
  initCaptain();
  score = 0;
  timer = 0;
}

// Function defination for initVeggies()
void GameEngine::initVeggies() {
  string filename;
  bool fileExists = false;
  // Ask the user for the name of the input file
  while (!fileExists) {
    cout << "Please enter the name of the vegetable point file: ";
    cin >> filename;
    ifstream infile(filename);

    // open the file and parse the contents like height and width
    if (infile.is_open()) {
      fileExists = true;
      string Size;
      string Height;
      string Width;

      getline(infile,Size,',');
      getline(infile,Height,',');
      getline(infile,Width);

      height = stoi(Height);
      width = stoi(Width) * 3;

      string veggie;
      string name;
      string symbol;
      string Points;
      int points;

      // Parse till the end for points of all possible vegetables
      while (infile.eof() != 1) {
      
          getline(infile,name,',');
          getline(infile,symbol,',');
          getline(infile,Points);
          points = stoi(Points);
          possibleVeggies.push_back(new Veggie(name, symbol, points));
      }

      // Close the file
      infile.close();
    } else {
      cout << filename <<" does not exist! ";
    }
  }

field = new FieldInhabitant**[height]; // Allocate array of pointers to pointers for field

for (int i = 0; i < height; ++i) {
  field[i] = new FieldInhabitant*[width]; // Allocate array of pointers for each row for field
  for (int j = 0; j < width; ++j) {
    field[i][j] = nullptr; // Initialize each element in the row to nullptr in field
  }
}

  srand(time(0)); // Seed random number generator

  // fill the field with random vegetables
  for (int i = 0; i < NUMBEROFVEGGIES; ++i) {
    int x, y;
    do {
      x = rand() % width;
      y = rand() % height;
    } while (field[y][x] != nullptr);
    field[y][x] = new Veggie(*possibleVeggies[rand() % possibleVeggies.size()]);
  }
}

// function defination for initCaptain
void GameEngine::initCaptain() {
  int x, y;

  // generate a random empty coordinates in field and assign them to the captain
  do {
    x = rand() % width;
    y = rand() % height;
  } while (field[y][x] != nullptr);
  captain = new Captain(x, y);
  field[y][x] = captain;
}

// function defination for spawnRabbits
void GameEngine::spawnRabbits() {
  if (rabbits.size() < NUMBEROFRABBITS) {
    int x, y;
    // generate a random empty coordinates in field and assign them to the rabbit
    do {
      x = rand() % width;
      y = rand() % height;
    } while (field[y][x] != nullptr);
    auto R = new Rabbit(x, y);
    rabbits.push_back(R);
    field[y][x] = R;
    cout << "Oh no! Here comes another rabbit!\n" << endl;
  }
}

//function defination for timerTick
void GameEngine::timerTick(){
  if(timer == 0 || (timer % 5) == 0){
    spawnRabbits();
  }
  timer++;
}

//function defination for remainingVeggies
int GameEngine::remainingVeggies() {
  int count = 0;
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      if (field[i][j] != nullptr && dynamic_cast<Veggie*>(field[i][j])) {
        count++;
      }
    }
  }
  return count;
}

//function defination for intro
void GameEngine::intro() {
  cout << "Welcome to Captain Veggie!" << endl;

  // Explain the game's goal
  cout << "The rabbits are invading your garden and you must harvest" << endl;
  cout << "as many vegetables as possible before the rabbits eat them" << endl;
  cout << "all! Each vegetable is worth a different number of points" << endl;
  cout << "so go for the high score! \n" << endl;
  
  // Present the list of vegetables
  cout << "The vegetables are: " << endl;
  for (Veggie* veggie : possibleVeggies) {
    // Format output for better readability
    cout << veggie->getSymbol() << ": " << veggie->getName() << ", " << veggie->getPoints() << endl;
  }

  // Explain Captain Veggie and rabbit symbols
  cout << "\nCaptain Veggie is " << captain->getSymbol() << ", and the rabbits are R's." << endl;
  cout << "\nCatching a rabbit is worth 5 points, but more are" << endl;
  cout << "always on the way!" << endl;
  cout << "\nGood Luck!" << endl;
}

// Function defination moveCptVertical
void GameEngine::moveCptVertical(int movement) {
  int newY = captain->getY() + movement;

  // Check if the move is within field boundaries
  if (newY >= 0 && newY < height) {
    // Check if the new location is empty
    if (field[newY][captain->getX()] == nullptr) {
      // Update Captain's location in the field
      field[captain->getY()][captain->getX()] = nullptr;
      captain->setY(newY);
      field[newY][captain->getX()] = captain;

    } else if (dynamic_cast<Veggie*>(field[newY][captain->getX()])) {
      // Captain found a veggie
      Veggie* veggie = dynamic_cast<Veggie*>(field[newY][captain->getX()]);
      cout << "Yummy! A delicious " << veggie->getName() << "!\n" << endl;
      captain->addVeggie(veggie);
      score += veggie->getPoints();

      // Update Captain's location and remove veggie from field
      field[captain->getY()][captain->getX()] = nullptr;
      captain->setY(newY);
      field[newY][captain->getX()] = captain;
      delete veggie; // Deallocate memory for collected veggie

    } else if(dynamic_cast<Rabbit*>(field[newY][captain->getX()])) {
      Rabbit* rabbit = dynamic_cast<Rabbit*>(field[newY][captain->getX()]);
      score += RABBITPOINTS;

      // Update Captain's location and remove rabbit from field
      field[captain->getY()][captain->getX()] = nullptr;
      captain->setY(newY);
      field[newY][captain->getX()] = captain;

      for (auto it = rabbits.begin(); it != rabbits.end(); ++it) {
        if (*it == rabbit) {
          rabbits.erase(it);
          break;
        }
      }

      delete rabbit; // Deallocate memory for collected veggie

      cout << "Finally got one of those pesky bunnies!\n";
    }
  } else {
    // Captain cannot move outside the field
    cout << "You cannot move that way.\n";
  }
}

// Function defination moveCptHorizontal
void GameEngine::moveCptHorizontal(int movement) {
  int newX = captain->getX() + movement;

  // Check if the move is within field boundaries
  if (newX >= 0 && newX < width) {
    // Check if the new location is empty
    if (field[captain->getY()][newX] == nullptr) {
      // Update Captain's location in the field
      field[captain->getY()][captain->getX()] = nullptr;
      captain->setX(newX);
      field[captain->getY()][newX] = captain;
    } else if (dynamic_cast<Veggie*>(field[captain->getY()][newX])) {
      // Captain found a veggie
      Veggie* veggie = dynamic_cast<Veggie*>(field[captain->getY()][newX]);
      cout << "You found a delicious " << veggie->getName() << "!\n" << endl;
      captain->addVeggie(veggie);
      score += veggie->getPoints();

      // Update Captain's location and remove veggie from field
      field[captain->getY()][captain->getX()] = nullptr;
      captain->setX(newX);
      field[captain->getY()][newX] = captain;
      delete veggie; // Deallocate memory for collected veggie

    } else if(dynamic_cast<Rabbit*>(field[captain->getY()][newX])) {
      Rabbit* rabbit = dynamic_cast<Rabbit*>(field[captain->getY()][newX]);
      score += RABBITPOINTS;

      // Update Captain's location and remove veggie from field
      field[captain->getY()][captain->getX()] = nullptr;
      captain->setX(newX);
      field[captain->getY()][newX] = captain;

      for (auto it = rabbits.begin(); it != rabbits.end(); ++it) {
        if (*it == rabbit) {
          rabbits.erase(it);
          break;
        }
      }

      delete rabbit; // Deallocate memory for collected veggie

      cout << "Finally got one of those pesky bunnies!\n";
    }
  } else {
    // Captain cannot move outside the field
    cout << "You cannot move that way.\n";
  }
}

void GameEngine::printField() {
  // Print top border
  for (int i = 0; i < width + 2; ++i) {
    cout << "#";
  }
  cout << "\n";

  // Print each row of the field
  for (int i = 0; i < height; ++i) {
    cout << "#";
    for (int j = 0; j < width; ++j) {
      if (field[i][j] == nullptr) {
        cout << " ";
      } else {
        cout << field[i][j]->getSymbol();
      }
    }
    cout << "#\n";
  }

  // Print bottom border
  for (int i = 0; i < width + 2; ++i) {
    cout << "#";
  }
  cout << "\n";
}

// Function defination moveRabbits
void GameEngine::moveRabbits() {
  for (Rabbit* rabbit : rabbits) {
    int moveX = rand() % 3 - 1; // Generate random movement (-1, 0, 1)
    int moveY = rand() % 3 - 1;

    int newX = rabbit->getX() + moveX;
    int newY = rabbit->getY() + moveY;

    // Check if the move is within field boundaries
    if (newX >= 0 && newX < width && newY >= 0 && newY < height) {
      // Check if the new location is empty or has a veggie
      if (field[newY][newX] == nullptr || dynamic_cast<Veggie*>(field[newY][newX])) {
        // Update Rabbit's location in the field
        field[rabbit->getY()][rabbit->getX()] = nullptr;
        rabbit->setX(newX);
        rabbit->setY(newY);
        field[newY][newX] = rabbit;
      }
    }
  }
}

// Function defination moveCaptain
void GameEngine::moveCaptain() {
  char input;
  string Choice;
  cout << "Would you like to move up(W), down(S), left(A), or right(D):";
  cin >> Choice;
  cout << endl;

  if(Choice.length() == 1){

    input = Choice[0];

    switch (toupper(input)) {
    case 'W':
      moveCptVertical(-1);
      break;
    case 'A':
      moveCptHorizontal(-1);
      break;
    case 'S':
      moveCptVertical(1);
      break;
    case 'D':
      moveCptHorizontal(1);
      break;
  }
  }
  else{
    cout << Choice <<" is not a valid option!"<< endl;
  }
}

// Function defination gameOver
void GameEngine::gameOver() {
  cout << endl;
  printField();
  cout << "GAME OVER!\n";
  cout << "You managed to harvest the following vegetables:\n";
  for (Veggie* veggie : captain->getVeggies()) {
    cout << veggie->getName() << "\n";
  }
  cout << "Your score was: " << score << "\n";
}

// Function defination getScore
int GameEngine::getScore(){
    return score;
}