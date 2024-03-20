#include "player.h"
player::player()
{
	pos.first = -1;
	pos.second = -1;
	dir = IDLE;
}
player::player(int x, int y)
{
	pos.first = x;
	pos.second = y;
	dir = IDLE;
}
void player::updatePos(int x, int y)
{
	pos.first = x;
	pos.second = y;
}
pair<int,int> player::getPos()
{
	return pos;
}
bool player::playerInput()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			return true;
		case 'd':
			dir = RIGHT;
			return true;
		case 'w':
			dir = UP;
			return true;
		case 's':
			dir = DOWN;
			return true;
		default:
			dir = IDLE;
			return false;
		}
	}
}
void player::displayDir()
{
	switch (dir)
	{
	case LEFT:
		cout << "left" << endl;
		break;
	case RIGHT:
		cout << "right" << endl;
		break;
	case UP:
		cout << "up" << endl;
		break;
	case DOWN:
		cout << "down" << endl;
		break;
	}

}
