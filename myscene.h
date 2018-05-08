#ifndef MYSCENE_H
#define MYSCENE_H
#include "myrectangle.h"
#include "myline.h"
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class MyScene : public QGraphicsScene
{
    Q_OBJECT
    // 数据定义区
public:
    QList<MyItem*> headList;
    MyItem *selectedItem;
    int sizeWidth;
    int sizeHeight;
    int gap;
    QPoint newPos;
    int m_start_x;
    int m_start_y;

    bool isSelect;

    // 函数定义区
public:
    explicit MyScene(int w, int h, QObject *parent = 0);
    void addItem(MyItem *myItem);
    bool updateSelect();
    void drawAll(QPainter &painter);
    void moveItem(int xMove, int yMove);

private:
    void traverseAlltoUpdateSelect(MyItem *item);
    bool updatePos();
    void traverseAlltoUpdateScope(MyItem *item);
    void traverseAlltoMoveScope(MyItem *item, int xMove, int yMove);
    void traverseAlltoUpdatePos(MyItem *item);
    void traverseAlltoDraw(MyItem *item, QPainter &painter);
    void traverseAlltoMove(MyItem *item, int xMove, int yMove);
    void traverseAlltoDelete(MyItem *item);

signals:
    void readyToUpdate();

public slots:
    void insertItem();
    void deleteItem();
    void resetItem();
};

#endif // MYSCENE_H
