#pragma once
#include <Windows.h>
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include <thread>
#include <vector>
#pragma comment(lib, "winmm.lib")

using namespace std;

#define KEY_UP    72
#define KEY_LEFT  75
#define KEY_RIGHT 77
#define KEY_DOWN  80
#define ENTER     13
#define ESC 27
#define ENTER 13

#define thutvao 23

#define LG_LEFT_BORDER 60 // le trai cua khung load game
#define LG_RIGHT_BORDER 115 // le phai cua khung load game

#define SCREEN_BORDER_LEFT 0
#define SCREEN_BORDER_RIGHT 161
#define BOX_WIDTH 56 //LG_RIGHT_BORDER - LG_LEFT_BORDER + 2
#define BOX_LENGTH 20
#define BOX_TOP 7

static int music_state = 1;
static bool menu_stop = false;
static bool loadGame_stop = false;
static int menu_selection = 3;
static int loadGame_selection = 0;



void resizeConsole(int width, int height);

void setConsoleScreenBufferSize();

void setColor(int backgound_color, int text_color);

void ShowCur(bool CursorVisibility);

void gotoXY(int x, int y);

void readFile(string filename, int X, int Y);

void drawMuiTen(float ex, float ey);
int drawLose(int x, int y);
int drawPauseGame(int x, int y);
string drawSaveGame(int x, int y);

//save level va ten player vo text file
void saveGame(string name, int level);

//menu
void loadGameAnimation(vector<string> nameList, int levelList[]);
void loadGame(int& level, string& playerName);
void menuAnimation();
void menu(int& level, string& playerName);




