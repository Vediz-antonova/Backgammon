#include "dice.h"

Dice::Dice(QObject *parent) : QObject(parent), QGraphicsItem()
{
    setValue(1);
    setEnabled(true);
}

Dice::~Dice(){}

bool Dice::isWhiteTurn = true;

void Dice::setValue(int new_value) {
    diceValue = new_value;
    update();
}

int Dice::getValue() { return diceValue; }

void Dice::setEnabled(bool value) {
    enabled = value;
    update();
}

bool Dice::getEnabled() {
    return enabled;
}

/*
void Dice::setPlayed(bool value) {
    played = value;
    update();
}

bool Dice::getPlayed() {
    return played;
}
*/

void Dice::setCallbackFunc(void (*func) ()) {
    callbackFunc = func;
}

void Dice::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(enabled ? Qt::white : Qt::gray);

    painter->setPen(Qt::black);
    painter->drawRect(0, 0, DICE_SIZE, DICE_SIZE);

    painter->setPen(Qt::black);
    painter->setBrush(Qt::black);
    if (getValue() == 1 || getValue() == 3 || getValue() == 5) {
        painter->drawEllipse(QPointF(DICE_SIZE/2, DICE_SIZE/2), DICE_DOT_SIZE, DICE_DOT_SIZE); // центральная точка
    }
    if (getValue() >= 2) {
        painter->drawEllipse(QPointF(DICE_DOT_L, DICE_DOT_L), DICE_DOT_SIZE, DICE_DOT_SIZE); // верхний левый угол
        painter->drawEllipse(QPointF(DICE_DOT_R, DICE_DOT_R), DICE_DOT_SIZE, DICE_DOT_SIZE); // нижний правый угол
    }
    if (getValue() >= 4) {
        painter->drawEllipse(QPointF(DICE_DOT_R, DICE_DOT_L), DICE_DOT_SIZE, DICE_DOT_SIZE); // верхний правый угол
        painter->drawEllipse(QPointF(DICE_DOT_L, DICE_DOT_R), DICE_DOT_SIZE, DICE_DOT_SIZE); // нижний левый угол
    }
    if (getValue() == 6) {
        painter->drawEllipse(QPointF(DICE_DOT_L, DICE_SIZE/2), DICE_DOT_SIZE, DICE_DOT_SIZE); // левая сторона
        painter->drawEllipse(QPointF(DICE_DOT_R, DICE_SIZE/2), DICE_DOT_SIZE, DICE_DOT_SIZE); // правая сторона
    }
}

QRectF Dice::boundingRect() const
{
    return QRectF(0, 0, DICE_SIZE, DICE_SIZE);
}

void Dice::Game()
{
    setValue(QRandomGenerator::global()->bounded(1, 7));
    update();
}

void Dice::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);

    if (enabled && callbackFunc) {
        callbackFunc();
    }
}
