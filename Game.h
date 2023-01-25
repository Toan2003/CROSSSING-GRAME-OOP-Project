#pragma once

#include <fstream>
#include <thread>
#include <chrono>
#include <vector>
#include "Obstacle.h"
#include "People.h"
#include "tool.h"
using namespace std;

//Function for console

#define levelWin 5

class Game {
private:
    string player;
    int level;
    int speed;
    CPEOPLE* people;
    vector<lane*> list;
public:
    static bool IS_WINNING;
    bool LOSE_BOARD = false;
    bool IS_RUNNING = true;
    CPEOPLE* getPeople();
    string getName();
    int getSpeed();
    int getLevel();
    void setPlayer(string);
    void setSpeed(int);
    void gameRepair(int, string);
    bool isImpact();
    void deathAnimation();
    void updateLane();
    void updatePeople(char MOVING);
    void drawLight();
    void drawGame();

    void gamePlay();
    void pause(thread&);
    void resume(thread&);
    void newGame();
    void save();

    void deleteSource();
    ~Game();
};


void drawGameBoard();
void drawCharacterBoard(int level, string name);
void drawInstructorBoard();

void draw(int i, int j, int x, int y, string s[6]);
void drawWin(int x, int y);