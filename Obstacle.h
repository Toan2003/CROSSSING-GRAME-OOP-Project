#pragma once
#include <queue>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include "tool.h"
#include <time.h>

using namespace std;

#define leftToRight 0
#define rightToLeft 1

#define redLight -1
#define greenLight 1

#define borderGLx 5
#define borderGRx 112
#define borderGUy 1
#define borderGDy 41

#define heightOflane 5
#define car -1
#define truck 0
#define cat 1 
#define bus 2
#define spacelevel1 26
#define spacelevel2 19
#define spacelevel3 18
#define spacelevel4 17
#define spacelevel5 15

#define borderCLx 117
#define borderCRx 154
#define borderCUy 6
#define borderCDy 21

#define borderLevelUy 22
#define borderLevelDy 31

class Vehicle {
private:
    int x, y;
    int direction; //-1 left-to-right, 1 right-to-left
public:
    short type;
    short length;
    Vehicle(int , int);
    void setDirection(int direction);
    void setXY(int, int);
    int getX() const;
    int getY() const;
    void setX(int);
    void setY(int);
    void move();
    virtual void draw() =0;
};

class Car :public Vehicle {
private:
    int direction = leftToRight;
public:
    Car(int ,int);
    const string picture[4] =
    { "  ______     ",
      " /|_||_\\`.__ ",
      "(   _    _ _\\",
      "=`-(_)--(_)-'"};
    const short height = 4;
    const short length = 13;
    void draw();
};

class Truck : public Vehicle {
private:
    int direction = rightToLeft;
public:
    Truck(int, int);
    const string picture[4] =
    {"      ____        ",
     " ____//_]|________",
     "(o _ |  -|   _  o|",
     " `(_)-------(_)--'"};
    const short height = 4;
    const short length = 18;
    void draw();
};

class Cat : public Vehicle {
private:
    int direction = leftToRight;
public:
    Cat(int, int);
    const string picture[4] =
    {"\\    /\\ ",
     " )  ( ')",
     " ( /  ) ",
     " \(__)| "};
    const short height = 4;
    const short length = 8;
    void draw();
};

class Bus : public Vehicle {
private:
    int direction = rightToLeft;
public:
    Bus(int, int);
    int returnType();
    const string picture[4] =
    {  "   _____________     ",
       " _/_|[][][][][] | - -",
       "(      City Bus | - -",
       "=--OO-------OO--=dwb "};
    const short height = 4;
    const short length = 21;
    void draw();
};

class trafficLight {
private:
    int y;
    bool isRed;
    int order;
public:
    trafficLight();
    void setY(int);
    void setRedOn();
    void setGreenOn();
    void setOrder(int);
    bool isRedLight();
    void draw();
};

class lane {
private:
    int level;
    int order;
    deque <Vehicle*> point;
    int direction;
    trafficLight light;
    int countTimeForRedLight;
public:
    // (level, order, direction)
    const int time[5] = { 100,70,70,45,30 };
    lane(int, int, int );
    bool isRedOn();
    void updateLane();
    void drawVehicle();
    void drawLight();
    void setTrafficLight(bool);
    Vehicle* returnEachVehicle(const int&);
    virtual ~lane();
};


