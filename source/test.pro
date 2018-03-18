#-------------------------------------------------
#
# Project created by QtCreator 2017-05-24T16:45:59
#
#-------------------------------------------------

QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    Bullet.cpp \
    Game.cpp \
    Player.cpp \
    playercontroler.cpp \
    wall.cpp \
    Button.cpp \
    TankButton.cpp \
    state_box.cpp \
    river.cpp \
    firebullet.cpp \
    turret.cpp

HEADERS  += \
    Game.h \
    Bullet.h \
    Player.h \
    Setting.h \
    playercontroler.h \
    wall.h \
    Button.h \
    TankButton.h \
    state_box.h \
    river.h \
    firebullet.h \
    turret.h

FORMS    +=

RESOURCES += \
    res.qrc

DISTFILES += \
    tank_injured6.png \
    tank_injured5.png \
    tank_injured4.png \
    tank_injured3.png \
    tank_injured2.png \
    tank_injured1.png
