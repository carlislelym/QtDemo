#include <QDebug>
#include "myscene.h"

MyScene::MyScene(int w, int h, QObject *parent)
    : QGraphicsScene(parent)
{
    this->sizeWidth = w;
    this->sizeHeight = h;
    this->setSceneRect(QRectF(0, 0, w, h));
    this->m_start_x = sizeWidth / 2 - 50;
    this->m_start_y = sizeHeight / 2 - 200;
    this->gap = 50;
    newPos.setX(0);
    newPos.setY(0);
}

void MyScene::addItem(MyItem *myItem)
{
    this->headList.push_back(myItem);
    selectedItem = myItem;
}

bool MyScene::updateSelect()
{
    isSelect = false;
    foreach (MyItem *item, headList) {
        traverseAlltoUpdateSelect(item);
    }
    if (!isSelect)
        selectedItem = NULL;
    return isSelect;
}

void MyScene::traverseAlltoUpdateSelect(MyItem *item)
{
    if (item->next.size() <= 0) {
        // visit
        int pX = newPos.rx();
        int pY = newPos.ry();
        if (pX >= item->x && pX <= item->x + item->width
                && pY >= item->y && pY <= item->y + item->height) {
            selectedItem = item;
            item->isSelected = true;
            this->isSelect = true;
        } else {
            item->isSelected = false;
        }
        return;
    }
    foreach (MyItem *childItem, item->next) {
        traverseAlltoUpdateSelect(childItem);
    }
    // visit
    int pX = newPos.rx();
    int pY = newPos.ry();
    if (pX >= item->x && pX <= item->x + item->width
            && pY >= item->y && pY <= item->y + item->height) {
        selectedItem = item;
        item->isSelected = true;
        this->isSelect = true;
    } else {
        item->isSelected = false;
    }
}

bool MyScene::updatePos()
{
    // 首先更新所有节点的范围值
    foreach (MyItem *item, headList) {
        traverseAlltoUpdateScope(item);
    }
    // 根据范围值更新当前所有节点的位置
    foreach (MyItem *item, headList) {
//        // 添加节点之后判断是否超出scene，超出则进行调整
//        int value_x = this->width() - item->scope_x + item->width;
//        int value_y = this->height() - item->scope_y + item->height;
//        if (value_x < 0 || value_y < 0) {
//            // 判断调整之后范围值是否超出scene
//            value_x = (value_x < 0) ? value_x : 0;
//            value_y = (value_y < 0) ? value_y : 0;
//            if (item->scope_x+value_x < 0 || item->scope_y+value_y < 0)
//                return false;
//            traverseAlltoMoveScope(item, value_x, value_y);
//        }
        // 首先更新头节点的scope_x 与 scope_y
        item->scope_x = item->getX() - (item->scope_width - item->width) / 2;
        item->scope_y = item->getY();

        traverseAlltoUpdatePos(item);
    }
    return true;
}
// 更新每一个节点的范围值
void MyScene::traverseAlltoUpdateScope(MyItem *item)
{
    if (item->next.size() <= 0)
        return;
    // 统计scope
    item->scope_width = 0;
    item->scope_height = item->height;
    int max_height = 0;
    foreach (MyItem *childItem, item->next) {
        traverseAlltoUpdateScope(childItem);
        // visit
        item->scope_width += (childItem->scope_width + this->gap);
        if (childItem->scope_height > max_height)
            max_height = childItem->scope_height;
    }
    item->scope_width -= this->gap;
    item->scope_width = (item->scope_width > item->width) ? item->scope_width : item->width;
    item->scope_height += max_height;
}

void MyScene::traverseAlltoMoveScope(MyItem *item, int xMove, int yMove)
{
    if (item->next.size() <= 0) {
        // visit
        item->scope_x += xMove;
        item->scope_y += yMove;
        return;
    }
    foreach (MyItem *childItem, item->next) {
        traverseAlltoMove(childItem, xMove, yMove);
    }
    // visit
    item->scope_x += xMove;
    item->scope_y += yMove;
}

void MyScene::traverseAlltoUpdatePos(MyItem *item)
{
    // 更新自身的位置（x，y）
    item->setX(item->scope_x + (item->scope_width - item->width) / 2);
    item->setY(item->scope_y);
    //    if (item->type != Line) {   // 当前节点 不是线的时候直接更新 线 的位置

    // 当前为叶子节点
    if (item->next.size() == 0)
        return;
    // 更新叶子节点的x, y, scope_x与scope_y
    int mid_x = item->getX() + item->width / 2;
    MyItem *line = item->next.first();
    line->scope_x = mid_x - line->scope_width / 2;
    line->scope_y = item->scope_y + item->height;
    line->setX(mid_x);
    line->setY(line->scope_y);

    // 更新Line下 所有节点的 scope_x, scope_y
    int temp_x = line->scope_x;
    foreach (MyItem* childItem, line->next) {
        childItem->scope_x = temp_x;
        childItem->scope_y = line->scope_y + line->height;
        temp_x += childItem->scope_width + this->gap;
        traverseAlltoUpdatePos(childItem);
    }
}


void MyScene::drawAll(QPainter &painter)
{
    foreach (MyItem *item, headList) {
        traverseAlltoDraw(item, painter);
    }
}

void MyScene::traverseAlltoDraw(MyItem *item, QPainter &painter)
{
    if (item->next.size() <= 0) {
        // visit
        item->draw(painter);
        return;
    }
    foreach (MyItem *childItem, item->next) {
        traverseAlltoDraw(childItem, painter);
    }
    // visit
    item->draw(painter);
}

void MyScene::moveItem(int xMove, int yMove)
{
    foreach (MyItem *item, headList) {
        if (item->scope_x + xMove < 0 || item->scope_y + yMove < 0 ||
                item->scope_x + item->scope_width + xMove > this->width() ||
                item->scope_y + item->scope_height + yMove > this->height())
            continue;
        traverseAlltoMove(item, xMove, yMove);
    }
}

void MyScene::traverseAlltoMove(MyItem *item, int xMove, int yMove)
{
    if (item->next.size() <= 0) {
        // visit
        item->changePos(xMove, yMove);
        return;
    }
    foreach (MyItem *childItem, item->next) {
        traverseAlltoMove(childItem, xMove, yMove);
    }
    // visit
    item->changePos(xMove, yMove);
}

void MyScene::traverseAlltoDelete(MyItem *item)
{
    // 叶子节点时
    if (item->next.size() <= 0) {
        // visit
        // 当该节点为头节点时，把该节点从头节点List中去掉
        if (item->pre == NULL) {
            for (QList<MyItem*>::iterator t_it = this->headList.begin(); t_it != this->headList.end(); t_it++) {
                if (*t_it == item) {
                    this->headList.erase(t_it);
                    break;
                }
            }
            delete item;
            return;
        }
        // 把自己从父节点的nextList中去除，然后删除自己
        for (QList<MyItem*>::iterator t_it = item->pre->next.begin(); t_it != item->pre->next.end(); t_it++) {
            if (*t_it == item) {
                item->pre->next.erase(t_it);
                delete item;
                return;
            }
        }
    }
    foreach (MyItem *childItem, item->next) {
        traverseAlltoDelete(childItem);
    }
    // visit
    // 当该节点为头节点时，把该节点从头节点List中去掉
    if (item->pre == NULL) {
        for (QList<MyItem*>::iterator t_it = this->headList.begin(); t_it != this->headList.end(); t_it++) {
            if (*t_it == item) {
                this->headList.erase(t_it);
                break;
            }
        }
        delete item;
        return;
    }
    // 把自己从父节点的nextList中去除，然后删除自己
    for (QList<MyItem*>::iterator t_it = item->pre->next.begin(); t_it != item->pre->next.end(); t_it++) {
        if (*t_it == item) {
            item->pre->next.erase(t_it);
            delete item;
            return;
        }
    }
}

void MyScene::insertItem()
{
    if (selectedItem == NULL) {    // 若当前没有选中Item，则在新的位置 新添加一个HeadItem
        MyRectangle *head = new MyRectangle(0, newPos.rx(), newPos.ry());
        // 检查当前位置能否添加该元素
        if (head->scope_x < 0 || head->scope_y < 0 ||
                head->scope_x + head->scope_width > this->width() ||
                head->scope_y + head->scope_height > this->height()) {
            delete head;
            qDebug() << "添加失败\n";
        } else {
            headList.push_back(head);
            selectedItem = head;
            selectedItem->isSelected = true;
            emit readyToUpdate();
        }
    } else {                       // 若选中Item，则在该Item下插入Item
        if (selectedItem->order < 5) {
            if (selectedItem->next.size() == 0) {   // 当前Item为叶子节点，给其赋予线
                MyLine *line = new MyLine(selectedItem->order+1,
                                          selectedItem->getX(), selectedItem->getY()+selectedItem->height);
                MyRectangle *subItem = new MyRectangle(selectedItem->order+1,
                                                       selectedItem->getX(), selectedItem->getY()+selectedItem->height + this->gap);
                line->pre = selectedItem;
                line->next.push_back(subItem);
                subItem->pre = line;
                selectedItem->next.push_back(line);
                if (!updatePos()) {
                    qDebug() << "添加失败!!\n" ;
                    selectedItem->next.pop_back();
                    delete line;
                    delete subItem;
                } else {
                    qDebug() << "添加成功!!\n";
                }
            } else {       // 当前Item非叶子，直接添加子节点
                MyRectangle *subItem = new MyRectangle(selectedItem->order+1,
                                                       selectedItem->getX(), selectedItem->getY()+selectedItem->height + this->gap);
                subItem->pre = selectedItem->next.first();
                selectedItem->next.first()->next.push_back(subItem);
                if (!updatePos()) {
                    qDebug() << "添加失败!!!\n" ;
                    selectedItem->next.first()->next.pop_back();
                    delete subItem;
                } else {
                    qDebug() << "添加成功!!!\n";
                }
            }
            emit readyToUpdate();
        }
    }
}

void MyScene::deleteItem()
{
    if (selectedItem != NULL) {    // 若选中Item，则直接删除该Item
        traverseAlltoDelete(selectedItem);
        selectedItem = NULL;
        this->updatePos();
        emit readyToUpdate();
    }
}

void MyScene::resetItem()
{
    if (this->headList.size() <= 0)
        return;
    int xMove = m_start_x - this->headList.first()->getX();
    int yMove = m_start_y - this->headList.first()->getY();
    this->moveItem(xMove, yMove);
    emit readyToUpdate();
}
