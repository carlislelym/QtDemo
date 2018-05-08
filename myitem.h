#ifndef MYITEM_H
#define MYITEM_H

#include <QList>
#include <QPainter>
enum DiagramType { Rectangle, Triangle, Circle, Line };
class MyItem
{
    // 数据定义区
public:
    int order;
    int x;
    int y;
    int width;
    int height;
    int scope_x;
    int scope_y;
    int scope_height;
    int scope_width;
    DiagramType type;
    MyItem *pre;
    QList<MyItem*> next;

    bool isSelected;


    // 函数定义区
public:
    MyItem(int order);
    MyItem(int order, int x, int y);
    virtual ~MyItem();
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);

    virtual void draw(QPainter &p) = 0;
    virtual void changePos(int xMove, int yMove) = 0;
};

#endif // MYITEM_H
