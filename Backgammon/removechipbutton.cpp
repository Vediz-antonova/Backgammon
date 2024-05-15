#include "removechipbutton.h"
#include "sizes.h"

RemoveChipButton::RemoveChipButton(QObject *parent)
    : QObject{parent}
{}

void RemoveChipButton::setColor(ChipColor color) {
    chipColor = color;
}

void RemoveChipButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(Qt::darkGreen);
    painter->setBrush(Qt::green);
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

}
