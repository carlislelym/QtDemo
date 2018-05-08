#ifndef MYLINE_H
#define MYLINE_H

#include "myitem.h"

class MyLine : public MyItem
{
    // 数据定义区
public:
    int gap;
    static int m_selectColor;
    static int m_normalColor;
    static int m_selectWidth;
    static int m_normalWidth;

    // 函数定义区
public:
    MyLine(int order);
    MyLine(int order, int x, int y);

    ~MyLine();

    void draw(QPainter &p);
    void changePos(int xMove, int yMove);
};

#endif // MYLINE_H
