#pragma once
#include <string>
#include<vector>
#include "player.h"
#include "graphAM.h"
#include "stdlib.h"
#include "conio.h"
#include "windows.h"
#include <stack>
using namespace std;
struct node
{
	char landType;
	pair<int, int> tpPair;
	node* next;
	node() { landType = '?'; next = nullptr; tpPair.first = 0; tpPair.second = 0; }
	node(char land) { landType = land; next = nullptr; }
};
class map
{
public:
	node*** copyMatrix(node*** from,int x, int y);
	node* copyNode(node* &toBeCopied );
	pair<player, map> loadMap(string* source);
	//void displayNode(node* toDisplay);
	void drawMap();
	bool checkMove(int x, int y);
	int getWeight(int x, int y);
	map();
	map(int x, int y);
	map(const map& copy);
	map& operator =(const map& to);
	~map();
	void display();
	void nodeDupe(node* curr, int num);
	void nodeLoader(node* curr);
	int mapX;
	int mapY;
	node* current;
	node*** matrix;
	void setData(node* source, char data, pair<int,int> tpData);
	pair<int , int > goal;
};

