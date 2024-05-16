#ifndef REMOVECHIPBUTTON_H
#define REMOVECHIPBUTTON_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

#include "enums.h"
#include "sizes.h"

class RemoveChipButton : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit RemoveChipButton(QObject *parent = nullptr);

    void setColor(ChipColor color);
    ChipColor getColor();
    void setMove(int value);
    int getMove();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void setCallbackFunc(void (*func) (int move));

private:
    ChipColor chipColor;
    void (*callbackFunc)(int move) = 0;
    int move;
};

#endif // REMOVECHIPBUTTON_H
