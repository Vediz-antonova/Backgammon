#include "rulesscreen.h"

RulesScreen::RulesScreen(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout;
    QLabel *label = new QLabel("Rules", this);
    QFont font = label->font();
    font.setPointSize(30);
    label->setFont(font);

    QTextEdit *rulesText = new QTextEdit(this);
    rulesText->setReadOnly(true);
    font.setPointSize(10);
    rulesText->setFont(font);
    rulesText->setPlainText("Правила игры в длинные нарды: Игра начинается с того, что два игрока расставляют по 15 шашек на своей части доски вдоль правой стороны. Цель игры - пройти всеми шашками полный круг против часовой стрелки, зайти ими в “дом” и “выбросить” их раньше противника. Право первого хода определяется путем броска одного игрального кубика каждым игроком - ходит тот, у кого выпало большее количество очков. Игроки ходят по очереди, бросая два кубика и передвигая свои шашки на число очков, выпавшее на кубиках. Если на обоих кубиках выпадает одинаковое количество очков, игрок делает 4 хода. После того, как все шашки игрока заведены в “дом”, он снимает с доски от 1 до 4 шашек, в лунках, соответствующих числу выброшенных на кубиках очков. Игра заканчивается, когда один из игроков выводит все свои шашки с доски. В данном случае реализована игра с ботом");

    QPushButton *backButton = new QPushButton("Назад", this);
    backButton->setMinimumSize(100, 100);
    QFont buttonFont = backButton->font();
    buttonFont.setPointSize(30);
    buttonFont.setItalic(true);
    backButton->setFont(buttonFont);
    connect(backButton, &QPushButton::clicked, this, &QWidget::close);

    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::blue);
    this->setPalette(palette);
    this->setAutoFillBackground(true);
    layout->addWidget(label);
    layout->addWidget(rulesText);
    layout->addWidget(backButton);
    setLayout(layout);
}
