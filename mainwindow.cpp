#include "mainwindow.h"

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // 右侧画布
    scene = new MyScene(2000, 2000, this);
    canvas = new MyCanvas(scene);

    // 左侧控制键
    QWidget *tempWidget = new QWidget;
    QGridLayout *tempLayout = new QGridLayout;
    buttonAdd = new QPushButton("添加", tempWidget);
    connect(buttonAdd, SIGNAL(clicked(bool)),
            scene, SLOT(insertItem()));
    buttonDelete = new QPushButton("删除", tempWidget);
    connect(buttonDelete, SIGNAL(clicked(bool)),
            scene, SLOT(deleteItem()));
    buttonReset = new QPushButton("复位", tempWidget);
    connect(buttonReset, SIGNAL(clicked(bool)),
            scene, SLOT(resetItem()));
    tempLayout->addWidget(buttonAdd, 0, 0, 1, 1);
    tempLayout->addWidget(buttonDelete, 1, 0, 1, 1);
    tempLayout->addWidget(buttonReset, 2, 0, 1, 1);
    tempLayout->setRowStretch(3, 5);
    tempWidget->setLayout(tempLayout);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(tempWidget);

    layout->addWidget(canvas);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("Diagramscene"));
    setUnifiedTitleAndToolBarOnMac(true);
}


MainWindow::~MainWindow()
{

}
