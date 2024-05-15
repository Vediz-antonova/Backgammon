#ifndef GAME_H
#define GAME_H

#include "cell.h"
#include "chip.h"
#include "dice.h"

class Game {
public:
    static Game& getInstance() {
        static Game instance;
        return instance;
    }

    Game();
    ~Game();
    std::vector<Cell*> board;

    void setScene(QGraphicsScene* new_sc) { scene = new_sc; }
    void startNewGame();
    void endGame();
    void makeMove(Chip* chip, Cell* cell);
    void rollDices();
    int rollDice(Dice *dice);
    void tryMakeMove(Cell *from, Cell *to);
    void selectCell(Cell *cell);
    void unselectCell();

private:
    QGraphicsScene* scene;

    Dice *dice1;
    Dice *dice2;

    std::vector<Chip*> chip_black;
    std::vector<Chip*> chip_white;

    MoveIndicator *moveIndicator;
    // std::vector<Player> players;

    Cell *selectedCell;

    ChipColor playerColor = white;

    static void cellClicked(int id);
    static void diceClicked();

};


#endif // GAME_H
