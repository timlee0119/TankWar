#include "turret.h"
#include "Bullet.h"
#include <cmath>
#include <QGraphicsScene>
#include <QDebug>

#include "setting.h"
#include "Game.h"
#define PI 3.14159265

extern Game * game;

Turret::Turret(QGraphicsItem *parent)
{
    (void)parent;
    angle = 0;

    setPixmap(QPixmap(":/images/turret.png"));
    setTransformOriginPoint(50,50);

    //start rotate timer
    timerR = new QTimer(this);
    connect(timerR,SIGNAL(timeout()),this,SLOT(rotate()));
    timerR->start(1000/TANK_REFRESH_RATE);

    //start bullet timer
    timerB = new QTimer(this);
    connect(timerB,SIGNAL(timeout()),this,SLOT(creatBullet()));
    timerB->start(1000);

    // set injure sound
    injuring = new QMediaPlayer(this);
    injuring->setMedia(QUrl("qrc:/sounds/attacked.mp3"));
    injuring->setVolume(30);


    // set bounce sound
    for(int i = 0; i < 6; i++){
        bounce[i] = new QMediaPlayer(this);
        bounce[i]->setMedia(QUrl("qrc:/sounds/bounce.mp3"));
        bounce[i]->setVolume(30);
    }
    bounce_order = 0;

    // set fire sound
    for(int i = 0; i < 6; i++){
        bulletSound[i] = new QMediaPlayer(this);
        bulletSound[i]->setMedia(QUrl("qrc:/sounds/fire.mp3"));
        bulletSound[i]->setVolume(30);
    }
    bulletSound_order = 0;

}

Turret::~Turret()
{
    delete timerR;
    timerR = nullptr;
    delete timerB;
    timerB = nullptr;

    for(int i = 0; i < 6; i++){
        delete bounce[i];
        bounce[i] = nullptr;
        delete bulletSound[i];
        bulletSound[i] = nullptr;
    }
    delete injuring;
    injuring = nullptr;
}

void Turret::creatBullet()
{
    double nx = pos().x()+(50-5)+(50+15)*sin((angle/180)*PI);
    double ny = pos().y()+(50-5)-(50+15)*cos((angle/180)*PI);

    Bullet * bullet = new Bullet(1, angle);
    bullet->setPos(nx,ny);
    scene()->addItem(bullet);

    connect(bullet,SIGNAL(collide()),this,SLOT(playBounce()));

    // play bulletSound
    if(bulletSound_order >= 6)
        bulletSound_order = 0;
    if (bulletSound[bulletSound_order]->state() == QMediaPlayer::PlayingState)
        bulletSound[bulletSound_order]->setPosition(0);
    else if (bulletSound[bulletSound_order]->state() == QMediaPlayer::StoppedState)
        bulletSound[bulletSound_order]->play();
    bulletSound_order ++;
}

void Turret::rotate()
{
    this->setRotation(angle);
    angle ++;
}

void Turret::playBounce()
{
    if(bounce_order >= 6)
        bounce_order = 0;
    if (bounce[bounce_order]->state() == QMediaPlayer::PlayingState)
        bounce[bounce_order]->setPosition(0);
    else if (bounce[bounce_order]->state() == QMediaPlayer::StoppedState)
        bounce[bounce_order]->play();
    bounce_order ++;
}
