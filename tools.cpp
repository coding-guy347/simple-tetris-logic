#include"tools.h"

RenderWindow window;
bool visited[15][15];

int ToPixel_x(int x)
{
	int newX = x * CellSize+Offset_X;
	return newX;
}

int ToPixel_y(int y)
{
	int newY = y * CellSize +Offset_y;
	return newY;
}

void RenderRect(int x, int y,const array<Uint8,3>&color)
{
	RectangleShape rect;
	rect.setPosition({ (float)ToPixel_x(x),(float)ToPixel_y(y)});
	rect.setSize({CellSize-1,CellSize-1});
	Color newcolor = { color[0],color[1],color[2],255 };
	rect.setFillColor(newcolor);
	rect.setOutlineColor(Color::Black);
	window.draw(rect);
}
