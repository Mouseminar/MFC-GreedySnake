#include "pch.h"
#include "Snake.h"

Snake::Snake()
{
}

Snake::~Snake()
{
}

void Snake::Init(int row)
{
    ateFood = false;
    currentDirection = Direction::RIGHT;	//初始方向：向右
    body.clear();
    body.push_back(CPoint(7, row));
	body.push_back(CPoint(6, row));
    body.push_back(CPoint(5, row));
}

void Snake::Move(CPoint food)
{
    // 获取蛇头当前位置
    int headX = body.front().x;
    int headY = body.front().y;

    // 根据移动方向更新蛇头位置
    switch (currentDirection) {
    case Direction::UP:
        headY--;
        break;
    case Direction::DOWN:
        headY++;
        break;
    case Direction::LEFT:
        headX--;
        break;
    case Direction::RIGHT:
        headX++;
        break;
    }

    //// 检查碰撞
    //if (CheckCollision(headX, headY)) {
    //    // 处理碰撞逻辑，例如游戏结束等
    //    return;
    //}

    // 在蛇头前添加一个新的点作为新的蛇头
    body.insert(body.begin(), CPoint(headX, headY));

    //判断是否吃到了食物
    IsateFood(food, body.front());

    //如果蛇没有吃到食物，移除尾部点以保持蛇的长度
    if (!ateFood) {
        body.pop_back();
    }
}

bool Snake::CheckCollision() const
{
    // 获取蛇头当前位置
    int x = body.front().x;
    int y = body.front().y;
    
    // 检查是否撞墙（超出绘图控件范围）
    if (x < 0 || x >= 20 || y < 0 || y >= 20) {
        return true;
    }

    // 检查是否撞到自己的身体
    for (size_t i = 1; i < body.size(); ++i) {
        if (body[i].x == x && body[i].y == y) {
            return true;
        }
    }

    return false;
}

void Snake::IsateFood(CPoint food, CPoint head)
{
    if (food == head)
        ateFood = true;
    else
        ateFood = false;
}

void Snake::SetDirection(Direction dir)
{
    // 根据当前蛇的方向，避免直接反方向的移动
    if ((dir == Direction::UP && currentDirection != Direction::DOWN) ||
        (dir == Direction::DOWN && currentDirection != Direction::UP) ||
        (dir == Direction::LEFT && currentDirection != Direction::RIGHT) ||
        (dir == Direction::RIGHT && currentDirection != Direction::LEFT)) {
        currentDirection = dir;
    }
}

void Snake::AutoMoveToFood(CPoint food)
{
    int headX = body.front().x;
    int headY = body.front().y;
    int foodX = food.x;
    int foodY = food.y;

    if (headX < foodX && currentDirection != Direction::LEFT) {
        currentDirection = Direction::RIGHT;
    }
    else if (headX > foodX && currentDirection != Direction::RIGHT) {
        currentDirection = Direction::LEFT;
    }
    else if (headY < foodY && currentDirection != Direction::UP) {
        currentDirection = Direction::DOWN;
    }
    else if(headY > foodY && currentDirection != Direction::DOWN)
    {
        currentDirection = Direction::UP;
    }
    else if(currentDirection != Direction::DOWN)
    {
        currentDirection = Direction::UP;
    }
    else
    {
        currentDirection = Direction::LEFT;
    }
}

void Snake::Draw(CDC* pDC, COLORREF color)
{
    CBrush brush(color); // 使用绿色画刷绘制蛇身体
    for (CPoint& point : body) {
        int left = point.x * BodySize; // 每节身体的大小为BodySize*BodySize，计算绘制位置
        int top = point.y * BodySize;
        int right = left + BodySize;
        int bottom = top + BodySize;
        pDC->SelectObject(&brush);
        pDC->Rectangle(left, top, right, bottom); // 绘制蛇身体的一个节
    }
}

vector<CPoint> Snake::GetBody() const
{
    // TODO: 在此处插入 return 语句
    return body;
}
