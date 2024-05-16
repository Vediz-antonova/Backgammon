#ifndef CURRENTPLAYER_H
#define CURRENTPLAYER_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

#include "enums.h"
#include "sizes.h"

class CurrentPlayer: public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit CurrentPlayer(QObject *parent = nullptr);

    void setColor(ChipColor color);
    ChipColor getColor();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    ChipColor chipColor;
};

#endif // CURRENTPLAYER_H
