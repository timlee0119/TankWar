#include "Player.h"
#include "Bullet.h"
#include "wall.h"
#include "river.h"
#include "firebullet.h"
#include "setting.h"
#include <QGraphicsScene>
#include <QApplication>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <cmath>
#include <QTimer>
#include <QList>
#include <QDebug>
#include <QPoint>
#include "Game.h"
#define PI 3.14159265
#define RESTART_CODE 1000

extern QApplication * app;
extern Game * game;

Player::Player(int id, int tankType, double a, QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    this->id = id;
    type = tankType;
    damage = BULLET_DAMAGE[type-1];
    health = TANK_MAX_HEALTH[type-1];
    Max_Health = TANK_MAX_HEALTH[type-1];
    power = TANK_MAX_POWER[type - 1] / 10;
    Max_Power = TANK_MAX_POWER[type - 1];
    recoverAmount = TANK_POWER_RECOVER_RATE[type -1];
    magazine = MAX_MAGAZINE[type-1];
    angle = a;
    speed = TANK_SPEED[type-1];
    oldX = 0;
    oldY = 0;
    direction[0] = false;
    direction[1] = false;
    moving[0] = false;
    moving[1] = false;
    thorn = false;
    fordash = false;
    powerUp = false;
    flameDot = 0;
    sword  = nullptr;
    lazerAnimation_Count = 49;

    // set sound effect
    for (int i = 0; i < 6; i++){
        heroPowerList[i] = new QMediaPlaylist(this);
    }
    heroPowerList[0]->addMedia(QUrl("qrc:/sounds/dash.mp3"));
    heroPowerList[1]->addMedia(QUrl("qrc:/sounds/flameBullet.mp3"));
    heroPowerList[2]->addMedia(QUrl("qrc:/sounds/sword.mp3"));
    heroPowerList[3]->addMedia(QUrl("qrc:/sounds/healing.mp3"));
    heroPowerList[4]->addMedia(QUrl("qrc:/sounds/thorn.mp3"));
    heroPowerList[5]->addMedia(QUrl("qrc:/sounds/lazer.mp3"));

    heroPower = new QMediaPlayer(this);
    heroPower->setPlaylist(heroPowerList[type-1]);
    heroPower->setVolume(EFFECT_VOLUME[type-1]);

    // set images
    tankImages[0] = new QPixmap(":/images/tank1.png");
    tankImages[1] = new QPixmap(":/images/tank2.png");
    tankImages[2] = new QPixmap(":/images/tank3.png");
    tankImages[3] = new QPixmap(":/images/tank4.png");
    tankImages[4] = new QPixmap(":/images/tank5.png");
    tankImages[5] = new QPixmap(":/images/tank6.png");

    tankInjuredImages[0] = new QPixmap(":/images/tank_injured1.png");
    tankInjuredImages[1] = new QPixmap(":/images/tank_injured2.png");
    tankInjuredImages[2] = new QPixmap(":/images/tank_injured3.png");
    tankInjuredImages[3] = new QPixmap(":/images/tank_injured4.png");
    tankInjuredImages[4] = new QPixmap(":/images/tank_injured5.png");
    tankInjuredImages[5] = new QPixmap(":/images/tank_injured6.png");

    // set the color of the tank
    setPixmap(*tankImages[type-1]);

    setTransformOriginPoint(TANK_WIDTH/2,TANK_HEIGHT/2);

    // set injure sound
    injuring = new QMediaPlayer(this);
    injuring->setMedia(QUrl("qrc:/sounds/attacked.mp3"));
    //injuring->setVolume(30);


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

    // refresh the position
    timerP = new QTimer(this);
    connect(timerP,SIGNAL(timeout()),this,SLOT(setNewPosition()));
    timerP->start(1000/TANK_REFRESH_RATE);

    timerF = nullptr;
    timerH = nullptr;
    timerT = nullptr;
    connect(timerP,SIGNAL(timeout()),this,SLOT(power_Recover()));
}

Player::~Player()
{
    for(int i = 0; i < 6; i++){
        delete bounce[i];
        bounce[i] = nullptr;
        delete bulletSound[i];
        bulletSound[i] = nullptr;
    }
    delete injuring;
    injuring = nullptr;
    delete timerP;
    timerP = nullptr;
    delete timerF;
    timerF = nullptr;
    delete timerH;
    timerH = nullptr;
    delete timerT;
    timerT = nullptr;
    for (int i = 0; i < 6; i++){
        delete heroPowerList[i];
        heroPowerList[i] = nullptr;
    }
    delete heroPower;
    heroPower = nullptr;

}

void Player::usePower()
{
    if(type == 1){
        if(!moving[0] && !moving[1])
            return;
    }

    int consume = TANK_POWER_CONSUME[type -1];
    if(this->power - consume > 0){
        power -= consume;
        if(this->id == 1)
            game->box1->ChangePower(this->getPowerRate());
        else
            game->box2->ChangePower(this->getPowerRate());

        // play hero power sound
        if (heroPower->state() == QMediaPlayer::PlayingState)
            heroPower->setPosition(0);
        else if (heroPower->state() == QMediaPlayer::StoppedState)
            heroPower->play();

        /*************************  Power  ******************************/
        // dash
        if (type == 1){
            fordash = true;
            for (int i = 0; i < 20; i++){
                this->move();
            }
            fordash = false;
        }
        // fire bullet
        else if (type == 2){
            double nx = pos().x()+(TANK_WIDTH/2-5)+(TANK_WIDTH/2+15)*sin((angle/180)*PI);
            double ny = pos().y()+(TANK_HEIGHT/2-5)-(TANK_HEIGHT/2+15)*cos((angle/180)*PI);
            Firebullet * firebullet = new Firebullet(angle);
            firebullet->setPos(nx,ny);
            scene()->addItem(firebullet);
            connect(firebullet,SIGNAL(collide()),this,SLOT(playBounce()));
        }
        // sword
        else if (type == 3){
            if (sword != nullptr){
                return;
            }

            sword = new QGraphicsPixmapItem(this);
            sword->setPixmap(QPixmap(":/images/sword.png"));
            sword->setPos(0,-30);

            QList<QGraphicsItem *> colliding_items = sword->collidingItems();
            for (int i = 0, n = colliding_items.size(); i < n; ++i){
                if (typeid(*(colliding_items[i])) == typeid(Player)){
                    Player * player;
                    if(colliding_items[i] == game->player1){
                        player = game->player1;
                    }
                    else{
                        player = game->player2;
                    }

                    player->injured(400);

                    delete this->sword;
                    this->sword = nullptr;
                }
                if (typeid(*(colliding_items[i])) == typeid(Bullet)){
                    scene()->removeItem(colliding_items[i]);
                    delete colliding_items[i];
                }
            }

            QTimer::singleShot(100,this,SLOT(deleteSword()));
        }
        // recover
        else if (type == 4){
            if (timerH != nullptr){
                delete timerH;
                timerH = nullptr;
                recoverCount = 0;
                if (id == 1)
                    game->scene()->removeItem(game->box1->buff[1]);
                else
                    game->scene()->removeItem(game->box2->buff[1]);
            }

            // set image
            this->setPixmap(QPixmap(":/images/recoverTank.png"));
            QTimer::singleShot(800,this,SLOT(recoverOut()));
            // set buff
            if(id == 1)
                game->scene()->addItem(game->box1->buff[1]);
            else
                game->scene()->addItem(game->box2->buff[1]);

            timerH = new QTimer(this);
            connect(timerH,SIGNAL(timeout()),this,SLOT(recover()));
            timerH->start(1000);
        }
        // thorn
        else if (type == 5){
            if (thorn)
                timerT->setInterval(5000);
            else {
                thorn = true;
                this->setPixmap(QPixmap(":/images/thornTank.png"));
                timerT = new QTimer(this);
                //QTimer::singleShot(5000,this,SLOT(thornOut()));
                connect(timerT,SIGNAL(timeout()),this,SLOT(thornOut()));
                timerT->start(5000);
                if (id == 1)
                    game->scene()->addItem(game->box1->buff[1]);
                else
                    game->scene()->addItem(game->box2->buff[1]);
            }
        }
        // lazer
        else if (type == 6){
            if(lazerAnimation_Count>= 49){
                lazerAnimation_Count = 0;
                lazer = new QGraphicsRectItem(this);
                this->setZValue(1);
                lazer->setZValue(3);
                lazer->setBrush(QBrush(Qt::white));
                lazer->setPen(QPen(Qt::NoPen));
                lazerAnimation();
            }
        }
        /*************************  Power  ******************************/
    }

}

void Player::setNewPosition(){
    oldAngle = angle;

    // rotate first
    if (direction[0]){
        angle -= ANGLE_PER_REFRESH;
        if (angle < 0)
            angle += 360;
    }
    else if (direction[1]){
        angle += ANGLE_PER_REFRESH;
        if (angle >= 360)
            angle -= 360;
    }
    // rotate
    setRotation(angle);
    QList<QGraphicsItem *> colliding_items;
    colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Wall)
                || typeid(*(colliding_items[i])) == typeid(Player) || typeid(*(colliding_items[i])) == typeid(River)){
            // rollback angle
            setRotation(oldAngle);
            angle = oldAngle;
        }
    }

    // move
    move();
}


void Player::move()
{
    oldX = pos().x();
    oldY = pos().y();
    double nx = oldX, ny = oldY;

    // move later
    if (moving[0]){
        nx = pos().x()+speed*sin((angle/180)*PI);
        ny = pos().y()-speed*cos((angle/180)*PI);
    }
    else if (moving[1]){
        nx = pos().x()-speed*sin((angle/180)*PI);
        ny = pos().y()+speed*cos((angle/180)*PI);
    }

    // move X axis
    setPos(nx, pos().y());
    QList<QGraphicsItem *> colliding_items;
    colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Wall)
                || typeid(*(colliding_items[i])) == typeid(Player) || typeid(*(colliding_items[i])) == typeid(River)){
            // rollback X
            setPos(oldX, pos().y());
            if (typeid(*(colliding_items[i])) == typeid(Player) && fordash){
                if (id == 1)
                    game->player2->injured(5);
                else
                    game->player1->injured(5);
            }
        }
    }
    // move Y axis
    setPos(pos().x(), ny);
    colliding_items = collidingItems();
    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Wall)
                || typeid(*(colliding_items[i])) == typeid(Player) || typeid(*(colliding_items[i])) == typeid(River)){
            // rollback Y
            setPos(pos().x(), oldY);
        }
    }
}

void Player::createBullet(){
    if (magazine > 0){
        // create a bullet
        double nx = pos().x()+(TANK_WIDTH/2-5)+(TANK_WIDTH/2+15)*sin((angle/180)*PI);
        double ny = pos().y()+(TANK_HEIGHT/2-5)-(TANK_HEIGHT/2+15)*cos((angle/180)*PI);

        Bullet * bullet = new Bullet(this->type, angle);
        bullet->setPos(nx,ny);
        scene()->addItem(bullet);
        magazine--;
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
}

void Player::addBullet(){
    if (magazine < MAX_MAGAZINE[type-1])
        magazine++;
}

void Player::injured(int damage){
    if (game->isOver){
        return;
    }

    // play injured sound
    if (injuring->state() == QMediaPlayer::PlayingState)
        injuring->setPosition(0);
    else if (injuring->state() == QMediaPlayer::StoppedState)
        injuring->play();

    if (health - damage >= 0){
        health -= damage;
        if (health > Max_Health)
            health = Max_Health;
    }
    else
        health = 0;

//    // power up
//    if (health/Max_Health <= 0.3)
//        recoverAmount = recoverAmount * 1.5;

    // change blood
    if (id == 1)
        game->box1->ChangeBlood(this->getBloodRate());
    else
        game->box2->ChangeBlood(this->getBloodRate());
    // dead
    if (health == 0){
        moving[0] = false;
        moving[1] = false;
        direction[0] = false;
        direction[1] = false;
        angle = 0;
        this->setPixmap(QPixmap(":/images/tombstone.png"));
        emit dead(this->id);
    }
    else{
        // change image
        this->setPixmap(*tankInjuredImages[this->type-1]);
        QTimer::singleShot(200,this,SLOT(changeInjuredImage()));
    }

    // thorn shield
    if (thorn){
        if (id == 1){
            if (game->player2->type == 5 && game->player2->thorn)
                return;
            game->player2->injured(damage/2);
        }
        else {
            if (game->player1->type == 5 && game->player1->thorn)
                return;
            game->player1->injured(damage/2);
        }
    }

}

void Player::power_Recover(){
    //double recover = TANK_POWER_RECOVER_RATE[type -1];
    if(this->power + recoverAmount < this->Max_Power){
        if (powerUp == true)
            power += recoverAmount*1.5;
        else
            power += recoverAmount;
    }
    if(this->id == 1)
        game->box1->ChangePower(this->getPowerRate());
    else
        game->box2->ChangePower(this->getPowerRate());
}

void Player::fireInjured(){
    if (game->isOver)
        return;

    // play injured sound
    if (injuring->state() == QMediaPlayer::PlayingState)
        injuring->setPosition(0);
    else if (injuring->state() == QMediaPlayer::StoppedState)
        injuring->play();

    if (health - 200 >= 0)
        health -= 200;
    else {
        health = 0;
    }

    if (id == 1)
        game->box1->ChangeBlood(this->getBloodRate());
    else
        game->box2->ChangeBlood(this->getBloodRate());

    // dead
    if (health == 0){
        moving[0] = false;
        moving[1] = false;
        direction[0] = false;
        direction[1] = false;
        angle = 0;
        this->setPixmap(QPixmap(":/images/tombstone.png"));
        emit dead(this->id);
    }
    else{
        // change image
        this->setPixmap(*tankInjuredImages[this->type-1]);
        QTimer::singleShot(200,this,SLOT(changeInjuredImage()));
    }

    // thorn sheild
    if (thorn){
        if (id == 1)
            game->player2->injured(damage/2);
        else
            game->player1->injured(damage/2);
    }

    // flamed dot
    if (timerF != nullptr){
        delete timerF;
        timerF = nullptr;
        flameDot = 0;
        if (id == 1)
            game->scene()->removeItem(game->box1->buff[0]);
        else
            game->scene()->removeItem(game->box2->buff[0]);
        speed = TANK_SPEED[type-1];
    }

    // burned debuff
    if (id == 1)
        game->scene()->addItem(game->box1->buff[0]);
    else
        game->scene()->addItem(game->box2->buff[0]);
    // slow down
    speed = TANK_SPEED[type-1] * 0.6;

    timerF = new QTimer(this);
    connect(timerF,SIGNAL(timeout()),this,SLOT(dotInjured()));
    timerF->start(1000);
}

void Player::dotInjured(){
    if (game->isOver)
        return;

    // play injured sound
    if (injuring->state() == QMediaPlayer::PlayingState)
        injuring->setPosition(0);
    else if (injuring->state() == QMediaPlayer::StoppedState)
        injuring->play();
    // change image
    this->setPixmap(*tankInjuredImages[this->type-1]);
    QTimer::singleShot(200,this,SLOT(changeInjuredImage()));

    if (health - 60 >= 50)
        health -= 60;

    if (id == 1)
        game->box1->ChangeBlood(this->getBloodRate());
    else
        game->box2->ChangeBlood(this->getBloodRate());
    flameDot++;
    if (flameDot == 5){
        timerF->stop();
        delete timerF;
        timerF = nullptr;
        flameDot = 0;

        // debuff off
        if (id == 1)
            game->scene()->removeItem(game->box1->buff[0]);
        else
            game->scene()->removeItem(game->box2->buff[0]);
        speed = TANK_SPEED[type-1];
    }
}

double Player::getBloodRate(){
    double rate = health/Max_Health;
    // power up
    if (rate <= 0.3)
        powerUp = true;
    else
        powerUp = false;
    return rate;
}

double Player::getPowerRate(){
    return this->power/Max_Power;
}

void Player::playBounce(){
    if(bounce_order >= 6)
        bounce_order = 0;
    if (bounce[bounce_order]->state() == QMediaPlayer::PlayingState)
        bounce[bounce_order]->setPosition(0);
    else if (bounce[bounce_order]->state() == QMediaPlayer::StoppedState)
        bounce[bounce_order]->play();
    bounce_order ++;
}

void Player::recover(){
    if (game->isOver)
        return;

    // set image
    this->setPixmap(QPixmap(":/images/recoverTank.png"));
    QTimer::singleShot(800,this,SLOT(recoverOut()));

    if (health + 40 > Max_Health)
        health = Max_Health;
    else
        health += 40;

    if (id == 1)
        game->box1->ChangeBlood(this->getBloodRate());
    else
        game->box2->ChangeBlood(this->getBloodRate());

    recoverCount++;
    if (recoverCount == 5){
        timerH->stop();
        delete timerH;
        timerH = nullptr;
        recoverCount = 0;

        if(id == 1)
            game->scene()->removeItem(game->box1->buff[1]);
        else
            game->scene()->removeItem(game->box2->buff[1]);
    }
}

void Player::changeInjuredImage(){
    if (health == 0){
        return;
    }

    if (thorn){
        this->setPixmap(QPixmap(":/images/thornTank.png"));
    }
    else{
        this->setPixmap(*tankImages[this->type-1]);
    }
}

void Player::lazerAnimation(){

    int count = lazerAnimation_Count;

    if(count <= 48){
        QList<QGraphicsItem *> colliding_items = lazer->collidingItems();
        for (int i = 0, n = colliding_items.size(); i < n; ++i){
            if (typeid(*(colliding_items[i])) == typeid(Player))
            {
                Player * player;
                if(colliding_items[i] == game->player1){
                    player = game->player1;
                }
                else{
                    player = game->player2;
                }

                // adjust the damage
                int dmg;
                if (count <= 23){
                    dmg = 5;
                }
                else if (count > 23 && count <= 33){
                    dmg = 50;
                }
                else{
                    dmg = 0;
                }

                if(player != this)
                    player->injured(dmg);
            }
            if (typeid(*(colliding_items[i])) == typeid(Bullet))
            {
                scene()->removeItem(colliding_items[i]);
                delete colliding_items[i];
            }
        }
    }

    if(count <= 20){
        lazer->setRect(29,-1500+7,2,1500);
        QTimer::singleShot(50,this,SLOT(lazerAnimation()));
    }
    else if(count <= 23){
        double cc = count - 20;
        lazer->setRect((60-(2+6*cc))/2,-1500+7,2+6*cc,1500);
        QTimer::singleShot(50,this,SLOT(lazerAnimation()));
    }
    else if(count <= 33){
        if(count %2 == 0)
            lazer->setRect(20,-1500+7,20,1500);
        else
            lazer->setRect(21,-1500+7,18,1500);
        QTimer::singleShot(50,this,SLOT(lazerAnimation()));
    }
    else if(count <= 48){
        double cc = 48-count;
        lazer->setRect((60-((20/15)*cc))/2,-1500+7,(20/15)*cc,1500);
        QTimer::singleShot(50,this,SLOT(lazerAnimation()));
    }
    if(count == 49){
        delete lazer;
        lazer = nullptr;
    }
    else{
        this->lazerAnimation_Count++;
        if(count < 23 ){
            if(count %2 == 0)
                lazer->setBrush(QBrush(Qt::red));
            else
                lazer->setBrush(QBrush(Qt::white));
        }
        if(count == 23){
            lazer->setBrush(QBrush(Qt::white));
            lazer->setPen(QPen(Qt::red,2));
        }
        if(count == 33){
            lazer->setPen(QPen(Qt::NoPen));

        }
    }
}

void Player::thornOut(){
    if (game->isOver)
        return;
    if(id == 1)
        game->scene()->removeItem(game->box1->buff[1]);
    else
        game->scene()->removeItem(game->box2->buff[1]);
    this->setPixmap(*tankImages[this->type-1]);
    this->thorn = false;
    delete timerT;
    timerT = nullptr;
}

void Player::recoverOut(){
    if (game->isOver)
        return;

    this->setPixmap(*tankImages[this->type-1]);
}

void Player::deleteSword(){
    if (this->sword != nullptr){
        delete this->sword;
        this->sword = nullptr;
    }
}
