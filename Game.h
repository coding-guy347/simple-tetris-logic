#pragma once
#include"tools.h"
#include"tools.h"
#include"Block.h"
#include<random>
#include<algorithm>
using namespace std;

class Game {
private:
	enum State
	{
		Menu,
		Playing,
		Ending
	};
    vector<int>bag;
	random_device rd;
	mt19937 engine;
	uniform_int_distribution<int>dist{ 0,6 };
	State state=Menu;
public:
	Game() :engine(rd()){}
	void Run();
	void ReFillBag();
	int NewIndex();
	void RenderMap();
	void DeleteCol();
};