#ifndef RULESSCREEN_H
#define RULESSCREEN_H

#include <QGraphicsWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGraphicsProxyWidget>

class RulesScreen : public QGraphicsWidget
{
    Q_OBJECT

public:
    RulesScreen(QGraphicsItem *parent = 0);
};

#endif // RULESSCREEN_H
