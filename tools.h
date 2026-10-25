#pragma once
#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<array>
using namespace sf;
using namespace std;
extern RenderWindow window;
extern bool visited[15][15];
#define Map_Cols 15
#define Map_Rows 15
#define CellSize 50
#define Offset_X 0
#define Offset_y 50
void RenderRect(int x, int y, const array<Uint8,3>&color);
void SetFps();
int ToPixel_x();
int ToPixel_y();
void MatrixMultiply(array<array<bool,4>,4>a,array<array<bool,4>,4>&b);
void Normalization(array<array<bool, 4>, 4>& b);