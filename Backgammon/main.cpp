#include <QApplication>
#include "startwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartWidget startWidget;
    startWidget.show();
    return a.exec();
}
