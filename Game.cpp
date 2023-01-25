#include "Game.h"

char MOVING = '\0';

bool Game::IS_WINNING = false;

void subThread(Game* a) {
    system("cls");
    drawGameBoard();
    drawCharacterBoard(a->getLevel(), a->getName());
    drawInstructorBoard();
    a->drawLight();

    while (a->IS_RUNNING) {
        if (!a->getPeople()->isDead()) {
            a->updatePeople(MOVING);
        }
        MOVING = '\0';
        a->updateLane();
        a->drawGame();
        if (a->isImpact()) {
            this_thread::sleep_for(chrono::milliseconds(300));
            a->deathAnimation();
            a->IS_RUNNING = false;
        }
        if (a->getPeople()->isFinish()) {
            system("cls");
            if (a->getLevel() == levelWin) {
                Game::IS_WINNING = true;
                drawWin(27, 10);
                break;
            }
            a->deleteSource();
            a->gameRepair(a->getLevel() + 1, a->getName());
            drawGameBoard();
            drawCharacterBoard(a->getLevel(), a->getName());
            drawInstructorBoard();
            a->drawLight();
        }
        this_thread::sleep_for(chrono::nanoseconds(a->getSpeed()));
    }
}

void Game::gameRepair(int level, string player) {
    if (player == "") {
        this->player = "unknown";
    }
    else {
        this->player = player;
    }
    this->level = level;

    lane* temp;
    for (int i = 1; i <= 6; i++) {
        if (i % 2 == 0) {
            temp = new lane(i, leftToRight, level);
        }
        else {
            temp = new lane(i, rightToLeft, level);
        }
        list.push_back(temp);
        
    }
    speed = 500;
    people = new CPEOPLE;
}

void Game::drawGame() {
    for (int i = 0; i < list.size(); i++) {
        if (level > 3) {
            if (list[i]->isRedOn()) {
                continue;
            }
        }
        list[i]->drawVehicle();
    }
    people->update();
}

void Game::deleteSource() {
    if (people != NULL) {
        delete people;
        people = NULL;
    }
    lane* temp = NULL;
    while (!list.empty()) {
        temp = list.back();
        list.pop_back();
        delete temp;
    }
}

Game::~Game() {
    deleteSource();
}

void Game::deathAnimation() {
    //    for (int i = 0; i < list.size(); i++)
    //        list[i]->erase();

    int UFOx = people->getMX() - 7; // ve ufo, ham ve lay cua verhicle
    int UFOy = 2;
    const int height = 5;
    const int length = 17;
    const string picture[5] =
    {"       ___       ",
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
    gotoXY(45, 40);
    cout << "Press any key to continue";
    LOSE_BOARD = true;
}

void Game::updatePeople(char MOVING) {
    people->nhanbanphim(MOVING);
}

void Game::updateLane() {
    for (int i = 0; i < list.size(); i++) {
        list[i]->updateLane();
    }
}

int Game::getLevel() {
    return level;
}

int Game::getSpeed() {
    return speed;
}

void Game::setSpeed(int speed) {
    this->speed = speed;
}

void Game::setPlayer(string name) {
    player = name;
}

void Game::drawLight() {
    for (int i = 0; i < list.size(); i++) {
        list[i]->drawLight();
    }
}

string Game::getName() {
    return player;
}

CPEOPLE* Game::getPeople() {
    return people;
}

bool Game::isImpact() {
    Vehicle* p = NULL;
    bool check = false;
    for (int i = 0;i < list.size(); i++) {
        int j = 0;
        do {
            p = list[i]->returnEachVehicle(j);
            if (!p) break;
            check = people->isImpact(p, p->type);
            if (check) return true;
            j++;
        } while (true);
    }
    return check;
}

void Game::resume(thread& th1) {
    this->IS_RUNNING = true;
    th1 = thread(subThread, this);
}

void Game::pause(thread& th1) {
    this->IS_RUNNING = false;
    th1.join();
}

void Game::newGame() {
    menu(level, player);
    if (level < 0) {
        this->deleteSource();
        return;
    }
    this->deleteSource();
    this->gameRepair(level, player);
    drawGameBoard();
    drawCharacterBoard(this->getLevel(), this->getName());
}

void Game::save() {
    player = drawSaveGame(45, 15);
    ShowCur(false);
    saveGame(player, level);
}

void Game::gamePlay() {
    thread th1(subThread, this);
    char key = '\0';
    int selection = 0;

    while (true) {
        key = _getch();
        if (!this->getPeople()->isDead()) {
            if (key == 27) {
                pause(th1);
                return;
            }
            else if (key == 'p') {
                //xu ly pauseGame
                pause(th1);
                selection = drawPauseGame(45, 15);
                if (selection == 1) { // continue
                    resume(th1);
                }
                else if (selection == 2) { // new game - back-to-menu
                    newGame();
                    if (level < 0) return;
                    resume(th1);
                }
                else if (selection == 3) { //save game
                    save();
                    resume(th1);
                }
                else if (selection == 4) {
                    break;
                }
                selection = 0;
            }
            else if (key == 's') {
                pause(th1);
                save();
                newGame();
                if (level < 0) return;
                resume(th1);
            }
            else {
                if (Game::IS_WINNING) {
                    //save game
                    Game::IS_WINNING = false;
                    pause(th1);
                    string playerName;
                    playerName = drawSaveGame(70, 17);
                    saveGame(playerName, this->getLevel());
                    //backto menu
                    newGame();
                    if (level < 0) return;
                    resume(th1);
                }
                else {
                    MOVING = key;
                }
            }
        }
        else {
            if (this->LOSE_BOARD) {
                this->LOSE_BOARD = false;
                selection = drawLose(45, 15);
            }
            if (selection == 1) { // save game
                selection = 0;
                pause(th1);
                save();
                newGame();
                if (level < 0) return;
                resume(th1);
            }
            else if (selection == 2) { // new game
                selection = 0;
                pause(th1);
                newGame();
                if (level < 0) return;
                resume(th1);
            }
            else if (selection == 3) { // exit
                selection = 0;
                pause(th1);
                break;
            }
        }
    }
}

//------------------------draw screen game play

void drawGameBoard() {
    for (int i = borderGLx + 1, j = borderGRx - 1; i < borderGRx; ++i) {
        //cac vien ben ngoai
        gotoXY(i, borderGUy);
        cout << '_';
        gotoXY(j, borderGDy);
        cout << '_';
        //cac vien ben trong
        gotoXY(j, borderGUy + 5);
        cout << '_';
        gotoXY(i, borderGUy + 10);
        cout << '_';
        gotoXY(j, borderGUy + 15);
        cout << '_';
        gotoXY(i, borderGUy + 20);
        cout << '_';
        gotoXY(j, borderGUy + 25);
        cout << '_';
        gotoXY(i, borderGUy + 30);
        cout << '_';
        gotoXY(j, borderGUy + 35);
        cout << '_';
        gotoXY(i, borderGUy + 40);
        cout << '_';
        --j;
    }
    for (int i = borderGUy + 1, j = borderGDy; i <= borderGDy; i++) {
        gotoXY(borderGRx, i);
        cout << '|';
        gotoXY(borderGLx, j);
        cout << '|';
        j--;
    }
}

void drawCharacterBoard(int level, string name) {
    for (int i = borderCLx + 1; i < borderCRx; i++) {
        gotoXY(i, borderCUy);
        cout << '_';
        gotoXY(i, borderCDy);
        cout << '_';
    }
    for (int i = borderCUy + 1; i <= borderCDy; i++) {
        gotoXY(borderCRx,i);
        cout << "|";
        gotoXY(borderCLx, i);
        cout << "|";
    }
    gotoXY(borderCLx+1, borderCUy+2);
    cout << "============CROSSING-GAME===========";
    gotoXY(borderCLx +1 , borderCUy+3);
    cout << "    -From Professional Team: 10-";
    gotoXY(borderCLx + 1, borderCUy + 4);
    cout << "          NAME OF WARRIOR:";
    gotoXY(borderCLx + 1, borderCUy + 5);
    cout << "              " << name;
    string nameFile = to_string(level) + ".txt";
    readFile(nameFile,borderCLx + 15, borderCUy + 7);
}

void drawInstructorBoard() {
    for (int i = borderCLx + 1; i < borderCRx; i++) {
        gotoXY(i, borderLevelUy);
        cout << '_';
        gotoXY(i, borderLevelDy);
        cout << '_';
    }
    for (int i = borderLevelUy + 1; i <= borderLevelDy; i++) {
        gotoXY(borderCRx, i);
        cout << "|";
        gotoXY(borderCLx, i);
        cout << "|";
    }
    gotoXY(borderCLx+1, borderLevelUy+1);
    cout << "         KEYBOARD CONTROL";
    gotoXY(borderCLx+1, borderLevelUy + 3);
    cout << "    press direction keys to move";
    gotoXY(borderCLx+1, borderLevelUy + 4);
    cout << "       press ESC to exit game";
    gotoXY(borderCLx + 1, borderLevelUy + 5);
    cout << "        press P to pause game";
    gotoXY(borderCLx + 1, borderLevelUy + 6);
    cout << "  press S to save and back to Menu";
}

//------------------------draw win game
void draw(int i, int j, int x, int y, string s[6])
{
    int ex2;
    int ey;
    string temp;
    ex2 = x + thutvao;
    ey = y + 25;
    temp = s[0].substr(i, j);
    gotoXY(ex2, ey);
    cout << temp;
    temp = s[1].substr(i, j);
    gotoXY(ex2, ey + 1);
    cout << temp;
    temp = s[2].substr(i, j);
    gotoXY(ex2, ey + 2);
    cout << temp;
    temp = s[3].substr(i, j);
    gotoXY(ex2, ey + 3);
    cout << temp;
    temp = s[4].substr(i, j);
    gotoXY(ex2, ey + 4);
    cout << temp;
    temp = s[5].substr(i, j);
    gotoXY(ex2, ey + 5);
    cout << temp;
}

void drawWin(int x, int y)
{
    int ex = x;
    int ey = y;

    ifstream in;
    in.open("win.txt");
    string s[6];
    if (in)
    {
        int i = 0;
        getline(in, s[i]);
        i++;
        while (!in.eof())
        {
            getline(in, s[i]);

            i++;
        }
    }
    in.close();
    in.open("congrat.txt");
    string congrat[8];
    if (in)
    {
        int i = 0;
        getline(in, congrat[i]);
        gotoXY(x-2, 8);
        cout << congrat[i] << endl;
        i++;
        while (!in.eof())
        {
            gotoXY(x-2, 8+i);
            getline(in, congrat[i]);
            cout << congrat[i] << endl;
            i++;
        }
    }
    int j = 1;
    int ei = 72;
    int ej = 1;
    int count = 0;
    int flag = 0;
    int reverse = 0;
    ex = x + 45;
    ey = y + 10;
    gotoXY(ex, ey);
    cout << "Press any key to out game";
    int ex2 = ex = x + thutvao;
    ey = y + 25;
    int i = 72;
    char c;
    while (Game::IS_WINNING)
    {
        string temp;
        ex = ex2;
        ey = y + 25;
        if (count <= 71 || reverse >= 5)
        {
            if (count >= 72)
            {
                draw(ei, ej, x, y, s);
                ej++;
                ei--;
            }
            else
            {
                draw(i, j, x, y, s);
                j++;
                i--;
                count++;
            }

        }
        if (count >= 72)
        {
            if (count >= 145)
            {
                count = reverse - 4;
                i = ei;
                j = ej;
                ex = x + thutvao;
                reverse = 0;
                ei = 72;
                ej = 1;
            }
            else {
                temp = " " + s[0].substr(i, j);
                gotoXY(ex, ey);
                cout << temp;
                temp = " " + s[1].substr(i, j);
                gotoXY(ex, ey + 1);
                cout << temp;
                temp = " " + s[2].substr(i, j);
                gotoXY(ex, ey + 2);
                cout << temp;
                temp = " " + s[3].substr(i, j);
                gotoXY(ex, ey + 3);
                cout << temp;
                temp = " " + s[4].substr(i, j);
                gotoXY(ex, ey + 4);
                cout << temp;
                temp = " " + s[5].substr(i, j);
                gotoXY(ex, ey + 5);
                cout << temp;
                count++;
                j--;
                ex++;
                reverse++;
            }
        }
        ex2 = ex;
        if (flag % 2 == 0)
        {
            ex = x + 10;
            ey = y + 10;
            gotoXY(ex, ey);
            cout << "(" << (char)3 << (char)31 << (char)3 << ")/" << endl;
            ey++;
            gotoXY(ex, ey);
            cout << "<)  )" << endl;
            ey++;
            gotoXY(ex, ey);
            cout << " /  \\";

        }
        else
        {
            ex = x + 10;
            ey = y + 10;
            gotoXY(ex, ey);
            cout << "\\(" << (char)3 << (char)31 << (char)3 << ")" << endl;
            ey++;
            gotoXY(ex, ey);
            cout << "(  (>" << endl;
            ey++;
            gotoXY(ex, ey);
            cout << " /  \\";

        }
        if (flag % 2 == 0)
        {

            ex = x + 100;
            ey = y + 10;
            gotoXY(ex, ey);
            cout << "\\(" << (char)3 << (char)31 << (char)3 << ")" << endl;
            ey++;
            gotoXY(ex, ey);
            cout << "(  (>" << endl;
            ey++;
            gotoXY(ex, ey);
            cout << " /  \\";


        }
        else
        {
            ex = x + 100;
            ey = y + 10;
            gotoXY(ex, ey);
            cout << "(" << (char)3 << (char)31 << (char)3 << ")/" << endl;
            ey++;
            gotoXY(ex, ey);
            cout << "<)  )" << endl;
            ey++;
            gotoXY(ex, ey);
            cout << " /  \\";

        }
        flag++;
        Sleep(60);
    }
}

