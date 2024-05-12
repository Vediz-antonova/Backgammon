#ifndef CUBE_H
#define CUBE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QPropertyAnimation>
#include <QRandomGenerator>
#include <QGraphicsSceneMouseEvent>

#include <chip.h>

class Cube : public QObject, public QGraphicsItem{
    Q_OBJECT

public:
    explicit Cube(QObject *parent = 0);
    ~Cube();

    static bool isWhiteTurn;

    void setValue(int new_value) { valueCube = new_value; }
    int getValue() { return valueCube; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    void setOtherCube(Cube *cube);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QPainterPath shape() const;

protected:
    int valueCube;
    Cube *otherCube;

signals:

public slots:
    void Game();
};

#endif // CUBE_H
