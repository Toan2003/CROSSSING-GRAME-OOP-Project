#pragma once

#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include "Obstacle.h"
#include "People.h"
using namespace std;

//Function for console

class Game {
private:
    string player;
    int level;
    int speed;
    CPEOPLE* people;
    vector<lane*> list;
public:
    Game(int level, string player);
    ~Game();
    CPEOPLE* returnPeople() {
        return people;
    };
    void gamePlay();
    void startGame();
    void endGame();
    void loadGame(ifstream);
    void saveGame(ifstream);
    void pauseGame(HANDLE);
    void resumeGame(HANDLE);
};

