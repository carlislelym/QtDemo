#ifndef MYCANVAS_H
#define MYCANVAS_H

#include "myrectangle.h"
#include "myscene.h"
#include <QGraphicsView>

class MyCanvas : public QGraphicsView
{
    Q_OBJECT
    // 数据定义区
public:
    QPoint m_mousePos;
    int m_start_x;
    int m_start_y;
    QPoint m_movePos;
    bool readyMove;

private:
    MyScene *myScene;

    // 函数定义区
public:
    explicit MyCanvas(MyScene *scene, QGraphicsView *parent = 0);
    void paintEvent(QPaintEvent *) override;
    MyScene* scene();

public slots:
    void updateView();

protected:
    void mousePressEvent(QMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QMouseEvent *mouseEvent) override;

};

#endif // MYCANVAS_H
