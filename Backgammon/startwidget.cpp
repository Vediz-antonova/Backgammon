#include "startwidget.h"
#include "ui_startwidget.h"

StartWidget::StartWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    mainWidget = new MainWidget();
    mainWidget->hide();
}

StartWidget::~StartWidget()
{
    delete ui;
}

void StartWidget::on_rulesButton_clicked()
{
    rulesScreen = new RulesScreen();
    rulesScreen->show();
}

void StartWidget::on_startButton_clicked()
{
    mainWidget->setTwoPlayers(false);
    mainWidget->showMaximized();
    this->hide();
}

void StartWidget::on_start2playerButton_clicked()
{
    mainWidget->setTwoPlayers(true);
    mainWidget->showMaximized();
    this->hide();
}

