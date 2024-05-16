#include "cell.h"

Cell::Cell() {
    chipsColor = none;
    chipsCount = 0;
    selected = false;
    availableToMove = false;
}

Cell::~Cell() {}

int Cell::getId() const { return id; }

void Cell::setId(int value) { id = value; }

bool Cell::getSelected() const { return selected; }

void Cell::setSelected(bool value) {
    selected = value;
    update();
}

bool Cell::getAvailableToMove() {
    return availableToMove;
}

void Cell::setAvailableToMove(bool value) {
    if (availableToMove != value) {
        availableToMove = value;
        update();
    }
}

bool Cell::addChip(ChipColor color) {
    if (chipsColor != none && chipsColor != color) {
        return false;
    }

    if (chipsCount >= 15) {
        return false;
    }

    chipsColor = color;
    chipsCount += 1;
    update();

    return true;
}

bool Cell::removeChip() {
    if (getChipsCount() > 0) {
        chipsCount -= 1;

        if (chipsCount == 0) {
            chipsColor = none;
        }

        update();
        return true;
    }

    return false;
}

int Cell::getChipsCount() const {
    return chipsCount;
}

ChipColor Cell::getChipsColor() const {
    return chipsColor;
}

void Cell::setCallbackFunc(void (*func) (int id)) {
    callbackFunc = func;
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

//    painter->setPen(Qt::white);
//    painter->drawRect(boundingRect());

    for (int i = 0; i < chipsCount; i++) {
        drawChip(painter, i);
    }

    drawAvailableMark(painter);
}

QRectF Cell::boundingRect() const
{
    return QRectF(0, 0, CELL_WIDTH, CELL_HEIGHT);
}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    if (callbackFunc) {
        callbackFunc(id);
    }
}

void Cell::drawChip(QPainter *painter, int pos) {
    Qt::GlobalColor color = chipsColor == white ? Qt::white : Qt::black;
    Qt::GlobalColor borderColor = chipsColor == white ? Qt::black : Qt::white;

    int chipYOffset = pos * CHIP_SHIFT;
    int chipY;

    if (isTopRow()) {
        chipY = chipYOffset;
    } else {
        chipY = CELL_HEIGHT - CHIP_SIZE - chipYOffset;
    }

    if(selected && pos == getChipsCount() - 1) {
        painter->setPen(QPen(Qt::red, 3));
    } else {
        painter->setPen(borderColor);
    }

    painter->setBrush(color);
    painter->drawEllipse(0, chipY, CHIP_SIZE, CHIP_SIZE);
}

void Cell::drawAvailableMark(QPainter *painter) {
    if (availableToMove) {
        int markX = (CELL_WIDTH - AVAILABLE_MARK_SIZE) / 2;
        int markY = getChipsCount() * CHIP_SHIFT + AVAILABLE_MARK_Y_OFFSET;

        if (getChipsCount() > 0) {
            markY += CHIP_SIZE - CHIP_SHIFT;
        }

        if (!isTopRow()) {
            markY = CELL_HEIGHT - AVAILABLE_MARK_SIZE - markY;
        }

        painter->setBrush(Qt::blue);
        painter->setPen(Qt::blue);
        painter->drawEllipse(markX, markY, AVAILABLE_MARK_SIZE, AVAILABLE_MARK_SIZE);
    }
}

bool Cell::isTopRow() {
    return id < 12;
}
