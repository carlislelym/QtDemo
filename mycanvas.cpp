#include "mycanvas.h"
#include <QDebug>

MyCanvas::MyCanvas(MyScene *scene, QGraphicsView *parent)
    : QGraphicsView(scene, parent)
{
    this->myScene = scene;
    connect(scene, SIGNAL(readyToUpdate()),
            this, SLOT(updateView()));
    m_start_x = scene->sizeWidth / 2 - 50;
    m_start_y = scene->sizeHeight / 2 - 200;
    MyRectangle *head = new MyRectangle(0, m_start_x, m_start_y);
    this->scene()->addItem(head);
    head->isSelected = true;
    readyMove = false;
}

void MyCanvas::mousePressEvent(QMouseEvent *event)
{
    m_mousePos = event->pos();
    m_movePos = event->pos();
    this->scene()->selectedItem = NULL;
    // 获取到scene中的坐标
    QPointF locPos = event->localPos();
    QTransform tmpTransform = this->viewportTransform().inverted();
    locPos = tmpTransform.map(locPos);

    this->scene()->newPos.setX(locPos.rx());
    this->scene()->newPos.setY(locPos.ry());

    readyMove = this->scene()->updateSelect();
    viewport()->update();
}

void MyCanvas::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    QPoint nowPoint = mouseEvent->pos();
    QPoint gap = nowPoint - m_movePos;
    if ( readyMove && (gap.rx() > 3 || gap.rx() < -3 ||
            gap.ry() > 3 || gap.ry() < -3)) {
        this->scene()->moveItem(gap.rx(), gap.ry());
        // 更新m_movePos
        m_movePos = nowPoint;
        viewport()->update();
    }
}

void MyCanvas::mouseReleaseEvent(QMouseEvent *mouseEvent)
{

}

void MyCanvas::paintEvent(QPaintEvent *)
{
    QPainter painter(viewport());
    painter.setWorldTransform(this->viewportTransform());
    this->scene()->drawAll(painter);
    viewport()->update();
}

MyScene* MyCanvas::scene()
{
    return this->myScene;
}

void MyCanvas::updateView()
{
    viewport()->update();
}
