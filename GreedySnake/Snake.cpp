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
    currentDirection = Direction::RIGHT;	//��ʼ��������
    body.clear();
    body.push_back(CPoint(7, row));
	body.push_back(CPoint(6, row));
    body.push_back(CPoint(5, row));
}

void Snake::Move(CPoint food)
{
    // ��ȡ��ͷ��ǰλ��
    int headX = body.front().x;
    int headY = body.front().y;

    // �����ƶ����������ͷλ��
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

    //// �����ײ
    //if (CheckCollision(headX, headY)) {
    //    // ������ײ�߼���������Ϸ������
    //    return;
    //}

    // ����ͷǰ���һ���µĵ���Ϊ�µ���ͷ
    body.insert(body.begin(), CPoint(headX, headY));

    //�ж��Ƿ�Ե���ʳ��
    IsateFood(food, body.front());

    //�����û�гԵ�ʳ��Ƴ�β�����Ա����ߵĳ���
    if (!ateFood) {
        body.pop_back();
    }
}

bool Snake::CheckCollision() const
{
    // ��ȡ��ͷ��ǰλ��
    int x = body.front().x;
    int y = body.front().y;
    
    // ����Ƿ�ײǽ��������ͼ�ؼ���Χ��
    if (x < 0 || x >= 20 || y < 0 || y >= 20) {
        return true;
    }

    // ����Ƿ�ײ���Լ�������
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
    // ���ݵ�ǰ�ߵķ��򣬱���ֱ�ӷ�������ƶ�
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
    CBrush brush(color); // ʹ����ɫ��ˢ����������
    for (CPoint& point : body) {
        int left = point.x * BodySize; // ÿ������Ĵ�СΪBodySize*BodySize���������λ��
        int top = point.y * BodySize;
        int right = left + BodySize;
        int bottom = top + BodySize;
        pDC->SelectObject(&brush);
        pDC->Rectangle(left, top, right, bottom); // �����������һ����
    }
}

vector<CPoint> Snake::GetBody() const
{
    // TODO: �ڴ˴����� return ���
    return body;
}
