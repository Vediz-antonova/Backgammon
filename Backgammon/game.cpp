#include "game.h"

Game::Game() {
    selectedCell = nullptr;
    dice1.setCallbackFunc(diceClicked);
    dice2.setCallbackFunc(diceClicked);

    removeBlackButton.setColor(black);
    removeWhiteButton.setColor(white);

    currentPlayer.setColor(playerColor);
}

Game::~Game() {}

void Game::startNewGame() {
    scene->addItem(&dice1);
    scene->addItem(&dice2);
    dice1.setPos((scene->width() - DICE_SIZE)/2, scene->height()/2 - 110);
    dice2.setPos((scene->width() - DICE_SIZE)/2, scene->height()/2 + 60);
    dice1.show();
    dice2.show();

    scene->addItem(&removeBlackButton);
    scene->addItem(&removeWhiteButton);
    removeBlackButton.setPos(40, (scene->height()-REMOVE_BUTTON_SIZE)/2);
    removeWhiteButton.setPos(scene->width() - REMOVE_BUTTON_SIZE - 110, (scene->height()-REMOVE_BUTTON_SIZE)/2);
    removeBlackButton.setCallbackFunc(removeButtonClicked);
    removeWhiteButton.setCallbackFunc(removeButtonClicked);
    removeBlackButton.hide();
    removeWhiteButton.hide();

    scene->addItem(&currentPlayer);
    currentPlayer.setPos(40, 50);
    currentPlayer.show();

    int x;
    int y;

    for (int i = 0; i < 24; i++) {
        if(i < 12){
            y = TOP_CELL_OFFSET;
        } else {
            y = TOP_CELL_OFFSET + CELL_HEIGHT + 10;
        }

        if ((i > 5 && i < 12) || (i > 11 && i < 18)) {
            x = LEFT_BOARD_OFFSET;
        } else {
            x = RIGHT_BOARD_OFFSET;
        }

        int column = i < 12 ? 11 - i : i - 12;
        Cell &c = board[i];
        c.setId(i);
        c.setCallbackFunc(cellClicked);

        scene->addItem(&c);
        c.setPos(x + column * (CELL_WIDTH + CELL_X_SPACE), y);
        c.show();
    }

    int num_chips = 15;

    for (int i = 0; i < num_chips; i++) {
        board[12].addChip(black);
    }

    for (int i = 0; i < num_chips; i++) {
        board[0].addChip(white);
    }
}

bool Game::endGame() {
    if (removed_black_chips == 15 || removed_white_chips == 15){
        QMessageBox message;
        if(removed_black_chips == 15){
            message.setText("Winer: black");
        } else {
            message.setText("Winer: white");
        }

        message.exec();

        return true;
    }

    return false;
}

void Game::setTwoPlayers(bool value){
    twoPlayer = value;
}

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

void Game::removeButtonClicked(int move){
    Game *game = &Game::getInstance();
    Cell *cell = game->selectedCell;

    if(cell == nullptr){
        return;
    }

    game->removeChipFromBoard(*cell, move);
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

    dice1.setEnabled(false);
    dice2.setEnabled(false);

    endOfMovements();
}

int Game::rollDice(Dice &dice) {
    int diceValue = QRandomGenerator::global()->bounded(1, 7);
    dice.setValue(diceValue);
    return diceValue;
}

bool Game::tryMakeMove(Cell &from, Cell &to)
{
    if (to.getId() == from.getId()) {
        return false;
    }

    if (!to.getAvailableToMove()) {
        return false;
    }

    ChipColor chipColor= from.getChipsColor();
    bool removed = from.removeChip();

    if (!removed) {
        return false;;
    }

    if(isCellHead(from)){
        fromHead = true;
    }

    to.addChip(chipColor);

    unselectCell();

    int distance = getCellsDistance(from, to);
    std::vector<int>::iterator movePos = std::find(availableMovements.begin(), availableMovements.end(), distance);
    if (movePos != availableMovements.end()) {
        availableMovements.erase(movePos);
    }

    endOfMovements();

    return true;
}

void Game::selectCell(Cell &cell) {
    if (availableMovements.size() == 0) {
        return;
    }

    if(fromHead && isCellHead(cell)){
        return;
    }

    cell.setSelected(true);
    selectedCell = &cell;

    std::vector<int> remove_moves;

    for (int move : availableMovements) {
        MoveType moveType = getMoveType(cell, move);

        if (moveType == regularMove) {
            int moveCellId = getCellIdAfterMove(cell, move);
            Cell &moveCell = board[moveCellId];
            moveCell.setAvailableToMove(true);
            removeWhiteButton.setMove(0);
            removeBlackButton.setMove(0);
        } else if (moveType == removeFromBoard && chipsRemoveAvailable()) {
            if (cell.getChipsColor() == white) {
                removeWhiteButton.show();
            } else {
                removeBlackButton.show();
            }
            remove_moves.push_back(move);
        }
    }

    if(!remove_moves.empty()){
        int move = remove_moves[std::distance(remove_moves.begin(), std::min_element(remove_moves.begin(), remove_moves.end()))];
        if (cell.getChipsColor() == white) {
            removeWhiteButton.setMove(move);
        } else {
            removeBlackButton.setMove(move);
        }
    }
}

void Game::unselectCell() {
    if (selectedCell) {
        selectedCell->setSelected(false);
        selectedCell = nullptr;
    }

    clearMovementsMarks();

    removeBlackButton.hide();
    removeWhiteButton.hide();
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
        if(cell.getChipsColor() == playerColor){
            MoveType moveType = getMoveType(cell, movement);
            if (moveType == regularMove || (moveType == removeFromBoard && removeAvailable)) {
                return true;
            }
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

    if(isCellHead(from) && fromHead){
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

void Game::removeChipFromBoard(Cell &cell, int move){\
    ChipColor color = cell.getChipsColor();

    if(color == white){
        removed_white_chips++;
    } else {
        removed_black_chips++;
    }

    cell.removeChip();
    unselectCell();

    std::vector<int>::iterator movePos = std::find(availableMovements.begin(), availableMovements.end(), move);
    if (movePos != availableMovements.end()) {
        availableMovements.erase(movePos);
    }

    endGame();
    endOfMovements();
}

void Game::endOfMovements(){
    bool no_movements = true;
    for(int move : availableMovements){
        if(validateMovement(move)){
            no_movements = false;
        }
    }

    if(no_movements){
        dice1.setEnabled(true);
        dice2.setEnabled(true);

        playerColor = playerColor == white ? black : white;
        currentPlayer.setColor(playerColor);
        fromHead = false;

        if(playerColor == aiColor && !twoPlayer){
            rollDices();
            while(!availableMovements.empty()){
                aiMove();
            }
        }
    }
}


bool Game::isCellHead(Cell &cell){
    ChipColor color = cell.getChipsColor();
    if(cell.getId() == 0 && color == white){
        return true;
    } else if(cell.getId() == 12 && color == black){
        return true;
    }

    return false;
}

void Game::aiMove() {
    if (availableMovements.empty()) {
        endOfMovements();
        return;
    }

    std::vector<Cell*> aiCells;
    for (Cell &cell : board) {
        if (cell.getChipsColor() == aiColor && cell.getChipsCount() > 0) {
            aiCells.push_back(&cell);
        }
    }
    if (aiCells.empty()) {
        return;
    }

    while(!availableMovements.empty()){
        Cell &fromCell = *aiCells[QRandomGenerator::global()->bounded(static_cast<int>(aiCells.size()))];

        for(int move : availableMovements){
            MoveType moveType = getMoveType(fromCell, move);
            if (moveType == regularMove) {
                int toCellId =  getCellIdAfterMove(fromCell, move);
                selectCell(fromCell);
                if(tryMakeMove(fromCell, board[toCellId])){
                    return;
                }
                unselectCell();
            } else if(chipsRemoveAvailable() && moveType == removeFromBoard){
                selectCell(fromCell);
                removeChipFromBoard(fromCell, move);
                return;
            }
        }
    }
}
