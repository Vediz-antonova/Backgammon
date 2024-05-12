#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QShortcut>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>

#include <cube.h>
#include <chip.h>
#include <moveindicator.h>

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
    Cube *cube1;
    Cube *cube2;
    std::vector<Chip*> chip_black;
    std::vector<Chip*> chip_white;
    QTimer *timer;
    MoveIndicator* moveIndicator;
};

#endif // MAINWIDGET_H
