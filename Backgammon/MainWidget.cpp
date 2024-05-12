#include "MainWidget.h"
#include "ui_MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->showMaximized();

    scene = new QGraphicsScene();
    cube1 = new Cube();
    cube2 = new Cube();
    cube1->setOtherCube(cube2);
    cube2->setOtherCube(cube1);

    moveIndicator = new MoveIndicator();
    scene->addItem(moveIndicator);

    QPixmap pixBoard("/home/vediz/OAiP/pictures/background.png");
    pixBoard = pixBoard.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixBoard);
    scene->addItem(item);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    /// Устанавливаем сглаживание
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    int num_chips = 15;
    int distance = 30;

    int x_black = 245;
    int y_black = scene->height() - 120;

    for (int i = 0; i < num_chips; i++) {
        Chip* chip = new Chip();

        chip->setPos(x_black, y_black - i * distance);
        scene->addItem(chip);
        chip->show();
        chip_black.push_back(chip);

        chip->setCube1(cube1);
        chip->setCube2(cube2);
    }
    int x_white = 1370;
    int y_white = 50;

    for (int i = 0; i < num_chips; i++) {
        Chip* chip = new Chip("white");

        chip->setPos(x_white, y_white + i * distance);
        scene->addItem(chip);
        chip->show();
        chip_white.push_back(chip);

        chip->setCube1(cube1);
        chip->setCube2(cube2);
    }

    scene->addItem(cube1);
    scene->addItem(cube2);
    cube1->show();
    cube2->show();
    cube1->setPos(scene->width()/2 - 120, scene->height()/2);
    cube2->setPos(scene->width()/2 + 60, scene->height()/2);

    timer = new QTimer();
    timer->start(1000 / 50);
}

MainWidget::~MainWidget()
{
    delete ui;
}
