#include "chip.h"

Chip::Chip(QObject *parent) : QObject(parent), QGraphicsItem()
{
    color = "black";
}

Chip::Chip(QString c, QObject *parent) : QObject(parent), QGraphicsItem()
{
    color = c;
}

Chip::~Chip(){}

void Chip::drawChip(QPainter *painter)
{
    if(color == "black"){
        painter->setBrush(Qt::black);
        painter->drawEllipse(0, 0, 70, 70);
        painter->setPen(QPen(Qt::white, 1));
        painter->drawEllipse(0, 0, 70, 70);
    }
    else {
        painter->setBrush(Qt::white);
        painter->drawEllipse(0, 0, 70, 70);
        painter->setPen(QPen(Qt::black, 1));
        painter->drawEllipse(0, 0, 70, 70);
    }

    if(selected) {
        painter->setPen(QPen(Qt::red, 3));
        painter->drawEllipse(0, 0, 70, 70);
    }
}

QRectF Chip::boundingRect() const
{
    return QRectF(0, 0, 70, 70);
}

void Chip::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    drawChip(painter);
}

Chip* Chip::selectedChip = nullptr;

void Chip::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if(event->button() == Qt::LeftButton) {
        if(Cube::isWhiteTurn && color == "white" || !Cube::isWhiteTurn && color == "black") {
            if(selectedChip && selectedChip != this) {
                selectedChip->selected = false;
                selectedChip->update();
            }
            selected = !selected;
            selectedChip = this;
            update();
        }
    }
}

std::vector<std::pair<int, int>> Chip::calculatePossibleMoves() {
    std::vector<std::pair<int, int>> possibleMoves;

    int val1 = cube1->getValue();
    int val2 = cube2->getValue();

    int pos1 = this->x() + val1 * 70;
    int pos2 = this->x() + val2 * 70;

    return possibleMoves;
}
