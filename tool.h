#pragma once
#include <Windows.h>
#include "tool.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

void resizeConsole(int width, int height);

void setConsoleScreenBufferSize();

void setColor(int backgound_color, int text_color);

void gotoXY(int x, int y);

void readFile(string filename, int X, int Y);
void chooseNewGame();
void chooseExit();
void chooseLoadGame();

void action(char command, int& selection, bool& quit);
void menu(bool& quit, int& selection);