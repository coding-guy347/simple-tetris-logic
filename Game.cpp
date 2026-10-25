#include"Game.h"

void Game::Run()
{
	window.setFramerateLimit(144);
	window.create(sf::VideoMode(1000, 800), "Russia Block");
	Block block;
	block.SetCurrentShape(NewIndex());
	Clock clock;
	double DropTime = 0.0f;
	double MoveTime = 0.0f;
	double DropTimeInterval = 0.5;
	double MoveTimeInterval=0.1;
	while (window.isOpen())
	{
		double dt = clock.restart().asSeconds();
		DropTime += dt;
		MoveTime += dt;
		Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Up)
				{
					block.Spin();
				}
				if (event.key.code==Keyboard::Down)
				{
					block.MoveDown();
				}
			}
		}
		if (MoveTime>= MoveTimeInterval)
		{
			MoveTime -= MoveTimeInterval;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				block.MoveLeft();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				block.MoveRight();
			}
		}
		if (DropTime >= DropTimeInterval)
		{
			DropTime -= DropTimeInterval;
			if(!block.Canmove())
			{
				block.SolidBlock();
				DeleteCol();
				block.SetCurrentShape(NewIndex());
				block.ReInit();
				if (!block.Canmove()) state = Ending;
			}
			block.MoveDown();
		}
		if (state == Ending) break;
		window.clear();
		block.Render();
		RenderMap();
		window.display();
	}
}

void Game::ReFillBag()
{
	if (bag.empty())
	{
		for (int i = 0;i < 7;i++)
		{
			bag.push_back(i);
		}
	}
	shuffle(bag.begin(), bag.end(), engine);
}

int Game::NewIndex()
{
	if (bag.empty())
	{
		ReFillBag();
	}
	int type = bag.back();
	bag.pop_back();
	return type;
}

void Game::RenderMap()
{
	for (int i = 0;i <Map_Rows;i++)
	{
		for (int j = 0;j < Map_Cols;j++)
		{
			if (visited[i][j] == true) RenderRect(j, i, { 200,180,200 });
		}
	}
}

void Game::DeleteCol()
{
	for (int row = Map_Rows - 1;row >= 0;row--)
	{
		bool isFull = true;
		for (int col = 0;col < Map_Cols;col++)
		{
			if (visited[row][col] == false)
			{
				isFull = false;
				break;
			}
		}
		if (isFull == true)
		{
			for (int r = row;r > 0;r--)
			{
				for (int c = 0;c < Map_Cols;c++)
				{
					visited[r][c] = visited[r - 1][c];
				}
			}
			for (int c = 0; c < Map_Cols; c++)
			{
				visited[0][c] = false;
			}
			row++;
		}
	}
}