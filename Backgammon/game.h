#ifndef GAME_H
#define GAME_H

#include <algorithm>

#include "cell.h"
#include "chip.h"
#include "dice.h"
#include "removechipbutton.h"

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

//    std::vector<Chip*> black_chips;
//    std::vector<Chip*> white_chips;
    std::vector<int> availableMovements;

    int removed_black_chips;
    int removed_white_ships;

    //MoveIndicator *moveIndicator;
    // std::vector<Player> players;

    Cell *selectedCell;

    ChipColor playerColor = white;

    static void cellClicked(int id);
    static void diceClicked();

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
};


#endif // GAME_H
