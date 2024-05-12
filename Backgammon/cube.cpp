#include "cube.h"

Cube::Cube(QObject *parent) : QObject(parent), QGraphicsItem()
{
    setValue(1);
}

Cube::~Cube(){}

bool Cube::isWhiteTurn = true;

void Cube::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::white);
    painter->drawRect(0, 0, 50, 50);

    painter->setBrush(Qt::black);
    if (getValue() == 1 || getValue() == 3 || getValue() == 5) {
        painter->drawEllipse(QPointF(25, 25), 5, 5); // центральная точка
    }
    if (getValue() >= 2) {
        painter->drawEllipse(QPointF(10, 10), 5, 5); // верхний левый угол
        painter->drawEllipse(QPointF(40, 40), 5, 5); // нижний правый угол
    }
    if (getValue() >= 4) {
        painter->drawEllipse(QPointF(40, 10), 5, 5); // верхний правый угол
        painter->drawEllipse(QPointF(10, 40), 5, 5); // нижний левый угол
    }
    if (getValue() == 6) {
        painter->drawEllipse(QPointF(10, 25), 5, 5); // левая сторона
        painter->drawEllipse(QPointF(40, 25), 5, 5); // правая сторона
    }
}

QRectF Cube::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void Cube::Game()
{
    setValue(QRandomGenerator::global()->bounded(1, 7));
    update();
}

void Cube::setOtherCube(Cube *cube) {
    otherCube = cube;
}

void Cube::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        Game();
        if (otherCube) {
            otherCube->Game();
        }

        isWhiteTurn = !isWhiteTurn;

        if (Chip::selectedChip) {
            Chip::selectedChip->selected = false;
            Chip::selectedChip->update();
            Chip::selectedChip = nullptr;
        }
    }
}

void Cube::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event); // Для игнорировния события
}

QPainterPath Cube::shape() const // Для установки ограничивающего прямоугольника
{
    QPainterPath path;
    path.addRect(QRectF(0, 0, 50, 50));
    return path;
}
