#include "removechipbutton.h"

RemoveChipButton::RemoveChipButton(QObject *parent)
    : QObject{parent}
{}

void RemoveChipButton::setColor(ChipColor color) {
    chipColor = color;
}

ChipColor RemoveChipButton::getColor(){
    return chipColor;
}

void RemoveChipButton::setMove(int value){
    move = value;
}

int RemoveChipButton::getMove(){
    return move;
}

void RemoveChipButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::green);
    painter->setBrush(Qt::darkGreen);
    painter->drawEllipse(0, 0, REMOVE_BUTTON_SIZE, REMOVE_BUTTON_SIZE);

    Qt::GlobalColor color = chipColor == white ? Qt::white : Qt::black;
    painter->setPen(color);
    painter->setBrush(color);

    int centrePos = (REMOVE_BUTTON_SIZE - REMOVE_BUTTON_CENTRE_SIZE) / 2;
    painter->drawEllipse(centrePos, centrePos, REMOVE_BUTTON_CENTRE_SIZE, REMOVE_BUTTON_CENTRE_SIZE);
}

QRectF RemoveChipButton::boundingRect() const {
    return QRectF(0, 0, REMOVE_BUTTON_SIZE, REMOVE_BUTTON_SIZE);
}

void RemoveChipButton::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);

    if (callbackFunc) {
        callbackFunc(move);
    }
}

void RemoveChipButton::setCallbackFunc(void (*func) (int move)) {
    callbackFunc = func;
}
