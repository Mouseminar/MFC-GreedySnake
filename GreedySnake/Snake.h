#pragma once

#define BodySize 40

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake
{
public:
    Snake();
    ~Snake();

    void Init(int row);
    void Move(CPoint food);
    bool CheckCollision() const;
    void IsateFood(CPoint food, CPoint head);
    void SetDirection(Direction dir);
    void AutoMoveToFood(CPoint food);
    void Draw(CDC* pDC, COLORREF color);

    vector<CPoint> GetBody() const;

    bool ateFood;

private: 
    vector<CPoint> body;
    Direction currentDirection;
};

