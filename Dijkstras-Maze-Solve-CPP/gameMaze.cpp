#include "gameMaze.h"
#include <iomanip>
using namespace std;
void displayShortest(double*& d, int*& pi, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "vertex: " << i << " : d= " << d[i] << " : pi= " << pi[i] << endl;
	}
}
gameMaze::gameMaze()
{
	currentPlayer = player();
	gameMap = map();
	gameGraph = new graphAM();
	dest.first = 0;
	dest.second = 0;
}
gameMaze::gameMaze(map& loadedMap, player& loadedPlayer)
{
	gameMap = loadedMap;
	currentPlayer = loadedPlayer;
	gameGraph =new graphAM(gameMap.mapX * gameMap.mapY);
	createGraph();
	int source = currentPlayer.getPos().second * gameMap.mapX + currentPlayer.getPos().first;
	int goal = gameMap.goal.second * gameMap.mapX + gameMap.goal.first;
	double* d;
	int* pi;
}
void gameMaze::drawMap()
{
	for (int i = 0; i <gameMap.mapY; i++)
	{
		for (int j = 0; j < gameMap.mapX; j++)
		{
			if ((i == currentPlayer.getPos().second) && (j == currentPlayer.getPos().first))
				cout << 'O' << " ";
			else
			{
				char out;
				switch (gameMap.matrix[i][j]->landType)
				{
				case 'P':
					out = ' ';
					break;
				case 'B':
					if (j == 0 || j == gameMap.mapX - 1)
					{
						if (i == 0 || i == gameMap.mapY - 1)
							out = '+';
						else
							out = '|';
					}
					else
						out = '-';
					break;
				default:
					out = gameMap.matrix[i][j]->landType;
					break;
				}
				cout << out << " ";
			}
		}
		cout << endl;
	}
}
void gameMaze::updatePlayer(node* &current)// checks if our cursor is nullptr before we update player pos this gives us the multiple key strokes property to simulate weight checks for valid moves and update player pos.
{
	if (current->next == nullptr)
	{
		switch (currentPlayer.dir)
		{
			int newCoord;
		case UP:
			if (currentPlayer.getPos().second - 1 <= 0)
				currentPlayer.updatePos(currentPlayer.getPos().first, currentPlayer.getPos().second);
			else
			{
				newCoord = currentPlayer.getPos().second - 1;
				if (gameMap.checkMove(currentPlayer.getPos().first, newCoord))
				{
					if (gameMap.matrix[newCoord][currentPlayer.getPos().first]->landType == 'T')
						currentPlayer.updatePos(gameMap.matrix[newCoord][currentPlayer.getPos().first]->tpPair.first, gameMap.matrix[newCoord][currentPlayer.getPos().first]->tpPair.second);
					else
						currentPlayer.updatePos(currentPlayer.getPos().first, newCoord);
					current = gameMap.matrix[currentPlayer.getPos().second][currentPlayer.getPos().first];
				}
			}
			break;
		case DOWN:
			if (currentPlayer.getPos().second + 1 >= gameMap.mapY - 1)
				currentPlayer.updatePos(currentPlayer.getPos().first, currentPlayer.getPos().second);
			else
			{
				newCoord = currentPlayer.getPos().second + 1;
				if (gameMap.checkMove(currentPlayer.getPos().first, newCoord))
				{
					if (gameMap.matrix[newCoord][currentPlayer.getPos().first]->landType == 'T')
						currentPlayer.updatePos(gameMap.matrix[newCoord][currentPlayer.getPos().first]->tpPair.first, gameMap.matrix[newCoord][currentPlayer.getPos().first]->tpPair.second);
					else
						currentPlayer.updatePos(currentPlayer.getPos().first, newCoord);
					current = gameMap.matrix[currentPlayer.getPos().second][currentPlayer.getPos().first];
				}
			}
			break;
		case LEFT:
			if (currentPlayer.getPos().first - 1 <= 0)
				currentPlayer.updatePos(currentPlayer.getPos().first, currentPlayer.getPos().second);
			else
			{
				newCoord = currentPlayer.getPos().first - 1;
				if (gameMap.checkMove(newCoord, currentPlayer.getPos().second))
				{
					if (gameMap.matrix[currentPlayer.getPos().second][newCoord]->landType == 'T')
						currentPlayer.updatePos(gameMap.matrix[currentPlayer.getPos().second][newCoord]->tpPair.first, gameMap.matrix[currentPlayer.getPos().second][newCoord]->tpPair.second);
					else
						currentPlayer.updatePos(newCoord, currentPlayer.getPos().second);
					current = gameMap.matrix[currentPlayer.getPos().second][currentPlayer.getPos().first];
				}

			}
			break;
		case RIGHT:
			if (currentPlayer.getPos().first + 1 >= gameMap.mapX - 1)
				currentPlayer.updatePos(currentPlayer.getPos().first, currentPlayer.getPos().second);
			else
			{
				newCoord = currentPlayer.getPos().first + 1;
				if (gameMap.checkMove(newCoord, currentPlayer.getPos().second))
				{
					if (gameMap.matrix[currentPlayer.getPos().second][newCoord]->landType == 'T')
						currentPlayer.updatePos(gameMap.matrix[currentPlayer.getPos().second][newCoord]->tpPair.first, gameMap.matrix[currentPlayer.getPos().second][newCoord]->tpPair.second);
					else
						currentPlayer.updatePos(newCoord, currentPlayer.getPos().second);
					current = gameMap.matrix[currentPlayer.getPos().second][currentPlayer.getPos().first];
				}
			}
			break;
		}
		system("cls");
		drawMap();
	}
	else
		current = current->next;
}
void gameMaze::play()//waits for input updates player pos until goal is reached
{
	system("cls");
	drawMap();
	node* curr = new node();
	while (currentPlayer.getPos()!=gameMap.goal)
	{
		bool input = false;
		while (!input)
		{
			input = currentPlayer.playerInput();
		}
		updatePlayer(curr);
	}
	system("cls");
	cout << "Maze solved great job!" << endl;
	Sleep(400);

}
void gameMaze::cpuPlay()//loads game graph and djikstra output uses that output to run pathToDes uses that output of directions to update player pos 
{
	createGraph();
	int source = currentPlayer.getPos().second * gameMap.mapX + currentPlayer.getPos().first;
	int goal = gameMap.goal.second * gameMap.mapX + gameMap.goal.first;
	double* d;
	int* pi;
	gameGraph->Djikstra(source, d, pi);
	stack<eDirection> moves, start;
	node* curr = new node();
	moves = pathToDest(goal, pi, start);
	bool autoMov =false;
	bool modeSet = false;
	while (!moves.empty()&&currentPlayer.getPos()!=gameMap.goal)
	{
		currentPlayer.dir = moves.top();
		if (!modeSet)
		{
			system("cls");
			drawMap();
			cout << "choose mode: 'a' for auto 'n' for step wise" << endl;
			while (!modeSet)
			{
				if (_kbhit())
				{
					switch (_getch())
					{
					case 'a':
						autoMov = true;
						modeSet = true;
						break;
					case 'n':
						autoMov = false;
						modeSet = true;
						break;
					default:
						modeSet = false;
						break;
					}
				}
			}
			system("cls");
			drawMap();
		}
		
		if (autoMov)
		{
			updatePlayer(curr);
			currentPlayer.displayDir();
			Sleep(500);
		}
		else
		{
			bool input = false;
			while (!input)
			{
				if (_kbhit())
				{
					switch (_getch())
					{
					case 'n':
						input = true;
						break;
					default:
						input = false;
						break;
					}
				}
			}
			updatePlayer(curr);
			currentPlayer.displayDir();
		}

		if (curr->next == nullptr)
			moves.pop();
	}
	system("cls");
	cout << "Djikstra gave you the shortest path for this maze!" << endl;
	Sleep(500);
}
stack<eDirection> gameMaze::pathToDest(int dest, int*& pi, stack<eDirection> movement)
{
	//basically turns vertext number into coordinates and uses these corrdinates to get the change in direction given by djikstra
	if (pi[dest] != -1)
	{
		int next = pi[dest];
		int destY = dest / gameMap.mapX;
		int destX = dest % gameMap.mapX;
		int nextY = next / gameMap.mapX;
		int nextX = next % gameMap.mapX;
		if (destY - nextY == 0&&abs(destX - nextX) <=1) //simple up down left right
		{
			if (destX - nextX == -1)
				movement.push(LEFT);
			else
				movement.push(RIGHT);
		}
		else if (destY - nextY == -1||destY-nextY==1)
		{
			if (destY - nextY == -1)
				movement.push(UP);
			else
				movement.push(DOWN);
		}
		else //teleporter cases
		{
			// we have to check tp Pairs in relation to dest because djikstra considers a move into a teleporter a move straight into the output tile.
			int tpnextY = gameMap.matrix[destY][destX]->tpPair.second;
			int tpnextX = gameMap.matrix[destY][destX]->tpPair.first;
			if (tpnextY - nextY == 0)
			{
				if (tpnextX - nextX == -1)
					movement.push(LEFT);
				else
					movement.push(RIGHT);

			}
			else
			{
				if (tpnextY - nextY == -1)
					movement.push(UP);
				else
					movement.push(DOWN);
			}
		}
		return pathToDest(next, pi, movement);
	}
	else
	return movement;
}
void gameMaze::createGraph() // runs through the matrix and sets edges for up down left right from the current tile if the move is valid
{
	for (int i = 1; i < gameMap.mapY-1; i++)
	{
		for (int j = 1; j < gameMap.mapX - 1; j++)
		{
			int u = (i * gameMap.mapX) + j;
			int w = gameMap.getWeight(j, i);
			int v;
				if (((i - 1) > 0) && (gameMap.checkMove(j, i - 1) && gameMap.checkMove(j, i)))
				{
					if (gameMap.matrix[i-1][j]->landType == 'T')// tp case
					{
						v = gameMap.matrix[i-1][j]->tpPair.second * gameMap.mapX + gameMap.matrix[i-1][j]->tpPair.first;
						gameGraph->setDirectedEdge(u, v,w);
					}
					v = ((i - 1) * gameMap.mapX) + j;
					gameGraph->setDirectedEdge(u, v, w);
				}
				if (((i + 1) < gameMap.mapY - 1) && (gameMap.checkMove(j, i + 1) && gameMap.checkMove(j, i)))
				{
					if (gameMap.matrix[i+1][j]->landType == 'T')
					{
						v = gameMap.matrix[i+1][j]->tpPair.second * gameMap.mapX + gameMap.matrix[i+1][j]->tpPair.first;
						gameGraph->setDirectedEdge(u, v,w);
					}
					v = ((i + 1) * gameMap.mapX) + j;
					gameGraph->setDirectedEdge(u, v, w);
				}
				if (((j - 1) > 0) && (gameMap.checkMove(j - 1, i) && gameMap.checkMove(j, i)))
				{
					if (gameMap.matrix[i][j-1]->landType == 'T')
					{
						v = gameMap.matrix[i][j-1]->tpPair.second * gameMap.mapX + gameMap.matrix[i][j-1]->tpPair.first;
						gameGraph->setDirectedEdge(u, v,w);
					}
					v = (i * gameMap.mapX) + j - 1;
					gameGraph->setDirectedEdge(u, v, w);
				}
				if (((j + 1) < gameMap.mapX - 1) && (gameMap.checkMove(j + 1, i) && gameMap.checkMove(j, i)))
				{
					if (gameMap.matrix[i][j+1]->landType == 'T')
					{
						v = gameMap.matrix[i][j+1]->tpPair.second * gameMap.mapX + gameMap.matrix[i][j+1]->tpPair.first;
						gameGraph->setDirectedEdge(u, v,w);
					}					
					v = (i * gameMap.mapX) + j + 1;
					gameGraph->setDirectedEdge(u, v, w);
				}
		}
	}
}
