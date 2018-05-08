#include "myrectangle.h"
int MyRectangle::m_selectColor = Qt::red;
int MyRectangle::m_normalColor = Qt::black;
int MyRectangle::m_selectWidth = 5;
int MyRectangle::m_normalWidth= 3;

MyRectangle::MyRectangle(int order, int x, int y)
    : MyItem(order, x, y)
{
    this->type = Rectangle;
}

MyRectangle::MyRectangle(int order)
    : MyItem(order)
{
    this->type = Rectangle;
}

void MyRectangle::draw(QPainter &p)
{
    if (isSelected) {
        p.setPen(QPen(Qt::blue,4,Qt::DashLine));
    } else {
        p.setPen(QPen(Qt::black,3,Qt::DashLine));
    }
    p.drawRect(this->x, this->y, this->width, this->height);
}

void MyRectangle::changePos(int xMove, int yMove)
{
    this->scope_x += xMove;
    this->scope_y += yMove;
    this->x += xMove;
    this->y += yMove;
}

MyRectangle::~MyRectangle()
{

}
