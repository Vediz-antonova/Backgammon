#include "currentplayer.h"

CurrentPlayer::CurrentPlayer(QObject *parent)
    : QObject{parent}
{}

void CurrentPlayer::setColor(ChipColor color) {
    chipColor = color;

    update();
}

ChipColor CurrentPlayer::getColor(){
    return chipColor;
}

void CurrentPlayer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    Qt::GlobalColor color = chipColor == white ? Qt::white : Qt::black;
    Qt::GlobalColor borderColor = chipColor == white ? Qt::black : Qt::white;
    painter->setBrush(color);
    painter->setPen(borderColor);
    painter->drawEllipse(0, 0, CHIP_SIZE, CHIP_SIZE);
}

QRectF CurrentPlayer::boundingRect() const {
    return QRectF(0, 0, CHIP_SIZE, CHIP_SIZE);
}
