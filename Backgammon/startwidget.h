#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>

#include <rulesscreen.h>
#include <MainWidget.h>

namespace Ui {
class StartWidget;
}

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = nullptr);
    ~StartWidget();

private slots:
    void on_rulesButton_clicked();

    void on_startButton_clicked();

    void on_start2playerButton_clicked();

private:
    Ui::StartWidget *ui;
    RulesScreen *rulesScreen;
    MainWidget *mainWidget;
};

#endif // STARTWIDGET_H
