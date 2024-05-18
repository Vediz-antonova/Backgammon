#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QResizeEvent>

#include "game.h"
#include "rulesscreen.h"

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

    void setTwoPlayers(bool value);

private:
    Ui::MainWidget *ui;
    QGraphicsScene *scene;
    Game *game;
};

#endif // MAINWIDGET_H
