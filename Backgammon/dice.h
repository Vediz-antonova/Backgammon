#ifndef DICE_H
#define DICE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>

#include "sizes.h"

class Dice : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    explicit Dice(QObject *parent = 0);
    ~Dice();

    static bool isWhiteTurn;

    void setValue(int new_value);
    int getValue();

    void setEnabled(bool value);
    bool getEnabled();

/*
    void setPlayed(bool value);
    bool getPlayed();
*/
    void setCallbackFunc(void (*func) ());

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void Game();

protected:
    int diceValue;
    bool enabled;
//    bool played;
    void (*callbackFunc)() = 0;
};

#endif // DICE_H
