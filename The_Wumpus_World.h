#pragma once
struct room
{
	short wum;
	short pit;
	short visited;
	bool Breeze;
	bool Stench;
	bool gold;
};
class Wumpus_World
{
private:
	struct room world[4][4];
	struct room known[4][4];
	short x = 0, y = 0;
	bool wum_killed = false;
	bool shoot_ = false;
public:
	void sense();
	void act();
	int path_search();
	int shoot();
	void check();
	void update(int a, int b);
	void display(int a);
	void spawn();
	bool end = false;
	int score = 0;
};