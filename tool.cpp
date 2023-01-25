#include "tool.h"

void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}

void setConsoleScreenBufferSize()
{
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;


	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &screenBufferInfo);

	COORD new_screen_buffer_size;

	new_screen_buffer_size.X = screenBufferInfo.srWindow.Right -
		screenBufferInfo.srWindow.Left + 1;
	new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom -
		screenBufferInfo.srWindow.Top + 1;


	SetConsoleScreenBufferSize(hConsole, new_screen_buffer_size);
}

void setColor(int backgound_color, int text_color)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int color_code = backgound_color * 16 + text_color;
	SetConsoleTextAttribute(hStdout, color_code);
}

void gotoXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void readFile(string filename, int X, int Y)
{
    ifstream in;
    in.open(filename);
    if (in)
    {
        string s;
        getline(in, s);
        while (!in.eof())
        {
            gotoXY(X, Y);
            cout << s;
            Y++;
            getline(in, s);
        }
    }
    else cout << "error";
    in.close();
}

void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;

    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;

    SetConsoleCursorInfo(handle, &ConCurInf);
}

void drawMuiTen(float ex, float ey)
{

    gotoXY(ex, ey);
    cout << (char)16;

}

int drawLose(int x, int y)
{
    int ex = x;
    int ey = y;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            gotoXY(ex, ey);
            cout << " ";
            ex++;
        }
        ex = x;
        ey++;
    }
    ex = x;
    ey = y;
    for (int i = 0; i < 30; i++)
    {
        gotoXY(ex, y);
        cout << (char)219;
        ey = y + 9;
        gotoXY(ex, ey);
        cout << (char)219;
        ex++;
    }
    ex = x;
    ey = y + 1;
    for (int i = 0; i < 8; i++)
    {
        gotoXY(ex, ey);
        cout << (char)221;
        ex = x + 29;
        gotoXY(ex, ey);
        cout << (char)222;
        ex = x;
        ey++;
    }
    ex = x + 30;
    ey = y + 0;
    gotoXY(ex, ey);
    cout << (char)191;
    ey++;
    for (int i = 0; i < 10; i++)
    {
        gotoXY(ex, ey);
        cout << (char)179;
        ey++;
    }
    ex = x + 0;
    ey--;
    gotoXY(ex, ey);
    cout << (char)192;
    ex++;
    for (int i = 0; i < 29; i++)
    {
        gotoXY(ex, ey);
        cout << (char)196;
        ex++;
    }
    gotoXY(ex, ey);
    cout << (char)217;
    ex = (x + 11);
    ey = y + 2;
    gotoXY(ex, ey);
    cout << "!YOU LOSE!";

    ex = x + 10;
    ey = y + 5;
    gotoXY(ex, ey);
    cout << "Save game";
    ey++;
    gotoXY(ex, ey);
    cout << "New game";
    ey++;
    gotoXY(ex, ey);
    cout << "Exit";


    ex = x + 8;
    ey = y + 5;
    drawMuiTen(ex, ey);
    char c;
    while (true)
    {
        int ex2 = ex;
        int ey2 = ey;
        c = _getch();
        switch (c)
        {
        case KEY_UP /* H */:
            ey--;
            if (ey < (y + 5))
                ey++;
            break;
        case KEY_DOWN /* K */:
            ey++;
            if (ey > (y + 7))
                ey--;
            break;
        }
        gotoXY(ex2, ey2);
        cout << " ";
        drawMuiTen(ex, ey);
        if (c == ENTER)
        {
            if (ey == y + 5)
            {
                return 1; //save game
            }
            else if (ey == y + 6)
            {
                return 2;//new game
            }
            else if (ey == y + 7)
            {
                return 3; //exit
            }
        }
    }
    return 0;
}

int drawPauseGame(int x, int y)
{
    int ex = x;
    int ey = y;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            gotoXY(ex, ey);
            cout << " ";
            ex++;
        }
        ex = x;
        ey++;
    }

    ex = x + 10;
    ey = y + 4;
    gotoXY(ex, ey);
    cout << "Continue";
    ey++;
    gotoXY(ex, ey);
    cout << "  Menu";
    ey++;
    gotoXY(ex, ey);
    cout << "Save game";
    ey++;
    gotoXY(ex, ey);
    cout << "Exit game";

    ex = x;
    ey = y;

    for (int i = 0; i < 30; i++)
    {
        gotoXY(ex, y);
        cout << (char)219;
        ey = y + 9;
        gotoXY(ex, ey);
        cout << (char)219;
        ex++;
    }
    ex = x;
    ey = y + 1;
    for (int i = 0; i < 8; i++)
    {
        gotoXY(ex, ey);
        cout << (char)221;
        ex = x + 29;
        gotoXY(ex, ey);
        cout << (char)222;
        ex = x;
        ey++;
    }
    ex = x + 30;
    ey = y + 0;
    gotoXY(ex, ey);
    cout << (char)191;
    ey++;
    for (int i = 0; i < 10; i++)
    {
        gotoXY(ex, ey);
        cout << (char)179;
        ey++;
    }
    ex = x + 0;
    ey--;
    gotoXY(ex, ey);
    cout << (char)192;
    ex++;
    for (int i = 0; i < 29; i++)
    {
        gotoXY(ex, ey);
        cout << (char)196;
        ex++;
    }
    gotoXY(ex, ey);
    cout << (char)217;
    ex = (x + 12);
    ey = y + 2;
    gotoXY(ex, ey);
    cout << "PAUSED";

    ex = x + 8;
    ey = y + 4;
    drawMuiTen(ex, ey);
    char c;
    while (true)
    {
        int ex2 = ex;
        int ey2 = ey;
        c = _getch();
        switch (c)
        {
        case KEY_UP /* H */:
            ey--;
            if (ey < (y + 4))
                ey++;
            break;
        case KEY_DOWN /* K */:
            ey++;
            if (ey > (y + 7))
                ey--;
            break;
        }
        gotoXY(ex2, ey2);
        cout << " ";
        drawMuiTen(ex, ey);
        if (c == ENTER)
        {
            if (ey == y + 4)
            {
                return 1;//continue
            }
            else if (ey == y + 5)
            {
                return 2;//new game
            }
            else if (ey == y + 6)
            {
                return 3;//save game
            }
            else if (ey == y + 7)
            {
                return 4;//exit
            }
            break;
        }
    }
    return 0;
}

string drawSaveGame(int x, int y)
{

    int ex = x;
    int ey = y;


    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            gotoXY(ex, ey);
            cout << " ";
            ex++;
        }
        ex = x;
        ey++;
    }
    ex = x;
    ey = y;
    for (int i = 0; i < 30; i++)
    {
        gotoXY(ex, y);
        cout << (char)219;
        ey = y + 9;
        gotoXY(ex, ey);
        cout << (char)219;
        ex++;
    }
    ex = x;
    ey = y + 1;
    for (int i = 0; i < 8; i++)
    {
        gotoXY(ex, ey);
        cout << (char)221;
        ex = x + 29;
        gotoXY(ex, ey);
        cout << (char)222;
        ex = x;
        ey++;
    }
    ex = x + 30;
    ey = y + 0;
    gotoXY(ex, ey);
    cout << (char)191;
    ey++;
    for (int i = 0; i < 10; i++)
    {
        gotoXY(ex, ey);
        cout << (char)179;
        ey++;
    }
    ex = x + 0;
    ey--;
    gotoXY(ex, ey);
    cout << (char)192;
    ex++;
    for (int i = 0; i < 29; i++)
    {
        gotoXY(ex, ey);
        cout << (char)196;
        ex++;
    }
    gotoXY(ex, ey);
    cout << (char)217;
    ex = (x + 9);
    ey = y + 2;
    gotoXY(ex, ey);
    cout << "Player's name";
    ex = x + 5;
    ey = y + 5;
    gotoXY(ex, ey);
    cout << "_____________________";
    ex = x + 7;
    ey = y + 4;
    gotoXY(ex, ey);
    string n;
    getline(cin, n);
    return n;
}

//save level va ten player vo text file
void saveGame(string name, int level) {
    ifstream in("data.txt");
    vector<string> data;
    string tmp;
    if (!in) {
        cout << "error: can not find data.txt";
        return;
    }
    while (!in.eof()) {
        getline(in, tmp);
        data.push_back(tmp);
    }
    in.close();

    ofstream out("data.txt");
    int dataSize = 5;

    if (data.size() < 5)
        dataSize = data.size() + 1;
    for (int i = 0; i < dataSize; i++) {
        if (i == 0) {
            out << name << " " << level;
            if (data[0] != "")
                out << endl;
        }
        else if (i < dataSize - 1)
            out << data[i - 1] << endl;
        else
            out << data[i - 1];
    }
    out.close();
}

//menu
void menuAnimation() {
    const int roadY = 30;

    const int cityHeight = 8;
    const string city[8] = {
"                                                  .======.                                                                  .======.                                                   ",
"                                                  |::: : |                                                                  |::: : |                                                   ",
"    .====.                                  .~.===: : : :|   ..===.           .====.                                  .~.===: : : :|   ..===.          .====.                          ",
"    |.::'||      .=====.      .=======.~,   |\"|: :|::::::|   ||:::|=====|     |.::'||      .=====.      .=======.~,   |\"|: :|::::::|   ||:::|=====|    |.::'||      .=====.      .=====",
" ___| :::|!__.,  |:::::|__    |: :: ::|\"|l_l|\"|:: |:;;:::|___!| ::|: : :|  ___| :::|!__.,  |:::::|__    |: :: ::|\"|l_l|\"|:: |:;;:::|___!| ::|: : :| ___| :::|!__.,  |:::::|__    |: :: ",
"|: :|::: |:: |!__|; :: |: |===::: :: :|\"||_||\"| : |: :: :|: : |:: |:::::| |: :|::: |:: |!__|; :: |: |===::: :: :|\"||_||\"| : |: :: :|: : |:: |:::::||: :|::: |:: |!__|; :: |: |===::: ::",
"|:::| _::|: :|:::|:===:|::|:::|:===F=:|\"!/|\\!\"|::F|:====:|::_:|: :|::__:| |:::| _::|: :|:::|:===:|::|:::|:===F=:|\"!/|\\!\"|::F|:====:|::_:|: :|::__:||:::| _::|: :|:::|:===:|::|:::|:===F",
"!_[]![_]_!_[]![]_!_[__]![]![_]![_][I_]!//_:_\\\\![]I![_][_]!_[_]![]_!_[__]! !_[]![_]_!_[]![]_!_[__]![]![_]![_][I_]!//_:_\\\\![]I![_][_]!_[_]![]_!_[__]!!_[]![_]_!_[]![]_!_[__]![]![_]![_][I"
    };


    for (int i = 0; i < cityHeight; i++) { // ve thanh pho
        gotoXY(0, roadY - cityHeight + i);
        cout << city[i];
    }

    for (int i = 0; i < SCREEN_BORDER_RIGHT; i++) { // ve duong
        gotoXY(i, roadY);
        cout << "=";
        gotoXY(i, roadY + 12);
        cout << "=";
        if (i % 3 == 0) {
            gotoXY(i, roadY + 6);
            cout << "-";
        }
    }

    int carY = roadY + 1;
    int carX = 0;
    const string car[4] = // copy , khong can dung obstacle
    { "  ______     ",
      " /|_||_\\`.__ ",
      "(   _    _ _\\",
      "=`-(_)--(_)-'" };

    int busY = roadY + 7;
    int busX = 133;
    const string bus[4] = // copy
    { "   _____________     ",
       " _/_|[][][][][] | - -",
       "(      City Bus | - -",
       "=--OO-------OO--=dwb " };

    while (!menu_stop) {
        if (carX > SCREEN_BORDER_RIGHT) // ve cac nut lenh
            carX = 0;
        if (busX < 0)
            busX = SCREEN_BORDER_RIGHT;
        gotoXY(80, 15);
        cout << "           ";
        gotoXY(80, 15);
        if (menu_selection == 3)
            cout << "->New game";
        else
            cout << "New game";
        gotoXY(80, 16);
        cout << "           ";
        gotoXY(80, 16);
        if (menu_selection == 2)
            cout << "->Load game";
        else
            cout << "Load game";
        gotoXY(80, 17);
        cout << "            ";
        gotoXY(80, 17);
        if (menu_selection == 1)
            if (music_state == 1)
                cout << "->Music: ON";
            else
                cout << "->Music: OFF";
        else
            if (music_state == 1)
                cout << "Music: ON";
            else
                cout << "Music: OFF";
        gotoXY(80, 18);
        cout << "          ";
        gotoXY(80, 18);
        if (menu_selection == 0)
            cout << "->Exit";
        else
            cout << "Exit";
        for (int i = 0; i < 4; i++) { // ve car
            for (int j = 0; j < 13; j++) {
                if ((carX + j) <= SCREEN_BORDER_LEFT) continue;
                if ((carX + j) >= SCREEN_BORDER_RIGHT) break;
                gotoXY(carX + j, carY + i);
                cout << car[i][j];
            }
            if (carX - 1 <= SCREEN_BORDER_LEFT || carX - 1 >= SCREEN_BORDER_RIGHT) continue;
            gotoXY(carX - 1, carY + i);
            cout << " ";
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 21; j++) {
                if ((busX - j) <= SCREEN_BORDER_LEFT) break;
                if ((busX - j) >= SCREEN_BORDER_RIGHT) continue;
                gotoXY(busX - j, busY + i);
                cout << bus[i][21 - j - 1];
            }
            if (busX + 1 <= SCREEN_BORDER_LEFT || busX + 1 >= SCREEN_BORDER_RIGHT) continue;
            gotoXY(busX + 1, busY + i);
            cout << " ";
        }

        carX++;
        busX--;
        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

void loadGameAnimation(vector<string> nameList, int levelList[]) {
    const int railY = 40;
    for (int i = 0; i < SCREEN_BORDER_RIGHT; i++) {
        gotoXY(i, railY);
        if (i % 2 == 0)
            cout << "+";
        else
            cout << "=";
    }

    int trainY = railY - 5;
    int trainX = SCREEN_BORDER_RIGHT + 123;
    const string train[5] =
    {
    "     o x o x o x o . . .                                                                                                   ",
    "    o      _____            _______________ _______________ _______________ _______________ _______________ ___=====__T___ ",
    "  .][__n_n_|DD[  ====_____  |    |.\\/.|   | |    |.\\/.|   | |    |.\\/.|   | |    |.\\/.|   | |    |.\\/.|   | |   |_|     |_ ",
    " >(________|__|_[_________]_|____|_/\\_|___|_|____|_/\\_|___|_|____|_/\\_|___|_|____|_/\\_|___|_|____|_/\\_|___|_|___________|_|",
    "_/oo OOOOO oo`  ooo   ooo   o^o       o^o   o^o       o^o   o^o       o^o   o^o       o^o   o^o       o^o   o^o     o^o    "
    };

    while (!loadGame_stop) {

        for (int i = 0; i < nameList.size(); i++) { // ve danh sach cho nguoi choi chon
            if (nameList[0] == "")
            {
                gotoXY(LG_LEFT_BORDER + 1, BOX_TOP + 3);
                cout << "Empty";
                break;
            }
            gotoXY(LG_LEFT_BORDER - 2, BOX_TOP + 3 + loadGame_selection);
            cout << "=>";
            if (nameList[i] != "") {
                gotoXY(LG_LEFT_BORDER + 1, BOX_TOP + 3 + i);
                cout << nameList[i];
                gotoXY(LG_RIGHT_BORDER - (BOX_WIDTH / 4), BOX_TOP + 3 + i);
                cout << levelList[i];
            }
        }
        gotoXY(LG_LEFT_BORDER - 2, BOX_TOP + 3 + loadGame_selection - 1);
        cout << " |";
        gotoXY(LG_LEFT_BORDER - 2, BOX_TOP + 3 + loadGame_selection + 1);
        cout << " |";

        if (trainX < 0) // ve tau
            trainX = SCREEN_BORDER_RIGHT + 123;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 123; j++) {
                if ((trainX - j) <= SCREEN_BORDER_LEFT) break;
                if ((trainX - j) >= SCREEN_BORDER_RIGHT) continue;
                gotoXY(trainX - j, trainY + i);
                cout << train[i][123 - j - 1];
            }
            if (trainX + 1 <= SCREEN_BORDER_LEFT || trainX + 1 >= SCREEN_BORDER_RIGHT) continue;
            gotoXY(trainX + 1, trainY + i);
            cout << " ";
        }
        trainX--;
    }
}

void loadGame(int& level, string& playerName) {
    fstream in("data.txt", ios::in);
    int boxWidth = LG_RIGHT_BORDER - LG_LEFT_BORDER + 2;
    int boxLength = 20;
    int boxTop = 7;

    system("cls");
    readFile("loadGame.txt", 61, 0);
    for (int i = 0; i < boxWidth - 1; i++)
    {
        gotoXY(LG_LEFT_BORDER + i, boxTop);
        cout << "-";
        gotoXY(LG_RIGHT_BORDER - i, boxTop + boxLength);
        cout << "-";
    }
    for (int i = 0; i < boxLength - 1; i++) {
        gotoXY(LG_RIGHT_BORDER + 1, boxTop + i + 1);
        cout << "|";
        gotoXY(LG_LEFT_BORDER - 1, boxTop + boxLength - i - 1);
        cout << "|";
    }
    for (int i = 0; i < boxWidth - 3; i++)
    {
        gotoXY(LG_LEFT_BORDER + i + 1, boxTop + 2);
        cout << "-";
    }
    gotoXY(LG_LEFT_BORDER + boxWidth / 2, boxTop + 1);
    cout << "|";
    gotoXY(LG_LEFT_BORDER + (boxWidth / 4 - 2), boxTop + 1);
    cout << "name";
    gotoXY(LG_RIGHT_BORDER - (boxWidth / 4 + 2), boxTop + 1);
    cout << "level";

    vector<string> nameList;
    string temp;
    int levelList[5];
    int index = 0;

    if (in) {
        while (!in.eof())
        {
            in >> temp;
            nameList.push_back(temp);
            in >> levelList[index++];
        }
    }
    else {
        gotoXY(LG_LEFT_BORDER + 1, boxTop + 3);
        cout << "Error!";
    }

    gotoXY(LG_LEFT_BORDER + (BOX_WIDTH / 2 - 7), BOX_TOP + BOX_LENGTH + 1);
    cout << "x: back to menu";
    char command;

    thread loadGame_thread(loadGameAnimation, nameList, levelList);
    while (true) {
        command = _getch();

        if (command == KEY_UP)
            if (loadGame_selection > 0)
                loadGame_selection--;
        if (command == KEY_DOWN)
            if (loadGame_selection < nameList.size() - 1)
                loadGame_selection++;
        if (command == ENTER) {
            loadGame_stop = true;
            loadGame_thread.join();
            loadGame_stop = false;
            level = levelList[loadGame_selection];
            playerName = nameList[loadGame_selection];
            break;
        }
        if (toupper(command) == 'X') {
            loadGame_stop = true;
            loadGame_thread.join();
            loadGame_stop = false;
            playerName = "back_to_menu";
            return;
        }
    }
    in.close();
}

void menu(int& level, string& playerName) {

    char command;
    bool quit = false;

    system("cls");
    readFile("menu.txt", 35, 5);
    thread menu_thread(menuAnimation);

    while (!quit) {
        command = _getch();
        if (command == 27)
        {
            menu_stop = true;
            menu_thread.join();
            menu_stop = false;
            level = -1;
            playerName = "exit";
            quit = true;
        }
        if (command == ENTER && menu_selection == 1) {
            if (music_state == 1) {
                music_state = 0;
                PlaySound(NULL, NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
            }
            else {
                music_state = 1;
                PlaySound(TEXT("music.wav"), NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
            }
            continue;
        }
        if (command == KEY_UP)
            if (menu_selection < 3)
                menu_selection++;
        if (command == KEY_DOWN)
            if (menu_selection > 0)
                menu_selection--;
        if (command == ENTER) {
            menu_stop = true;
            menu_thread.join();
            menu_stop = false;
            if (menu_selection == 3)
            {
                level = 1;
                playerName = "Unknown";
                quit = true;
            }
            else if (menu_selection == 2)
            {
                loadGame(level, playerName);
                quit = true;
            }
            else if (menu_selection == 0)
            {
                level = -1;
                playerName = "exit";
                quit = true;
            }
        }
    }
    if (playerName == "back_to_menu")
        menu(level, playerName);
}
