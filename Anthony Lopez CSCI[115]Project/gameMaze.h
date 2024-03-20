#pragma once
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
	void cpuPlay();
	stack<eDirection> pathToDest(int dest, int* &pi, stack<eDirection> movement);
	void drawMap();
	gameMaze();
	gameMaze(map& loadedMap, player& loadedPlayer);
	void createGraph();
	void updatePlayer(node* &curr);
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