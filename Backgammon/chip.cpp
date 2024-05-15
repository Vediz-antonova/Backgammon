#include "chip.h"
#include "game.h"

Chip::Chip(ChipColor c)
{
    color = c;
}

Chip::~Chip(){}

/*
void Chip::drawChip(QPainter *painter)
{
    if(color == black){
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
        if(Cube::isWhiteTurn && color == white || !Cube::isWhiteTurn && color == black) {
            if(selectedChip && selectedChip != this) {
                moveIndicator->setVisible(false);
                selectedChip->selected = false;
                selectedChip->update();
            }
            selected = !selected;
            selectedChip = this;
            update();

            std::vector<Cell*> moves = calculateMoves();

            if (!moves.empty()) {
                moveIndicator->setMoves(moves);
                moveIndicator->setVisible(true);
            }
        }
    }
}
*/

std::vector<Cell*> Chip::calculateMoves() {
    std::vector<Cell*> moves;

    int dice1 = cube1->getValue();
    int dice2 = cube2->getValue();

    Cell* move1 = nullptr;//getCellInDirection(selectedChip, dice1);
    if (move1 != nullptr && move1->canMoveTo(this)) {
        moves.push_back(move1);
        qDebug() << "Calculated move1";
    }

    Cell* move2 = nullptr;//getCellInDirection(selectedChip, dice2);
    if (move2 != nullptr && move2->canMoveTo(this)) {
        moves.push_back(move2);
        qDebug() << "Calculated move2";
    }

    if (moves.empty()) {
        qDebug() << "No moves calculated";
    }

    return moves;
}

Cell* Chip::getCellInDirection(Chip* chip, int steps) {
    Cell* currentCell = nullptr;
    for (Cell* cell : Game::getInstance().board) {
        if (cell->containsChip(chip)) {
            currentCell = cell;
            break;
        }
    }
    if (!currentCell) {
        return nullptr;
    }

    int currentIndex = std::distance(Game::getInstance().board.begin(), std::find(Game::getInstance().board.begin(), Game::getInstance().board.end(), currentCell));
    qDebug() << "current index: " << currentIndex;

    if(currentIndex - steps >= 0 && currentIndex < 12){
        steps *= -1;
    }
    int newIndex = currentIndex + steps;

    if (newIndex < 0 || newIndex >= Game::getInstance().board.size()) {
        return nullptr;
    }

    qDebug() << "new index: " << newIndex;
    return Game::getInstance().board[newIndex];
}

Cell* Chip::getCurrentCell() const {
    return currentCell;
}

void Chip::setCurrentCell(Cell* cell) {
    currentCell = cell;
}

void Chip::setMoveIndicator(MoveIndicator* moves) {
    moveIndicator = moves;
}
