#include "myline.h"

int MyLine::m_selectColor = Qt::red;
int MyLine::m_normalColor = Qt::black;
int MyLine::m_selectWidth = 5;
int MyLine::m_normalWidth= 3;

MyLine::MyLine(int order)
    : MyItem(order)
{
    this->gap = 50;
    this->type = Line;
    this->height = gap;
}

MyLine::MyLine(int order, int x, int y)
    : MyItem(order, x, y)
{
    this->gap = 50;
    this->type = Line;
    this->height = gap;
}

MyLine::~MyLine()
{

}

void MyLine::draw(QPainter &p)
{
    if (isSelected) {
        p.setPen(m_selectColor);
    } else {
        p.setPen(m_normalColor);
    }
    if (this->next.size() == 1) {
        int x_end = this->x;
        int y_end = this->next.first()->getY();
        p.drawLine(this->x, this->y, x_end, y_end);
    } else {
        int x_end = this->x;
        int y_end = this->y + this->height/2;
        p.drawLine(this->x, this->y, x_end, y_end);

        // 画出中间的横线
        p.drawLine(this->next.first()->getX()+this->next.first()->width/2, y_end,
                   this->next.last()->getX()+this->next.last()->width/2, y_end);
        foreach (MyItem *item, this->next) {
            p.drawLine(item->getX()+item->width/2, y_end,
                       item->getX()+item->width/2, item->getY());
        }
    }
}

void MyLine::changePos(int xMove, int yMove)
{
    this->x += xMove;
    this->y += yMove;
    this->scope_x += xMove;
    this->scope_y += yMove;
}
