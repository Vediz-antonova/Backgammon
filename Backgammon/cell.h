#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

#include <utility>
#include "enums.h"
#include "sizes.h"

class Cell : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    Cell();
    ~Cell();

    int getId() const;
    void setId(int value);
    bool getSelected() const;
    void setSelected(bool value);
    bool getAvailableToMove();
    void setAvailableToMove(bool value);

    bool addChip(ChipColor color);
    bool removeChip();
    int getChipsCount() const;
    ChipColor getChipsColor() const;

    void setCallbackFunc(void (*func) (int id));

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int id;
    ChipColor chipsColor;
    bool selected;
    bool availableToMove;
    int chipsCount;
    void (*callbackFunc)(int id) = 0;
    bool isTopRow();
    void drawChip(QPainter *painter, int pos);
    void drawAvailableMark(QPainter *painter);
};

#endif // CELL_H
