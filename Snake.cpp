#include "Snake.h"

Snake::Snake()
{
    head.x = 0;
    head.y = 0;
    body.emplace_front(head);
}

void Snake::move(int deltaX, int deltaY)
{
    previousEnd = body.back();
    body.pop_back();
    head = Cord(head.x + deltaX, head.y + deltaY);
    body.emplace_front(head);
}

const Snake::Cord Snake::getHead() const
{
    return head;
}

const std::list<Snake::Cord> Snake::getSnake() const
{
    return body;
}

void Snake::reset()
{
    body.clear();
    head.x = 0;
    head.y = 0;
    body.emplace_front(head);
}

void Snake::grow()
{
    body.emplace_back(previousEnd);
}

bool Snake::containsCord(Cord cord) const
{
    for (Cord c : body)
    {
        if (c.x == cord.x && c.y == cord.y)
        {
            return true;
        }
   }
    return false;
}

bool Snake::headIntersectsBody() const
{
    auto iter = body.begin();
    auto end = body.end();
    if (iter != end) iter++;

    while (iter != end)
    {
        Cord cord = *iter;
        if (cord.x == head.x && cord.y == head.y)
        {
            return true;
        }
        iter++;
    }
    return false;
}
