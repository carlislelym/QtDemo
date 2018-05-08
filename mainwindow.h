#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mycanvas.h"
#include "myscene.h"

#include <QButtonGroup>
#include <QGraphicsView>
#include <QMainWindow>
#include <QPushButton>

class DiagramScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    MyScene *scene;
    MyCanvas *canvas;

    QPushButton *buttonAdd;
    QPushButton *buttonDelete;
    QPushButton *buttonReset;

};

#endif // MAINWINDOW_H
