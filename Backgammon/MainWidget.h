#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWidget;
}
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

private slots:

private:
    Ui::MainWidget *ui;
    QGraphicsScene *scene;
    Game *game;
    QTimer *timer;
};

#endif // MAINWIDGET_H
