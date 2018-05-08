#include "myitem.h"


MyItem::MyItem(int order)
{
    this->order = order;
    this->x = 0;
    this->y = 0;
    this->width = (10-order) * 10;
    this->height = (6-order) * 10;
    this->scope_x = this->x;
    this->scope_y = this->y;
    this->scope_width = this->width;
    this->scope_height = this->height;
    this->pre = NULL;
    this->next = QList<MyItem*>();

    this->isSelected = false;
}

MyItem::MyItem(int order, int x, int y)
{
    this->order = order;
    this->x = x;
    this->y = y;
    this->width = (10-order) * 10;
    this->height = (6-order) * 10;

    this->scope_x = this->x;
    this->scope_y = this->y;
    this->scope_width = this->width;
    this->scope_height = this->height;

    this->pre = NULL;
    this->next = QList<MyItem*>();

    this->isSelected = false;
}

MyItem::~MyItem()
{

}

int MyItem::getX()
{
    return this->x;
}

int MyItem::getY()
{
    return this->y;
}

void MyItem::setX(int x)
{
    this->x = x;
}

void MyItem::setY(int y)
{
    this->y = y;
}
