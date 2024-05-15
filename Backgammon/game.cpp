#include "game.h"
#include "sizes.h"

Game::Game() {
    selectedCell = nullptr;
//    dice1 = new Dice();
//    dice2 = new Dice();
    dice1.setCallbackFunc(diceClicked);
    dice2.setCallbackFunc(diceClicked);

    removeBlackButton.setColor(black);
    removeWhiteButton.setColor(white);
//    dice1->setOtherCube(dice2);
//    dice2->setOtherCube(dice1);

//    moveIndicator = new MoveIndicator();
}

Game::~Game() {
    //delete dice1;
    //delete dice2;

//    for (Cell *cell : board) {
//        delete cell;
//    }
}

void Game::startNewGame() {
//    scene->addItem(moveIndicator);
    scene->addItem(&dice1);
    scene->addItem(&dice2);
    dice1.setPos((scene->width() - DICE_SIZE)/2, scene->height()/2 - 110);
    dice2.setPos((scene->width() - DICE_SIZE)/2, scene->height()/2 + 60);
    dice1.show();
    dice2.show();

    scene->addItem(&removeBlackButton);
    scene->addItem(&removeWhiteButton);
    removeBlackButton.setPos(10, 10);
    removeWhiteButton.setPos(scene->width() - 120, scene->height() - 120);

    int x;
    int y;

    for (int i = 0; i < 24; i++) {
        if(i < 12){
            y = TOP_CELL_OFFSET;
        } else {
            y = TOP_CELL_OFFSET + CELL_HEIGHT;
        }

        if ((i > 5 && i < 12) || (i > 11 && i < 18)) {
            x = LEFT_BOARD_OFFSET;
        } else {
            x = RIGHT_BOARD_OFFSET;
        }

        int column = i < 12 ? 11 - i : i - 12;
        //Cell* c = new Cell(i/*, x + column * (CELL_WIDTH + CELL_X_SPACE), y*/);
        Cell &c = board[i];
        c.setId(i);
        c.setCallbackFunc(cellClicked);

        scene->addItem(&c);
        c.setPos(x + column * (CELL_WIDTH + CELL_X_SPACE), y);
        c.show();
        //board.push_back(c);
    }

    int num_chips = 15;

    for (int i = 0; i < num_chips; i++) {
        board[12].addChip(black);
//        Chip* chip = new Chip(black);
        //std::pair<int, int> pos = board[12]->getChipPosition(true);
        //chip->setPos(pos.first, pos.second);
//        scene->addItem(chip);
//        chip->show();
//        chip->setMoveIndicator(moveIndicator);
//        black_chips.push_back(chip);

//        chip->setCube1(&dice1);
//        chip->setCube2(&dice2);
//        board[12]->addChip(chip);
//        chip->setCurrentCell((board[12]));
    }

    for (int i = 0; i < num_chips; i++) {
        board[0].addChip(white);
//        Chip* chip = new Chip(white);
        //std::pair<int, int> pos = board[11]->getChipPosition(false);
        //chip->setPos(pos.first, pos.second);
//        scene->addItem(chip);
//        chip->setMoveIndicator(moveIndicator);
//        chip->show();
//        white_chips.push_back(chip);

//        chip->setCube1(dice1);
//        chip->setCube2(dice2);
//        board[0]->addChip(chip);
//        chip->setCurrentCell((board[0]));
    }
}

void Game::endGame() {}

/* void Game::makeMove(Chip* chip, Cell* targetCell) {
   if (!targetCell->canMoveTo(chip)) {
        qDebug() << "Invalid move!";
        return;
    }

    Cell* currentCell = chip->getCurrentCell();
    currentCell->removeChip();

    targetCell->addChip(chip);
    chip->setCurrentCell(targetCell);

}
*/

void Game::cellClicked(int id) {
    Game *game = &Game::getInstance();
    Cell &cell = game->board[id];


    if (!game->selectedCell) {
        if (cell.getChipsColor() != game->playerColor) {
            return;
        }
        game->selectCell(cell);
        return;
    }

    int selectedCellId = game->selectedCell->getId();

    if (selectedCellId != id) {
        game->tryMakeMove(*game->selectedCell, cell);
    } else {
        game->unselectCell();
    }
}

void Game::diceClicked() {
    Game *game = &Game::getInstance();

    game->rollDices();
}

void Game::rollDices() {
    rollDice(dice1);
    rollDice(dice2);

    std::vector<int> dicesMovements = getDicesMovements();
    availableMovements.clear();

    for (int movement : dicesMovements) {
        if (validateMovement(movement)) {
            availableMovements.push_back(movement);
        }
    }

    //dice1.setEnabled(false);
    //dice2.setEnabled(false);
}

int Game::rollDice(Dice &dice) {
    int diceValue = QRandomGenerator::global()->bounded(1, 7);
    dice.setValue(diceValue);
    return diceValue;
}

void Game::tryMakeMove(Cell &from, Cell &to)
{
    if (to.getId() == from.getId()) {
        return;
    }

    if (!to.getAvailableToMove()) {
        return;
    }

    ChipColor chipColor= from.getChipsColor();
    bool removed = from.removeChip();

    if (!removed) {
        return;
    }

    to.addChip(chipColor);

    unselectCell();

    int distance = getCellsDistance(from, to);
    std::vector<int>::iterator movePos = std::find(availableMovements.begin(), availableMovements.end(), distance);
    if (movePos != availableMovements.end()) {
        availableMovements.erase(movePos);
    }
}

void Game::selectCell(Cell &cell) {
    if (availableMovements.size() == 0) {
        return;
    }

    cell.setSelected(true);
    selectedCell = &cell;
    int cellId = cell.getId();

    for (int move : availableMovements) {
        MoveType moveType = getMoveType(cell, move);

        if (moveType == regularMove) {
            int moveCellId = getCellIdAfterMove(cell, move);
            Cell &moveCell = board[moveCellId];
            moveCell.setAvailableToMove(true);
        } else if (moveType == removeFromBoard && chipsRemoveAvailable()) {
            if (cell.getChipsColor() == white) {
                removeWhiteButton.show();
            } else {
                removeBlackButton.show();
            }
        }
    }
    // ToDo: add possible movements marks
}

void Game::unselectCell() {
    if (selectedCell) {
        selectedCell->setSelected(false);
        selectedCell = nullptr;
    }

    clearMovementsMarks();
}

std::vector<int> Game::getDicesMovements() {
    std::vector<int> result;
    bool sameDices = dice1.getValue() == dice2.getValue();

    result.push_back(dice1.getValue());
    if (sameDices) {
        result.push_back(dice1.getValue());
    }

    result.push_back(dice2.getValue());
    if (sameDices) {
        result.push_back(dice2.getValue());
    }

    return result;
}

bool Game::validateMovement(int movement) {
    bool removeAvailable = chipsRemoveAvailable();

    for (Cell &cell : board) {
        MoveType moveType = getMoveType(cell, movement);
        if (moveType == regularMove || (moveType == removeFromBoard && removeAvailable)) {
            return true;
        }
    }

    return false;
}

void Game::clearMovementsMarks() {
    for (Cell &cell : board) {
        cell.setAvailableToMove(false);
    }
}

int Game::getCellsDistance(Cell &from, Cell &to) {
    return (to.getId() - from.getId() + 24) % 24;
}

MoveType Game::getMoveType(Cell &from, int move) {
    ChipColor fromCellColor = from.getChipsColor();

    if (fromCellColor == none) {
        return moveForbidden;
    }
    int toCellId = getCellIdAfterMove(from, move);

    if (fromCellColor == white && from.getId() > toCellId) {
        return removeFromBoard;
    }

    if (fromCellColor == black && from.getId() < 12 && toCellId > 11) {
        return removeFromBoard;
    }

    ChipColor toCellColor = board[toCellId].getChipsColor();
    if (toCellColor != none && toCellColor != fromCellColor) {
        return moveForbidden;
    }

    return regularMove;
}

int Game::getCellIdAfterMove(Cell &from, int move) {
    return (from.getId() + move) % 24;
}

bool Game::chipsRemoveAvailable() {
    for (Cell &cell : board) {
        if (playerColor == white && cell.getChipsColor() == white
            && cell.getChipsCount() > 0 && cell.getId() < 18) {
            return false;
        }

        if (playerColor == black && cell.getChipsColor() == black
            && cell.getChipsCount() > 0
            && (cell.getId() < 6 || cell.getId() > 11)) {
            return false;
        }
    }

    return true;
}
