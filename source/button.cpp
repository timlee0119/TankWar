#include <QObject>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWidget>
#include <QDebug>
#include <QMediaPlayer>
#include "Button.h"

Button::Button(){
    press = new QMediaPlayer(this);
    press->setMedia(QUrl("qrc:/sounds/select.mp3"));
    press->setVolume(50);
}

Button::~Button()
{
    delete press;
    press = nullptr;
}

void Button::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        // play press sound
        press->play();

        emit clicked();
        //qDebug() << event;
    }
}

void Button::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Slash || event->key() == Qt::Key_Q){
        // play press sound
        press->play();

        emit clicked();
        //qDebug() << event;
    }
}

