#ifndef MYRECTANGLE_H
#define MYRECTANGLE_H

#include "myitem.h"
#include <QPen>
#include <QBrush>

class MyRectangle : public MyItem
{
    // 数据定义区
public:
    static int m_selectColor;
    static int m_normalColor;
    static int m_selectWidth;
    static int m_normalWidth;

    // 函数定义区
public:
    MyRectangle(int order, int x, int y);
    MyRectangle(int order);

    ~MyRectangle();

    void draw(QPainter &p);
    void changePos(int xMove, int yMove);
};


#endif // MYRECTANGLE_H
