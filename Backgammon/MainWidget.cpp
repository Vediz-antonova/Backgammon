#include "MainWidget.h"
#include "ui_MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->showMaximized();

    scene = new QGraphicsScene();

    QPixmap pixBoard("/home/vediz/OAiP/pictures/background.png");
    pixBoard = pixBoard.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem(pixBoard);
    scene->addItem(item);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    game = &Game::getInstance();
    Game::getInstance().setScene(scene);
    Game::getInstance().startNewGame();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::setTwoPlayers(bool value){
    Game::getInstance().setTwoPlayers(value);
}
