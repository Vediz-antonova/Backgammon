#ifndef GAME_H
#define GAME_H

#include <algorithm>
#include <QMessageBox>

#include "cell.h"
#include "dice.h"
#include "removechipbutton.h"
#include "currentplayer.h"

#include "sizes.h"
#include "enums.h"

class Game {
public:
    static Game& getInstance() {
        static Game instance;
        return instance;
    }

    Game();
    ~Game();

    void setScene(QGraphicsScene* new_sc) { scene = new_sc; }
    void startNewGame();
    void endGame();

private:
    QGraphicsScene* scene;

    Cell board[24];

    Dice dice1;
    Dice dice2;

    RemoveChipButton removeBlackButton;
    RemoveChipButton removeWhiteButton;

    CurrentPlayer currentPlayer;

    std::vector<int> availableMovements;

    int removed_black_chips;
    int removed_white_chips;

    Cell *selectedCell;

    ChipColor playerColor = white;

    bool fromHead = false;

    static void cellClicked(int id);
    static void diceClicked();
    static void removeButtonClicked(int move);

    void rollDices();
    int rollDice(Dice &dice);
    void tryMakeMove(Cell &from, Cell &to);
    void selectCell(Cell &cell);
    void unselectCell();
    std::vector<int> getDicesMovements();
    bool validateMovement(int movement);
    void clearMovementsMarks();
    int getCellsDistance(Cell &from, Cell &to);
    MoveType getMoveType(Cell &from, int move);
    int getCellIdAfterMove(Cell &from, int move);
    bool chipsRemoveAvailable();
    void removeChipFromBoard(Cell &cell, int move);
    void endOfMovements();
    bool isCellHead(Cell &cell);
};


#endif // GAME_H
