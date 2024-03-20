#pragma once
#include<utility>
#include<iostream>
#include <conio.h>
using namespace std;
enum eDirection {LEFT, RIGHT, UP, DOWN, IDLE };
class player
{
public:
	bool playerInput();
	void displayDir();
	void updatePos(int x, int y);
	player();
	player(int x, int y);
	pair<int,int> getPos();
	eDirection dir; // the queued direction of the player character
private:
	pair<int, int> pos;
};

