#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include <utility>
#include "chip.h"
#include "enums.h"

class Chip;

class Cell : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    Cell();
//    Cell(int id/*, int x, int y*/);
    ~Cell();

    int getId() const;
    void setId(int value);
//    int getX() const;
//    int getY() const;
    bool getSelected() const;
    void setSelected(bool value);
    bool getAvailableToMove();
    void setAvailableToMove(bool value);

    bool addChip(ChipColor color);
    bool removeChip();
    int getChipsCount() const;
    ChipColor getChipsColor() const;

    void setCallbackFunc(void (*func) (int id));

    bool canMoveTo(Chip* ch);
    bool containsChip(Chip* chip) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int id;
//    int x;
//    int y;
    ChipColor chipsColor;
    bool selected;
    bool availableToMove;
    int chipsCount;
    void (*callbackFunc)(int id) = 0;
    bool isTopRow();
    void drawChip(QPainter *painter, int pos);
    void drawAvailableMark(QPainter *painter);
    //std::pair<int, int> getChipPosition(bool isBlack) const;
};

#endif // CELL_H
