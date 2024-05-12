#include "moveindicator.h"

MoveIndicator::MoveIndicator(QObject *parent) : QObject(parent), QGraphicsItem()
{
    visible = false;
}

MoveIndicator::~MoveIndicator(){}

void MoveIndicator::setMoves(const std::vector<std::pair<int, int>>& m) {
    moves = m;
}

QRectF MoveIndicator::boundingRect() const
{
    return QRectF(0, 0, 10, 10);
}

void MoveIndicator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(visible) {
        if (Chip::selectedChip->getColor() == "black") {
            painter->setBrush(Qt::blue);
        } else {
            painter->setBrush(Qt::red);
        }

        for (const auto& move : moves) {
            painter->drawEllipse(move.first, move.second, 10, 10);
        }
    }
}

