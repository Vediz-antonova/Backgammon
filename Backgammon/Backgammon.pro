QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cell.cpp \
    currentplayer.cpp \
    dice.cpp \
    game.cpp \
    main.cpp \
    MainWidget.cpp \
    removechipbutton.cpp \
    rulesscreen.cpp \
    startwidget.cpp

HEADERS += \
    MainWidget.h \
    cell.h \
    currentplayer.h \
    dice.h \
    enums.h \
    game.h \
    removechipbutton.h \
    rulesscreen.h \
    sizes.h \
    startwidget.h

FORMS += \
    MainWidget.ui \
    startwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
