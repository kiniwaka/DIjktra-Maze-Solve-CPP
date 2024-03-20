// this class handles the game state such as player position, what map is loaded, movements, actual direction setting, running shortest path 
#pragma once
#include <string>
#include<vector>
#include "player.h"
#include "graphAM.h"
#include "stdlib.h"
#include "conio.h"
#include "windows.h"
#include <stack>
#include "map.h"
using namespace std;
class gameMaze
{
public:
	void play();
	void cpuPlay();// runns djikstra creates the map graph then runs pathTodest the output of path to dest is a stack of directions that the cpuPlay funcion uses to update player position for each step
	stack<eDirection> pathToDest(int dest, int* &pi, stack<eDirection> movement);//loads a stack of directions given from djiktra
	void drawMap();
	gameMaze();
	gameMaze(map& loadedMap, player& loadedPlayer);
	void createGraph();
	void updatePlayer(node* &curr); // this takes player input and sets the player direction and updates the player position.
	void displayNode(node* toDisplay)
	{
		if (toDisplay != nullptr)
		{
			node* temp = toDisplay;
			int i = 0;
			while (temp)
			{
				cout << i <<temp->landType<< endl;
				temp = temp->next;
				i++;
			}
		}
	}
private:
	pair<int, int> dest;
	player currentPlayer;
	graphAM* gameGraph;
	map gameMap;
};