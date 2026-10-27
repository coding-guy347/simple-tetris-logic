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
    vector<int>bag;//存放7种方块的索引
	random_device rd;
	mt19937 engine;
	uniform_int_distribution<int>dist{ 0,6 };
	State state=Menu;
public:
	Game() :engine(rd()){}
	void Run();
	void ReFillBag();//重新装填bag
	int NewIndex();//获取新的方块索引
	void RenderMap();
	void DeleteCol();//消除整行方块
};