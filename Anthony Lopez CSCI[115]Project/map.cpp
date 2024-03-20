#include "map.h"
map::map()
{
	mapX = 0;
	mapY = 0;
	matrix = new node**;
	current = new node();
	goal.first = 0;
	goal.second = 0;
}
map::map(int x, int y)
{
	mapX = x;
	mapY = y;
	matrix = new node ** [mapY];
	for (int i = 0; i < mapY; i++)
	{
		matrix[i] = new node * [mapX];
	}
	for (int i = 0; i < mapY;i++)
	{
		for (int j = 0; j < mapX; j++)
		{
			matrix[i][j] = new node();
		}
	}
	current = new node();
	goal.first = 0;
	goal.second = 0;
}
map::map(const map& copy)
{
	mapX = copy.mapX;
	mapY = copy.mapY;
	current = copy.current;
	goal = copy.goal;
	matrix = copyMatrix(copy.matrix,mapX,mapY);
}
map& map::operator=(const map& to)
{
	map temp(to);
	mapY = temp.mapY;
	mapX = temp.mapX;
	matrix = copyMatrix(to.matrix, mapX, mapY);
	current = temp.current;
	goal = temp.goal;
	return *this;
}
map::~map()
{
	for (int i = 0; i < mapY; i++)
	{
		for (int j = 0; j < mapX; j++)
		{
			if(matrix[i][j]!=nullptr)
			delete matrix[i][j];
		}
		if(matrix[i]!=nullptr)
		delete matrix[i];
	}
	if(matrix!=nullptr)
	delete[] matrix;
	
}
void map::display()
{
	for (int i = 0; i < mapY; i++)
	{
		for (int j = 0; j < mapX; j++)
		{
			cout << matrix[i][j]->landType <<" ";
		}
		cout << endl;
	}
}
void map::drawMap()
{
	display();
}
pair<player, map> map::loadMap(string* source)
{
	pair<player, map> a;
	string temp;
	player currentPlayer;
	for (int i = 0; i < mapY; i++)
	{
		temp = source[i];
		int tpBuffer = 0;
		for (int j = 0; j < mapX; j++)
		{
			if (temp[j + tpBuffer] == 'O')
			{
				currentPlayer = player(j, i);
				matrix[i][j]->landType = ' ';
			}
			else if (temp[j + tpBuffer] == 'G')
			{
				goal.first = j;
				goal.second = i;
				matrix[i][j]->landType = 'G';
			}
			else
			{
				if (temp[j + tpBuffer] == 'T')
				{
					int coord1, coord2;
					int index = j + tpBuffer + 2;
					string coord = "";
					while ((temp[index] != ')') && (index < temp.length()))
					{
						if (temp[index] == ',')
						{
							coord1 = stoi(coord);
							coord = "";
						}
						else
							coord += temp[index];
						index++;
					}
					if (index == temp.length())
						goto ERRORMSG;
					try
					{

						coord2 = stoi(coord);
					}
					catch (string cord)
					{
						goto ERRORMSG;
					}
					matrix[i][j]->tpPair.first = coord1;
					matrix[i][j]->tpPair.second = coord2;
					matrix[coord2][coord1]->tpPair.first = j;
					matrix[coord2][coord1]->tpPair.second = i;
					tpBuffer = index - j;
					matrix[i][j]->landType = 'T';
				}
				else
				{
					matrix[i][j]->landType = temp[j + tpBuffer];
					nodeLoader(matrix[i][j]);
				}
			}
		}

	}
	a.first = currentPlayer;
	a.second = *this;
	return  a;
ERRORMSG:
	cout << "error loading map check syntax" << endl;
	delete this;
	a.first = player();
	a.second = map();
	return a;
}
bool map::checkMove(int x, int y)
{
	switch (matrix[y][x]->landType)
	{
	case '#':
		return false;
		break;
	default:
		return true; 
		break;
	}
}
void map::nodeDupe(node* curr, int num)
{
	if (num == 0)
		return;
	else
	{
		curr->next = new node(curr->landType);
		curr = curr->next;
		nodeDupe(curr, num - 1);
	}
}
void map::nodeLoader(node* curr)
{
	switch (curr->landType)
	{
		case 'F':
			nodeDupe(curr, 2);
			break;
		default:
			break;
	}
}
node* map::copyNode(node* &toBe )
{
	if (toBe->next!= nullptr)
	{
		node* temp = toBe->next;
		node* out = new node(toBe->landType);
		node* cursor = out;
		while (temp)
		{
			setData(cursor, toBe->landType, toBe->tpPair);
			temp = temp->next;
			cursor->next = new node();
			cursor = cursor->next;
		}
		return out;
	}
	else
	{
		node* out = new node();
		setData(out, toBe->landType, toBe->tpPair);
		return out;
	}
}
node*** map::copyMatrix(node*** from, int x, int y)
{
	node*** temp = new node * *[y];
	for (int i = 0; i < y; i++)
	{
		temp[i] = new node * [x];
		for (int j = 0; j <x; j++)
		{
			temp [i][j] = copyNode(from[i][j]);
		}
	}
	return temp;
}
void map::setData(node* source, char data, pair<int,int> tpData)
{
	source->landType = data;
	source->tpPair = tpData;
}
int map::getWeight(int x, int y)
{
	switch (matrix[y][x]->landType)
	{
	case 'F':
		return 3;
		break;
	default:
		return 1;
		break;
	}
}