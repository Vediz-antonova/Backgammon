#ifndef CELL_H
#define CELL_H

#include <utility>
#include "chip.h"
#include "enums.h"

class Chip;

class Cell : public QObject, public QGraphicsItem {
    Q_OBJECT
public:
    //explicit Cell(){}
    Cell(int id, int x, int y);
    ~Cell();

    int getId() const;
    int getX() const;
    int getY() const;
    bool getSelected() const;
    void setSelected(bool value);
    void setAvailableToMove(bool value);

    void addChip(Chip* ch);
    Chip* removeChip();
    int getChipsCount() const;
    ChipColor getChipsColor() const;

    void setCallbackFunc(void (*func) (int id));

    bool canMoveTo(Chip* ch);
    bool containsChip(Chip* chip) const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int id;
    int x;
    int y;
    bool selected = false;
    bool availableToMove = false;
    std::vector<Chip*> chips;
    void (*callbackFunc)(int id) = 0;
    bool isTopRow();
    void drawChip(QPainter *painter, int pos, Chip* chip);
    void drawAvailableMark(QPainter *painter);
    //std::pair<int, int> getChipPosition(bool isBlack) const;
};

#endif // CELL_H
