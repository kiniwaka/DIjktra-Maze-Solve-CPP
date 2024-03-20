#include"map.h"
#include <iostream>
#include <iomanip>
#include <fstream>  
#include "stdlib.h"
#include "conio.h"
#include "windows.h"
#include "gameMaze.h"
using namespace std;
string* txtToSource(fstream& file, int& k)
{
	string temp;
	string* t;
	k = 0;
	while(getline(file, temp))
	{
		k++;
	}
	file.clear();
	file.seekg(0);
	t = new string[k];
	int i = 0;
	while (getline(file, temp))
	{
		t[i] = temp;
		i++;
	}
	return t;
};

void main()
{
	cout << "Welcome to Anthony Lopez's maze project" << endl;
	Sleep(1000);
	system("cls");
	bool end = false;
	int choice;
	string mapName;
	string* mapSource;
	fstream file;
	while (!end)
	{
		system("cls");
		cout << "1-> choose map" << endl;
		cout << "2-> exit" << endl;
		if (!(cin >> choice))
		{
			cout<<"invalid option"<<endl;
			cin.clear();
			cin.get();
		}
		switch (choice)
		{
		case 1:
			system("cls");
			int choi;
			cout << "select which map you want to load: "<<endl;
			cout << "1 -> TRAPPED" << endl;
			cout << "2 -> tiny forest" << endl;
			cout << "3 -> split" << endl;
			cout << "4 -> Big teleporter frenzy" << endl;
			cout << "5 -> big forest" << endl;
			cin >> choi;
			switch (choi)
			{
			case 1:
				mapName = "testMap.txt";
				break;
			case 2: 
				mapName = "testMap2.txt";
				break;
			case 3:
				mapName = "testMap3.txt";
				break;
			case 4:
				mapName = "testMap4.txt";
				break;
			case 5:
				mapName = "testMap5.txt";
				break;
			default: 
				break;
			}
			cout << '\n'<< "loading map: " << mapName<<endl;
			system("cls");

			file.open(mapName, ios::in);
			if (file.is_open())
			{
				int C;
				int k;
				mapSource = txtToSource(file, k);
				map current = map(mapSource[0].length(), k);
				pair<player, map>a;
				a = current.loadMap(mapSource);
				gameMaze* game = new gameMaze(a.second, a.first);
				RETRY:
				bool choice = false;
				while (!choice)
				{
					system("cls");
					cout << "Choose if you want to play or if you want Djikstra to play!" << endl;
					cout << "'1' for you to play" << endl;
					cout << "'2' for Djikstra" << endl;
					if (!(cin >> C))
					{
						cout << "invalid option" << endl;
						cin.clear();
						cin.get();
					}
					else
						choice = true;
				}
				cout << C << endl;
				switch (C)
				{
				case 1:
					game->play();
					break;
				case 2:
					game->cpuPlay();
					break;
				default:
					goto RETRY;
					break;
				}
				file.close();
				delete game;
			
			}
			else
				cout << "map does not exist" << endl;

			break;
		case 2:
			system("cls");
			cout << "thanks for playing!";
			end = true;
			break;
		default: 
			break;
		}
	}

}