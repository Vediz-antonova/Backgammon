#include "cell.h"
#include "sizes.h"

Cell::Cell(int id, int x, int y) : id(id), x(x), y(y), chips(0) {}

Cell::~Cell(){}

int Cell::getId() const { return id; }

int Cell::getX() const { return x; }

int Cell::getY() const { return y; }

bool Cell::getSelected() const { return selected; }

void Cell::setSelected(bool value) {
    selected = value;
    update();
}

void Cell::setAvailableToMove(bool value) {
    if (availableToMove != value) {
        availableToMove = value;
        update();
    }
}

void Cell::addChip(Chip* ch) {
//    int chipY = y + (isTopRow() ? getChipsCount() * 25 : -getChipsCount() * 25);
//    ch->setPos(x, chipY);
    chips.push_back(ch);
    update();
}

Chip* Cell::removeChip() {
    if (getChipsCount() > 0) {
        Chip *chip = chips.back();
        chips.pop_back();
        update();
        return chip;
    }

    return nullptr;
}

int Cell::getChipsCount() const {
    return chips.size();
}

ChipColor Cell::getChipsColor() const {
    if (getChipsCount() == 0) {
        return none;
    }

    return chips[0]->getColor();
}

void Cell::setCallbackFunc(void (*func) (int id)) {
    callbackFunc = func;
}

/*
std::pair<int, int> Cell::getChipPosition(bool isBlack) const {
    return std::make_pair(x, y + (isBlack ? -getChipsCount() * 25 : getChipsCount() * 25));
}
*/

bool Cell::canMoveTo(Chip* ch) {
    if(getChipsCount() >= 1 && ch->getColor() != chips[getChipsCount() - 1]->getColor()){
        return false;
    }

    return true;
}

bool Cell::containsChip(Chip* chip) const {
    for (Chip* c : chips) {
        if (c == chip) {
            return true;
        }
    }
    return false;
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    for (std::vector<Chip*>::size_type i = 0; i < chips.size(); i++) {
        Chip* chip = chips[i];

        drawChip(painter, i, chip);
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

void Cell::drawChip(QPainter *painter, int pos, Chip* chip) {
    Qt::GlobalColor color = chip->getColor() == white ? Qt::white : Qt::black;
    Qt::GlobalColor borderColor = chip->getColor() == white ? Qt::black : Qt::white;

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
