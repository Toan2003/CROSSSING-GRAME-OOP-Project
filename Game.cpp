#include "Game.h"

void Game::gameRepair(int level, string player) {
    if (player == "") {
        this->player = "unknown";
    }
    else {
        this->player = player;
    }
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
        speed = 500000;
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
        speed = 5000000;
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
        speed = 5000000;
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
        speed = 50000;
    }
    else if (level == 5) {
        lane *a = new lane(level, 1, leftToRight);
        lane *b = new lane(level, 2, rightToLeft);
        lane *c = new lane(level, 3, leftToRight);
        lane *d = new lane(level, 4, rightToLeft);
        lane *e = new lane(level, 5, leftToRight);
        lane *f = new lane(level, 6, rightToLeft);
        lane *h = new lane(level, 7, leftToRight);
        list.push_back(a);
        list.push_back(b);
        list.push_back(c);
        list.push_back(d);
        list.push_back(e);
        list.push_back(f);
        list.push_back(h);
        speed = 5;
    }
    people = new CPEOPLE;
}


void Game::gamePlay() {
    while (!people->isFinish()) {
        for (int i = 0; i < list.size(); i++) {
            list[i]->play();
        }
        people->update();
        people->assignChar();
       
        //this_thread::sleep_for(chrono::nanoseconds(1));
    }
}

void Game::deleteSource() {
    delete people;
    lane* temp;
    while (!list.empty()) {
        temp = list.back();
        list.pop_back();
        delete temp;
    }
}

Game::~Game() {
    Game::deleteSource();
}

void Game::deathAnimation() {
    //    for (int i = 0; i < list.size(); i++)
    //        list[i]->erase();

    int UFOx = people->getMX() - 7; // ve ufo, ham ve lay cua verhicle
    int UFOy = 2;
    const int height = 5;
    const int length = 17;
    const string picture[5] =
    { "       ___       ",
     "   ___/UFO\\___   ",
     "  /   '---'   \\  ",
     " /'--_______--'\\ ",
     "/   /       \\   \\" };

    for (int i = borderGLx + 1; i < borderGRx; i++) // xoa duong ke ngang + xe 
        for (int j = borderGUy + 1; j < borderGDy; j++)
        {
            gotoXY(i, j);
            cout << " ";
        }

    for (int i = 0; i < height; i++) { // ve ufo
        for (int j = 0; j < picture[i].length(); j++) {
            if ((UFOx + j) <= borderGLx || (UFOx + j) >= borderGRx) continue;
            gotoXY(UFOx + j, UFOy + i);
            cout << picture[i][j];
        }
        cout << endl;
        if (UFOx - 1 <= borderGLx || UFOx - 1 >= borderGRx) continue;
        gotoXY(UFOx - 1, UFOy + i);
        cout << " ";
    }

    int x = people->getMX(); // lay toa do nguoi
    int y = people->getMY();
    if (x == 4)
        x = 5;
    if (x == 130)
        x = 129;
    while (y > 1) { // cho nguoi bay len
        gotoXY(x - 1, y);
        cout << "     ";
        gotoXY(x - 1, y + 1);
        cout << "     ";
        gotoXY(x - 1, y + 2);
        cout << "     ";
        gotoXY(x - 1, y + 3);
        cout << "     ";

        gotoXY(x - 1, y);
        cout << "  _  ";
        gotoXY(x - 1, y + 1);
        cout << "{\\o/}";
        gotoXY(x - 1, y + 2);
        cout << " /_\\ ";
        y--;
        for (int i = 0; i < height; i++) { // ve ufo
            for (int j = 0; j < picture[i].length(); j++) {
                if ((UFOx + j) <= borderGLx || (UFOx + j) >= borderGRx) continue;
                gotoXY(UFOx + j, UFOy + i);
                cout << picture[i][j];
            }
            cout << endl;
            if (UFOx - 1 <= borderGLx || UFOx - 1 >= borderGRx) continue;
            gotoXY(UFOx - 1, UFOy + i);
            cout << " ";
        }
        this_thread::sleep_for(chrono::milliseconds(80)); // cho no bay cham, chac vay
    }

}

