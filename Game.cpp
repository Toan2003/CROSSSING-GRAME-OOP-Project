#include "Game.h"

Game::gameRepair(int level, string player) {
    this->player = player;
    player = "unknown";
    this->level = level;
    if (level == 1) {
        lane *a = new lane(level, 1, leftToRight);
        lane *b = new lane(level, 3, rightToLeft);
        lane *c = new lane(level, 5, leftToRight);
        lane *d = new lane(level, 7, rightToLeft);
        list.push_back(a);
        list.push_back(b);
        list.push_back(c);
        list.push_back(d);
        speed = 500;
    }
    else if (level == 2) {
        lane *a = new lane(level, 1, leftToRight);
        lane *b = new lane(level, 2, rightToLeft);
        lane *c = new lane(level, 4, leftToRight);
        lane *d = new lane(level, 5, rightToLeft);
        lane *e = new lane(level, 7, leftToRight);
        list.push_back(a);
        list.push_back(b);
        list.push_back(c);
        list.push_back(d);
        list.push_back(e);
        speed = 400;
    }
    else if (level == 3) {
        lane *a = new lane(level, 1, leftToRight);
        lane *b = new lane(level, 2, rightToLeft);
        lane *c = new lane(level, 3, rightToLeft);
        lane *d = new lane(level, 5, leftToRight);
        lane *e = new lane(level, 6, leftToRight);
        lane *f = new lane(level, 7, rightToLeft);
        list.push_back(a);
        list.push_back(b);
        list.push_back(c);
        list.push_back(d);
        list.push_back(e);
        list.push_back(f);
        speed = 300;
    }
    else if (level == 4) {
        lane *a = new lane(level, 1, leftToRight);
        lane *b = new lane(level, 2, rightToLeft);
        lane *c = new lane(level, 3, leftToRight);
        lane *d = new lane(level, 5, rightToLeft);
        lane *e = new lane(level, 6, leftToRight);
        lane *f = new lane(level, 7, rightToLeft);
        list.push_back(a);
        list.push_back(b);
        list.push_back(c);
        list.push_back(d);
        list.push_back(e);
        list.push_back(f);
        speed = 200;
    }
    else if (level == 5) {
        lane *a = new lane(level, 1, leftToRight);
        lane *b = new lane(level, 2, rightToLeft);
        lane *c = new lane(level, 3, leftToRight);
        lane *d = new lane(level, 4, rightToLeft);
        lane *e = new lane(level, 5, leftToRight);
        lane *f = new lane(level, 6, rightToLeft);
        lane *h = new lane(level, 7, leftToRight);
        speed = 100;
    }
    people = new CPEOPLE;
}

Game::~Game() {
    while (!list.empty()) {
        lane* temp = list.back();
        list.pop_back();
        delete temp;
    }
}

void Game::gamePlay() {
    while (!people->isFinish()) {
        for (int i = 0; i < list.size(); i++) {
            list[i]->play();
        }
        people->update();
        people->assignChar();
       
        this_thread::sleep_for(chrono::nanoseconds(5000000));
    }
}