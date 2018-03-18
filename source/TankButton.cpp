#include <QObject>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWidget>
#include <QDebug>
#include <QMediaPlayer>
#include "TankButton.h"
#include "Game.h"

#define RESTART_CODE 1000
#define QUIT_CODE 2000

extern Game * game;

TankButton::TankButton(int ty){
    choose = new QMediaPlayer(this);
    choose->setMedia(QUrl("qrc:/sounds/choose.mp3"));
    choose->setVolume(3000);
    select = new QMediaPlayer(this);
    select->setMedia(QUrl("qrc:/sounds/select.mp3"));
    select->setVolume(50);
    this->type = ty;
}

TankButton::~TankButton(){
    delete choose;
    choose = nullptr;
    delete select;
    select = nullptr;
}

void TankButton::mouseDoubleClickEvent(QMouseEvent *event){
    // play select sound
    if (select->state() == QMediaPlayer::PlayingState)
            select->setPosition(0);
    else if (select->state() == QMediaPlayer::StoppedState)
            select->play();

//    if (game->current == 5 && event->button() == Qt::LeftButton){
//        if (this->type == 1){ // restart
//            emit clicked(RESTART_CODE);
//        }
//        else if (this->type == 2){ // quit
//            emit clicked(QUIT_CODE);
//        }
//    }
    if (event->button() == Qt::LeftButton && game->current != 5){
        emit clicked(this->type);
    }
}

void TankButton::keyPressEvent(QKeyEvent *event){

    // for p1 selection
    if (game->current == 1){
        // play sound effect
        if (event->key() == Qt::Key_Slash){
            if (select->state() == QMediaPlayer::PlayingState)
                select->setPosition(0);
            else if (select->state() == QMediaPlayer::StoppedState)
                select->play();
            emit clicked(this->type);
        }
        else if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right ||
                 event->key() == Qt::Key_Up || event->key() == Qt::Key_Down){
            if (choose->state() == QMediaPlayer::PlayingState)
                choose->setPosition(0);
            else if (choose->state() == QMediaPlayer::StoppedState)
                choose->play();
        }

        if (event->key() == Qt::Key_Left){
            int ty = this->type;
            if (ty == 1) {
                ty = 6;
            }
            else {
                ty -= 1;
            }
            game->tankButtonP1[ty - 1]->setFocus();
        }
        if (event->key() == Qt::Key_Right){
            int ty = this->type;
            if (ty == 6) {
                ty = 1;
            }
            else {
                ty += 1;
            }
            game->tankButtonP1[ty - 1]->setFocus();
        }
        if (event->key() == Qt::Key_Up){
            int ty = this->type;
            if (ty == 1 || ty == 2) {
                ty += 4 ;
            }
            else {
                ty -= 2;
            }
            game->tankButtonP1[ty - 1]->setFocus();
        }
        if (event->key() == Qt::Key_Down){
            int ty = this->type;
            if (ty == 5 || ty == 6) {
                ty -= 4;
            }
            else {
                ty += 2;
            }
            game->tankButtonP1[ty - 1]->setFocus();
        }
    }

    // for p2 selection
    else if (game->current == 2){
        // play sound effect
        if (event->key() == Qt::Key_Q){
            if (select->state() == QMediaPlayer::PlayingState)
                select->setPosition(0);
            else if (select->state() == QMediaPlayer::StoppedState)
                select->play();
            emit clicked(this->type);
        }
        else if (event->key() == Qt::Key_A || event->key() == Qt::Key_D ||
                 event->key() == Qt::Key_W || event->key() == Qt::Key_S){
            if (choose->state() == QMediaPlayer::PlayingState)
                choose->setPosition(0);
            else if (choose->state() == QMediaPlayer::StoppedState)
                choose->play();
        }

        if (event->key() == Qt::Key_A){
            int ty = this->type;
            if (ty == 1) {
                ty = 6;
            }
            else {
                ty -= 1;
            }
            game->tankButtonP2[ty - 1]->setFocus();
        }
        if (event->key() == Qt::Key_D){
            int ty = this->type;
            if (ty == 6) {
                ty = 1;
            }
            else {
                ty += 1;
            }
            game->tankButtonP2[ty - 1]->setFocus();
        }
        if (event->key() == Qt::Key_W){
            int ty = this->type;
            if (ty == 1 || ty == 2) {
                ty += 4 ;
            }
            else {
                ty -= 2;
            }
            game->tankButtonP2[ty - 1]->setFocus();
        }
        if (event->key() == Qt::Key_S){
            int ty = this->type;
            if (ty == 5 || ty == 6) {
                ty -= 4;
            }
            else {
                ty += 2;
            }
            game->tankButtonP2[ty - 1]->setFocus();
        }
    }
    // for map button
    else if (game->current == 3){
        // play sound effect
        if (event->key() == Qt::Key_Slash || event->key() == Qt::Key_Q){
            if (select->state() == QMediaPlayer::PlayingState)
                select->setPosition(0);
            else if (select->state() == QMediaPlayer::StoppedState)
                select->play();
            emit clicked(this->type);
        }
        else {
            if (choose->state() == QMediaPlayer::PlayingState)
                choose->setPosition(0);
            else if (choose->state() == QMediaPlayer::StoppedState)
                choose->play();
        }

        if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A){
            int ty = this->type;
            if (ty == 1) {
                ty = 6;
            }
            else {
                ty -= 1;
            }
            game->mapButton[ty - 1]->setFocus();
        }
        if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D){
            int ty = this->type;
            if (ty == 6) {
                ty = 1;
            }
            else {
                ty += 1;
            }
            game->mapButton[ty - 1]->setFocus();
        }
        if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W){
            int ty = this->type;
            if (ty == 1 || ty == 2 || ty == 3) {
                ty += 3 ;
            }
            else {
                ty -= 3;
            }
            game->mapButton[ty - 1]->setFocus();
        }
        if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S){
            int ty = this->type;
            if (ty == 1 || ty == 2 || ty == 3) {
                ty += 3;
            }
            else {
                ty -= 3;
            }
            game->mapButton[ty - 1]->setFocus();
        }
    }
    // for restart & quit
    else if (game->current == 5){
        // play sound effect
        if (event->key() == Qt::Key_Slash || event->key() == Qt::Key_Q){
            if (select->state() == QMediaPlayer::PlayingState)
                select->setPosition(0);
            else if (select->state() == QMediaPlayer::StoppedState)
                select->play();
        }
        else{
            if (choose->state() == QMediaPlayer::PlayingState)
                choose->setPosition(0);
            else if (choose->state() == QMediaPlayer::StoppedState)
                choose->play();
        }

        if (event->key() == Qt::Key_Slash || event->key() == Qt::Key_Q){
            if (this->type == 1){ // restart
                emit clicked(RESTART_CODE);
            }
            else if (this->type == 2){ // quit
                emit clicked(QUIT_CODE);
            }
        }
        if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A
                    || event->key() == Qt::Key_Right || event->key() == Qt::Key_D){
            int ty = this->type;
            if (ty == 1) {
                game->quit->setFocus();
            }
            else {
                game->restart->setFocus();
            }
        }
    }
}

void TankButton::focusOutEvent(QFocusEvent *event){
    (void) event;
    emit focusOut(this->type - 1);
}

void TankButton::focusInEvent(QFocusEvent *event){
    (void) event;
    emit focusIn(this->type - 1);
}

