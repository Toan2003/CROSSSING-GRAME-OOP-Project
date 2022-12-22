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

void chooseNewGame()
{
    system("cls");
}
void chooseLoadGame()
{
    system("cls");
    cout << "You chose load game";
}
void chooseExit()
{
    system("cls");
    cout << "You exited the game";
}

void action(char command, int& selection, bool& quit) {
    if (command == 27)
    {
        quit = true;
        chooseExit();
    }
    if (tolower(command) == 'w')
        if (selection < 3)
            selection++;
    if (tolower(command) == 's')
        if (selection > 1)
            selection--;
    if (command == 13)
        if (selection == 3)
        {
            chooseNewGame();
            quit = true;
        }
        else if (selection == 2)
        {
            chooseLoadGame();
            quit = true;
        }
        else
        {
            chooseExit();
            quit = true;
        }
}

void menu(bool& quit, int& selection) {
    char command;
    // system("color F0");
    system("cls");
    readFile("menu.txt", 20, 5);
    int X = 100;
    gotoXY(X, 15);
    if (selection == 3)
        cout << "->New game";
    else
        cout << "New game";
    gotoXY(X, 16);
    if (selection == 2)
        cout << "->Load game";
    else
        cout << "Load game";
    gotoXY(X, 17);
    if (selection == 1)
        cout << "->Exit";
    else
        cout << "Exit";
    command = _getch();
    action(command, selection, quit);
}

void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;

    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;

    SetConsoleCursorInfo(handle, &ConCurInf);
}