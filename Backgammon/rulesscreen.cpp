#include "rulesscreen.h"

RulesScreen::RulesScreen(QGraphicsItem *parent) : QGraphicsWidget(parent)
{
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout();

    QLabel *rulesLabel = new QLabel("Тут будут правила игры в длинные нарды...");
    layout->addWidget(rulesLabel);

    QPushButton *returnButton = new QPushButton("Вернуться");
    connect(returnButton, &QPushButton::clicked, widget, &QWidget::close);
    layout->addWidget(returnButton);

    widget->setLayout(layout);

    QGraphicsProxyWidget *proxy = new QGraphicsProxyWidget(this);
    proxy->setWidget(widget);
}
