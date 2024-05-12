#ifndef CHIP_H
#define CHIP_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include <moveindicator.h>
#include <cube.h>

class Cube;

class Chip : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Chip(QObject *parent = 0);
    explicit Chip(QString c, QObject *parent = 0);
    ~Chip();

    void setCube1(Cube* c) { cube1 = c; }
    void setCube2(Cube* c) { cube2 = c; }

    std::vector<std::pair<int, int>> calculatePossibleMoves();

    static Chip* selectedChip;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void drawChip(QPainter *painter);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    QString getColor(){ return color; }

    bool selected = false;

private:
    Cube* cube1;
    Cube* cube2;

    QString color;
};
#endif // CHIP_H
