#ifndef REMOVECHIPBUTTON_H
#define REMOVECHIPBUTTON_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

#include "enums.h"

class RemoveChipButton : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit RemoveChipButton(QObject *parent = nullptr);

    void setColor(ChipColor color);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    ChipColor chipColor;
signals:
};

#endif // REMOVECHIPBUTTON_H
