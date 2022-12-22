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

#define borderGLx 3
#define borderGRx 133
#define borderGUy 1
#define borderGDy 46

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

#define borderCLx 139
#define borderCRx 178

#define green 0;
#define red 1;

class Vehicle {
private:
    int x, y;
    int direction; //-1 left-to-right, 1 right-to-left
    int trafficLight; //-1:red-stop, 0:yellow-slow(sleep(40)), 1:green-fast(sleep(40))
public:
    int space;
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
    const int height = 4;
    const int length = 13;
    //const int length[4] = { int(picture[0].length()), int(picture[1].length()), int(picture[2].length()), int(picture[3].length()) };
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
    const int height = 4;
    const int length = 18;
    //const int length[4] = { int(picture[0].length()), int(picture[1].length()), int(picture[2].length()), int(picture[3].length()) };
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
    const int height = 4;
    const int length = 8;
    //const int length[4] = { int(picture[0].length()), int(picture[1].length()), int(picture[2].length()), int(picture[3].length()) };
    void draw();
};

class Bus : public Vehicle {
private:
    int direction = rightToLeft;
public:
    Bus(int, int);
    const string picture[4] =
    {  "   _____________     ",
       " _/_|[][][][][] | - -",
       "(      City Bus | - -",
       "=--OO-------OO--=dwb "};
    const int height = 4;
    const int length = 21;
    //const int length[4] = { int(picture[0].length()), int(picture[1].length()), int(picture[2].length()), int(picture[3].length()) };
    void draw();
};

class trafficLight {
private:
    const short timeRedOn = 3;
    int y;
    bool isRed;
    time_t begin;
    time_t end;
public:
    trafficLight();
    void setY(int y);
    void draw();
    void turnOff();
    bool getTrafficLife();
    void setRedOn();
};


class lane {
private:
    int order;
    int level;
    deque <Vehicle*> point;
    int direction;
    trafficLight light;
public:
    // (level, order, direction)
    lane();
    lane(int , int, int );
    void play();
    ~lane();
};


