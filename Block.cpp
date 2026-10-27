#include"Block.h"

Block::Block()
{ 
    x = 5;
    y = 0;//初始坐标
    // 初始化七种方块的形状
    shape[0] =
    {{
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}
    }};

    shape[1] =
    { {
        {0,0,0,0},
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0}
    } };

    shape[2] =
    { {
        {0,0,0,0},
        {1,1,1,0},
        {1,0,0,0},
        {0,0,0,0}
    } };

    shape[3] =
    { {
        {0,0,0,0},
        {0,1,1,1},
        {0,0,0,1},
        {0,0,0,0}
    } };

    shape[4] =
    { {
        {0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}
    } };

    shape[5] =
    { {
        {0,0,0,0},
        {0,0,1,0},
        {0,1,1,0},
        {0,1,0,0}
    } };

    shape[6] =
    { {
        {0,0,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,1,0}
    } };
}

int Block::Get_x()const
{
    return x;
}

int Block::Get_y()const
{
    return y;
}
//旋转
void Block::Spin()
{
    std::array<std::array<bool, 4>, 4> rotated{};

    // 1. 纯数学旋转
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (CurrentShape[r][c]) {
                rotated[c][3 - r] = true;
            }
        }
    }

    // 2. 判断它是不是长条
    bool isI = false;
    // 只要它全占满了一行或一列，就是长条
    if (CurrentShape[1] == std::array<bool, 4>{true, true, true, true} ||
        CurrentShape[0][1] && CurrentShape[1][1] && CurrentShape[2][1] && CurrentShape[3][1])
    {
        isI = true;
    }

    // 3. 只有非长条的方块，才做居中补偿
    if (!isI) {
        int min_x = 4, min_y = 4, max_x = -1, max_y = -1;
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                if (rotated[r][c]) {
                    if (r < min_x) min_x = r;
                    if (r > max_x) max_x = r;
                    if (c < min_y) min_y = c;
                    if (c > max_y) max_y = c;
                }
            }
        }
        int width = max_x - min_x + 1;
        int height = max_y - min_y + 1;

        std::array<std::array<bool, 4>, 4> centered{};
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                if (rotated[r][c]) {
                    int offsetX = (4 - width) / 2;
                    int offsetY = (4 - height) / 2;
                    centered[(r - min_x) + offsetX][(c - min_y) + offsetY] = true;
                }
            }
        }
        for (int i = 0;i < 4;i++)
        {
            for (int j = 0;j < 4;j++)
            {
                if (centered[i][j] == true)
                {
                    if (x + j - 1 < 0||x+j+1>=Map_Cols||y+i+1>Map_Rows||y+i-1<0) return;
                }
            }
        }
        CurrentShape = centered; // 普通方块：居中
    }
    else {
        for (int i = 0;i < 4;i++)
        {
            for (int j = 0;j < 4;j++)
            {
                if (rotated[i][j] == true)
                {
                    if (x + j -1< 0 || x + j+1 >=Map_Cols||y+i-1<0||y+i+1>=Map_Rows) return;
                }
            }
        }
        CurrentShape = rotated;  // 长条：绝对不居中，直接原样转！
    }
}
//设置当前方块的形状
void Block::SetCurrentShape(int index)
{
    CurrentShape = shape[index];
}
//左移
void Block::MoveLeft()
{
    for (int i = 0;i < 4;i++)
    {
        for (int j = 0;j < 4;j++)
        {
            if (CurrentShape[i][j] == true)
            {
                if (x + j - 1 < 0||visited[y+i][x+j-1]) return;
            }
        }
    }
    x--;
}
//右移
void Block::MoveRight()
{
    for (int i = 0;i < 4;i++)
    {
        for (int j = 0;j < 4;j++)
        {
            if (CurrentShape[i][j] == true)
            {
                if (x + j + 1 >= Map_Cols||visited[y+i][x+j+1]) return;
            }
        }
    }
    x++;
}
//下坠
void Block::MoveDown()
{
    if (!Canmove()) return;
    y++;
}
//渲染方块
void Block::Render()
{
    for (int i = 0;i < 4;i++)
    {
        for (int j = 0;j < 4;j++)
        {
            if (CurrentShape[i][j] == true)
            {
                int new_x = x + j;
                int new_y = y + i;
                RenderRect(new_x, new_y, { 200,180,200 });
            }
        }
    }
}
//判断是否可以移动
bool Block::Canmove()
{
    bool canMove = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (CurrentShape[i][j]) {
                int nextY = y+ 1 + i;
                //如果下一个位置超出边界或者已经被占用，则不能移动
                if (nextY >= Map_Rows || visited[y+1+i][x + j]) {
                    canMove = false;
                    break;
                }
            }
        }
    }
    return canMove;
}
//重新初始化
void Block::ReInit()
{
    x = 5;
    y = 0;
}
//固化方块
void Block::SolidBlock()
{
    for (int i = 0;i < 4;i++)
    {
        for (int j = 0;j < 4;j++)
        {
            if (CurrentShape[i][j] == true)
            {
                visited[y+i][x+j] = true;
            }
        }
    }
}
   
   
