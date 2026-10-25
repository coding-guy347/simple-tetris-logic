#pragma once
#include"tools.h"
#include<array>
#include<random>
#include<set>
using namespace std;
class Block
{
public:
	Block();
	void ReInit();
	void MoveLeft();
	void MoveRight();
	void MoveDown();
	void Spin();
	int Get_x() const;
	int Get_y() const;
	bool IsHitWall();
	bool Canmove();
	void SolidBlock();
	void SetCurrentShape(int index);
	void Render();
private:
	array<array<array<bool, 4>, 4>,7>shape;
	int x;
	int y;
	array<array<bool, 4>,4>CurrentShape;
};