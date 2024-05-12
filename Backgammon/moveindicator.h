#ifndef MOVEINDICATOR_H
#define MOVEINDICATOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>

#include "chip.h"

class MoveIndicator : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MoveIndicator(QObject *parent = nullptr);
    ~MoveIndicator();

    void setVisible(int new_visible) { visible = new_visible; }
    void setMoves(const std::vector<std::pair<int, int>>& m);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    bool visible;
    std::vector<std::pair<int, int>> moves;
};

#endif // MOVEINDICATOR_H
