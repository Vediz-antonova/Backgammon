#include "dice.h"
#include "sizes.h"

Dice::Dice(QObject *parent) : QObject(parent), QGraphicsItem()
{
    setValue(1);
}

Dice::~Dice(){}

bool Dice::isWhiteTurn = true;

void Dice::setValue(int new_value) {
    diceValue = new_value;
    update();
}

int Dice::getValue() { return diceValue; }


void Dice::setCallbackFunc(void (*func) ()) {
    callbackFunc = func;
}

void Dice::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setBrush(Qt::white);
    painter->drawRect(0, 0, DICE_SIZE, DICE_SIZE);

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

/*
void Dice::setOtherCube(Dice *cube) {
    otherCube = cube;
}
*/

void Dice::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    if (callbackFunc) {
        callbackFunc();
    }
/*
    if (event->button() == Qt::LeftButton) {
        Game();
        if (otherCube) {
            otherCube->Game();
        }

        isWhiteTurn = !isWhiteTurn;

        if (Chip::selectedChip) {
            Chip::selectedChip->selected = false;
//            Chip::selectedChip->update();
            Chip::selectedChip = nullptr;
        }
    }
*/
}

/*
void Dice::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event); // Для игнорировния события
}

QPainterPath Dice::shape() const // Для установки ограничивающего прямоугольника
{
    QPainterPath path;
    path.addRect(QRectF(0, 0, DICE_SIZE, DICE_SIZE));
    return path;
}
*/
