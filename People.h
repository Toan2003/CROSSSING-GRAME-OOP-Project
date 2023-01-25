#pragma once
#include "Obstacle.h"
#include <conio.h>
#include<string>
#include <iostream>
#include<Windows.h>
#include<fstream>
#include <thread>
#include <stdlib.h>
#include <time.h>

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80
#define ENTER     13

using namespace std;

class CPEOPLE
{
private:
    int mX, mY;
    bool mState;
    char c;
public:
    CPEOPLE();
    void Up();
    void Left();
    void Right();
    void Down();
    bool isImpact(Vehicle*&, int);
    bool isFinish();
    bool isDead();
    void move();
    void draw();
    void clearPeople();
    int getMX();
    int getMY();
    void assignMY(int);
    void update();
    void nhanbanphim(char);
};
