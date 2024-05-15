#ifndef CHIP_H
#define CHIP_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include "dice.h"
#include "cell.h"
#include "enums.h"

class MoveIndicator;
class Dice;
class Cell;

class Chip
{
//    Q_OBJECT
public:
 //   explicit Chip(QObject *parent = 0);
    explicit Chip(ChipColor c);
    ~Chip();

    void setCube1(Dice* c) { cube1 = c; }
    void setCube2(Dice* c) { cube2 = c; }

//    static Chip* selectedChip;

//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//    void drawChip(QPainter *painter);
//    QRectF boundingRect() const;
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    ChipColor getColor(){ return color; }

//    bool selected = false;

    std::vector<Cell*> calculateMoves();
    Cell* getCellInDirection(Chip* chip, int steps);
    Cell* getCurrentCell() const;
    void setCurrentCell(Cell* cell);
    void setMoveIndicator(MoveIndicator* moves);

private:
    MoveIndicator* moveIndicator;

    Dice* cube1;
    Dice* cube2;

    Cell* currentCell;

    ChipColor color;
    //bool isWhite;
};
#endif // CHIP_H
