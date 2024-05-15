#include "game.h"
#include "sizes.h"

Game::Game() {
    selectedCell = nullptr;
    dice1 = new Dice();
    dice2 = new Dice();
    dice1->setCallbackFunc(diceClicked);
    dice2->setCallbackFunc(diceClicked);
//    dice1->setOtherCube(dice2);
//    dice2->setOtherCube(dice1);

//    moveIndicator = new MoveIndicator();
}

Game::~Game() {}

void Game::startNewGame() {
//    scene->addItem(moveIndicator);
    scene->addItem(dice1);
    scene->addItem(dice2);
    dice1->show();
    dice2->show();
    dice1->setPos((scene->width() - DICE_SIZE)/2, scene->height()/2 - 110);
    dice2->setPos((scene->width() - DICE_SIZE)/2, scene->height()/2 + 60);

    int x;
    int y;

    for (int i = 0; i < 24; i++) {
        if(i < 12){
            y = TOP_CELL_OFFSET;
        } else {
            y = TOP_CELL_OFFSET + CELL_HEIGHT;
        }

        if ((i < 6) || (i > 11 && i < 18)) {
            x = LEFT_BOARD_OFFSET;
        } else {
            x = RIGHT_BOARD_OFFSET;
        }

        Cell* c = new Cell(i, x + i % 12 * (CELL_WIDTH + CELL_X_SPACE), y);
        c->setCallbackFunc(cellClicked);

        scene->addItem(c);
        c->setPos(x + i % 12 * (CELL_WIDTH + CELL_X_SPACE), y);
        c->show();
        board.push_back(c);
    }

    int num_chips = 15;

    for (int i = 0; i < num_chips; i++) {
        Chip* chip = new Chip(black);
        //std::pair<int, int> pos = board[12]->getChipPosition(true);
        //chip->setPos(pos.first, pos.second);
//        scene->addItem(chip);
//        chip->show();
        chip->setMoveIndicator(moveIndicator);
        chip_black.push_back(chip);

        chip->setCube1(dice1);
        chip->setCube2(dice2);
        board[12]->addChip(chip);
        chip->setCurrentCell((board[12]));
    }

    for (int i = 0; i < num_chips; i++) {
        Chip* chip = new Chip(white);
        //std::pair<int, int> pos = board[11]->getChipPosition(false);
        //chip->setPos(pos.first, pos.second);
//        scene->addItem(chip);
        chip->setMoveIndicator(moveIndicator);
//        chip->show();
        chip_white.push_back(chip);

        chip->setCube1(dice1);
        chip->setCube2(dice2);
        board[11]->addChip(chip);
        chip->setCurrentCell((board[11]));
    }
}

void Game::endGame() {}

void Game::makeMove(Chip* chip, Cell* targetCell) {
    if (!targetCell->canMoveTo(chip)) {
        qDebug() << "Invalid move!";
        return;
    }

    Cell* currentCell = chip->getCurrentCell();
    currentCell->removeChip();

    targetCell->addChip(chip);
    chip->setCurrentCell(targetCell);
}

void Game::cellClicked(int id) {
    Game *game = &Game::getInstance();
    Cell *cell = game->board[id];


    if (!game->selectedCell) {
        if (cell->getChipsColor() != game->playerColor) {
            return;
        }
        game->selectCell(cell);
        return;
    }

    int selectedCellId = game->selectedCell->getId();

    if (selectedCellId != id) {
        game->tryMakeMove(game->selectedCell, cell);
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
}

int Game::rollDice(Dice *dice) {
    int diceValue = QRandomGenerator::global()->bounded(1, 7);
    dice->setValue(diceValue);
    return diceValue;
}

void Game::tryMakeMove(Cell *from, Cell *to)
{
    if (to == from) {
        return;
    }

    if (to->getChipsColor() != none && to->getChipsColor() != from->getChipsColor()) {
        return;
    }

    Chip *chip = from->removeChip();
    to->addChip(chip);
    unselectCell();
}

void Game::selectCell(Cell *cell) {
    cell->setSelected(true);
    selectedCell = cell;
    // ToDo: add possible movements marks
}

void Game::unselectCell() {
    if (selectedCell) {
        selectedCell->setSelected(false);
        selectedCell = nullptr;
    }
    // ToDo: Clear movements marks
}
