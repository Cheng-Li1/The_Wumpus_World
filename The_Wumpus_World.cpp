#include "The_Wumpus_World.h"
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <time.h>
void Wumpus_World::sense()
{
	known[x][y].visited = 1;
	known[x][y].Breeze = world[x][y].Breeze;
	known[x][y].Stench = world[x][y].Stench;
	known[x][y].gold = world[x][y].gold;
	known[x][y].wum = world[x][y].wum;
	known[x][y].pit = world[x][y].pit;
	if (known[x][y].Stench == false && wum_killed == false)
	{
		if (x > 0)
		{
			known[x - 1][y].wum = 0;
		}
		if (x < 3)
		{
			known[x + 1][y].wum = 0;
		}
		if (y > 0)
		{
			known[x][y - 1].wum = 0;
		}
		if (y < 3)
		{
			known[x][y + 1].wum = 0;
		}
	}
	if (known[x][y].Stench == true)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (abs(i - x) + abs(j - y) != 1)
				{
					known[i][j].wum = 0;
				}
			}
		}
	}
    if (known[x][y].Breeze == false)
    {
		if (x > 0)
		{
			known[x - 1][y].pit = 0;
		}
		if (x < 3)
		{
			known[x + 1][y].pit = 0;
		}
		if (y > 0)
		{
			known[x][y - 1].pit = 0;
		}
		if (y < 3)
		{
			known[x][y + 1].pit = 0;
		}
	}
}
void Wumpus_World::act()
{
	int a;
	check();
	a = path_search();
	if (a == 0 && shoot_ == false)
	{
		a = shoot();
	}
	if (a == 0)
	{
		end = true;
	}
	sense();
	if (known[x][y].gold == true)
	{
		score += 1000;
		end = true;
	}
}
int Wumpus_World::path_search()
{
	int min = 100, xmov, ymov;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (known[i][j].pit == 0 && known[i][j].wum == 0 && known[i][j].visited == 0 && (min > abs(i - x) + abs(j - y)))
			{
				xmov = i;
				ymov = j;
				min = abs(i - x) + abs(j - y);
			}
		}
	}
	if (min == 100)
	{
		return 0;
	}
	if (x - xmov > 0 && known[x - 1][y].pit == 0 && known[x - 1][y].wum == 0 && known[x - 1][y].visited != 2)
	{
		x--;
		score--;
		std::cout << "Go Left" << std::endl;
		update(xmov, ymov);
		return 1;
	}
	if (x - xmov < 0 && known[x + 1][y].pit == 0 && known[x + 1][y].wum == 0 && known[x + 1][y].visited != 2)
	{
		x++;
		score--;
		std::cout << "Go Right" << std::endl;
		update(xmov, ymov);
		return 2;
	}
	if (y - ymov > 0 && known[x][y - 1].pit == 0 && known[x][y - 1].wum == 0 && known[x][y - 1].visited != 2)
	{
		y--;
		score--;
		std::cout << "Go Up" << std::endl;
		update(xmov, ymov);
		return 3;
	}
	if (y - ymov < 0 && known[x][y + 1].pit == 0 && known[x][y + 1].wum == 0 && known[x][y + 1].visited != 2)
	{
		y++;
		score--;
		std::cout << "Go Down" << std::endl;
		update(xmov, ymov);
		return 4;
	}
}
void Wumpus_World::check()
{
	int a = 0;
	if (x < 1 || (known[x - 1][y].pit == 0 && known[x - 1][y].wum == 0 && known[x - 1][y].visited == 2))
	{
		a++;
	}
	if (x > 3 || (known[x + 1][y].pit == 0 && known[x + 1][y].wum == 0 && known[x + 1][y].visited == 2))
	{
		a++;
	}
	if (y < 1 || (known[x][y - 1].pit == 0 && known[x][y - 1].wum == 0 && known[x][y - 1].visited == 2))
	{
		a++;
	}
	if (y > 3 || (known[x][y + 1].pit == 0 && known[x][y + 1].wum == 0 && known[x][y + 1].visited == 2))
	{
		a++;
	}
	if (a == 3)
	{
		known[x][y].visited = 2;
	}
}
void Wumpus_World::update(int a,int b)
{
	if (a == x && b == y)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (known[i][j].visited == 2)
				{
					known[i][j].visited = 1;
				}
			}
		}
	}
}
int Wumpus_World::shoot()
{
	int xmov = -1, ymov = -1, min = 100;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (known[i][j].Stench == 1 && min > abs(x - i) + abs(y - j))
			{
				min = abs(x - i) + abs(y - j);
				xmov = i, ymov = j;
			}
		}
	}
	if (min == 100)
	{
		shoot_ = true;
		return 0;
	}
	else if (x - xmov > 0 && known[x - 1][y].pit == 0 && known[x - 1][y].wum == 0 && known[x - 1][y].visited != 2)
	{
		x--;
		score--;
		std::cout << "Go Left" << std::endl;
		update(xmov, ymov);
	}
	else if (x - xmov < 0 && known[x + 1][y].pit == 0 && known[x + 1][y].wum == 0 && known[x + 1][y].visited != 2)
	{
		x++;
		score--;
		std::cout << "Go Right" << std::endl;
		update(xmov, ymov);
	}
	else if (y - ymov > 0 && known[x][y - 1].pit == 0 && known[x][y - 1].wum == 0 && known[x][y - 1].visited != 2)
	{
		y--;
		score--;
		std::cout << "Go Up" << std::endl;
		update(xmov, ymov);
	}
	else if (y - ymov < 0 && known[x][y + 1].pit == 0 && known[x][y + 1].wum == 0 && known[x][y + 1].visited != 2)
	{
		y++;
		score--;
		std::cout << "Go Down" << std::endl;
		update(xmov, ymov);
	}
	if (x == xmov && y == ymov)
	{
		score -= 10;
		if (x > 0 && known[x - 1][y].wum != 0)
		{
			std::cout << "Shoot Left" << std::endl;
			if (world[x - 1][y].wum == 2)
			{
				wum_killed = true;
			}
			else
			{
				known[x - 1][y].wum = 0;
			}
			shoot_ = true;
		}
		else if (x < 3 && known[x + 1][y].wum != 0)
		{
			std::cout << "Shoot Right" << std::endl;
			if (world[x + 1][y].wum == 2)
			{
				wum_killed = true;
			}
			else
			{
				known[x + 1][y].wum = 0;
			}
			shoot_ = true;
		}
		else if (y > 0 && known[x][y - 1].wum != 0)
		{
			std::cout << "Shoot Up" << std::endl;
			if (world[x][y - 1].wum == 2)
			{
				wum_killed = true;
			}
			else
			{
				known[x][y - 1].wum = 0;
			}
			shoot_ = true;
		}
		else if (y < 3 && known[x][y + 1].wum != 0)
		{
			std::cout << "Shoot Down" << std::endl;
			if (world[x][y + 1].wum == 2)
			{
				wum_killed = true;
			}
			else
			{
				known[x][y + 1].wum = 0;
			}
			shoot_ = true;
		}
		if (wum_killed == true)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					known[i][j].wum = 0;
					known[i][j].Stench = 0;
					world[i][j].wum = 0;
					world[i][j].Stench = 0;
				}
			}
		}
	}
}
void Wumpus_World::display(int a)
{
	struct room k[4][4];
	if (a == 0)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				k[i][j].Breeze = world[i][j].Breeze;
				k[i][j].pit = world[i][j].pit;
				k[i][j].gold = world[i][j].gold;
				k[i][j].Stench = world[i][j].Stench;
				k[i][j].wum = world[i][j].wum;
			}
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				k[i][j].Breeze = known[i][j].Breeze;
				k[i][j].pit = known[i][j].pit;
				k[i][j].gold = known[i][j].gold;
				k[i][j].Stench = known[i][j].Stench;
				k[i][j].wum = known[i][j].wum;
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			std::cout << "------------";
		}
		std::cout << std::endl;
		for (int j = 0; j < 4; j++)
		{
			if (k[j][i].wum == 2)
			{
				std::cout << "  Wumpus   |";
			}
			else if (k[j][i].Stench == 1)
			{
				std::cout << "  Stench   |";
			}
			else
			{
				std::cout << "           |";
			}
		}
		std::cout << std::endl;
		for (int j = 0; j < 4; j++)
		{
			if (k[j][i].pit == 2 && k[j][i].Breeze == 1)
			{
				std::cout << "pit Breeze |";
			}
			else if (k[j][i].pit == 2)
			{
				std::cout << "    pit    |";
			}
			else if (k[j][i].Breeze == 1)
			{
				std::cout << "  Breeze   |";
			}
			else
			{
				std::cout << "           |";
			}
		}
		std::cout << std::endl;
		for (int j = 0; j < 4; j++)
		{
			if (k[j][i].gold == 1)
			{
				std::cout << "   Gold    |";
			}
			else
			{
				std::cout << "           |";
			}
		}
		std::cout << std::endl;
		for (int j = 0; j < 4; j++)
		{
			if (j == x && i == y)
			{
				std::cout << "   You     |";
			}
			else
			{
				std::cout << "           |";
			}
		}
		std::cout << std::endl;
	}
}
void Wumpus_World::spawn()
{
	int a;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			world[i][j].Breeze = 0;
			world[i][j].gold = 0;
			world[i][j].pit = 0;
			world[i][j].Stench = 0;
			world[i][j].wum = 0;
			known[i][j].Breeze = 0;
			known[i][j].gold = 0;
			known[i][j].pit = 1;
			known[i][j].Stench = 0;
			known[i][j].wum = 1;
			known[i][j].visited = 0;
		}
	}
	srand(time(0));
	do
	{
		a = rand() % 16;
	} while ((a % 4 == 0 && a / 4 == 0) || world[a % 4][a / 4].pit == 2);
	world[a % 4][a / 4].gold = 1;
	for (int i = 0; i < 3; i++)
	{
		do
		{
			a = rand() % 16;
		} while ((a % 4 == 0 && a / 4 == 0) || world[a % 4][a / 4].pit == 2 || world[a % 4][a / 4].gold == 1);
		world[a % 4][a / 4].pit = 2;
		for (int j = a % 4 - 1; j < a % 4 + 2; j++)
		{
			if (j != -1 && j != 4 && j != a % 4)
			{
				world[j][a / 4].Breeze = 1;
			}
		}
		for (int k = a / 4 - 1; k < a / 4 + 2; k++)
		{
			if (k != -1 && k != 4 && k != a / 4)
			{
				world[a % 4][k].Breeze = 1;
			}
		}
	}
	do
	{
		a = rand() % 16;
	} while ((a % 4 == 0 && a / 4 == 0) || world[a % 4][a / 4].pit == 2);
	world[a % 4][a / 4].wum = 2;
	for (int j = a % 4 - 1; j < a % 4 + 2; j++)
	{
		if (j != -1 && j != 4 && j != a % 4)
		{
			world[j][a / 4].Stench = 1;
		}
	}
	for (int k = a / 4 - 1; k < a / 4 + 2; k++)
	{
		if (k != -1 && k != 4 && k != a / 4)
		{
			world[a % 4][k].Stench = 1;
		}
	}
}
int main()
{
	Wumpus_World w;
	w.spawn();
	w.sense();
	w.display(0);
	while (!w.end)
	{
		getchar();
		w.act();
		w.display(0);
	}
	std::cout << "score=" << w.score << std::endl;
	getchar();
}