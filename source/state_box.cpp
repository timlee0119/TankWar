#include "state_box.h"
#include "setting.h"
#include "Game.h"
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QBrush>
#include <QPen>
#include <QDebug>
#include "wall.h"

extern Game * game;

State_Box::State_Box(int index, int type, QGraphicsItem * parent): QGraphicsRectItem(parent){
    (void)parent;
    this->index = index;
    this->max_bullet = MAX_MAGAZINE[type-1];
    this->setZValue(30);
    Blood_Width = SCREEN_WIDTH/2 - 60;
    BloodBase = new QGraphicsRectItem(this);
    Blood = new QGraphicsRectItem(this);
    PowerBarBase = new QGraphicsRectItem(this);
    PowerBar = new QGraphicsRectItem(this);
    Bullet_Num = max_bullet;

    if (index == 1){
        this->setRect(SCREEN_WIDTH/2 ,GAME_SCREEN_HEIGHT,SCREEN_WIDTH/2,SCREEN_HEIGHT-GAME_SCREEN_HEIGHT);
        this->setBrush(QBrush(QImage(":/images/statusP1.png")));

        BloodBase->setRect(30 + SCREEN_WIDTH/2 ,50 + SCREEN_HEIGHT, Blood_Width ,30);
        Blood->setRect(30 + SCREEN_WIDTH/2 ,50 + SCREEN_HEIGHT, Blood_Width ,30);
        PowerBarBase->setRect(29 + SCREEN_WIDTH/2 ,80 + SCREEN_HEIGHT, Blood_Width ,10);
        PowerBar->setRect(29 + SCREEN_WIDTH/2 ,80 + SCREEN_HEIGHT, Blood_Width ,10);
        for (int i = 0; i < max_bullet; i++){
            magazine[i] = new QGraphicsPixmapItem(this);
            magazine[i]->setPixmap(QPixmap(":/images/magazine.png"));
            magazine[i]->setPos(SCREEN_WIDTH - 100 - (i*70) ,100 + SCREEN_HEIGHT);
            magazine[i]->setZValue(40);
        }
        // burned
        buff[0] = new QGraphicsPixmapItem();
        buff[0]->setPixmap(QPixmap(":/images/burned.png"));
        buff[0]->setPos(SCREEN_WIDTH - 180,13+SCREEN_HEIGHT);
        buff[0]->setZValue(40);

        // shield or healed
        if(game->player1->getType() == 4){
            buff[1] = new QGraphicsPixmapItem();
            buff[1]->setPixmap(QPixmap(":/images/healed.png"));
            buff[1]->setPos(SCREEN_WIDTH - 220,13+SCREEN_HEIGHT);
            buff[1]->setZValue(40);

        }
        else if(game->player1->getType() == 5){
            buff[1] = new QGraphicsPixmapItem();
            buff[1]->setPixmap(QPixmap(":/images/shield.png"));
            buff[1]->setPos(SCREEN_WIDTH - 220,13+SCREEN_HEIGHT);
            buff[1]->setZValue(40);

        }
        else
            buff[1] = nullptr;
    }
    else if (index == 2){
        this->setRect(0 ,GAME_SCREEN_HEIGHT,SCREEN_WIDTH/2,SCREEN_HEIGHT-GAME_SCREEN_HEIGHT);
        this->setBrush(QBrush(QImage(":/images/statusP2.png")));

        BloodBase->setRect(30,50 + SCREEN_HEIGHT, Blood_Width ,30);
        Blood->setRect(30,50 + SCREEN_HEIGHT, Blood_Width ,30);
        PowerBarBase->setRect(29,80 + SCREEN_HEIGHT, Blood_Width ,10);
        PowerBar->setRect(29,80 + SCREEN_HEIGHT, Blood_Width ,10);
        for (int i = 0; i < max_bullet; i++){
            magazine[i] = new QGraphicsPixmapItem(this);
            magazine[i]->setPixmap(QPixmap(":/images/magazine.png"));
            magazine[i]->setPos(30 + i * 70,100 + SCREEN_HEIGHT);
            magazine[i]->setZValue(40);
        }
        // burned
        buff[0] = new QGraphicsPixmapItem();
        buff[0]->setPixmap(QPixmap(":/images/burned.png"));
        buff[0]->setPos(150,13+SCREEN_HEIGHT);
        buff[0]->setZValue(40);
        // shield or healed
        if(game->player2->getType() == 4){
            buff[1] = new QGraphicsPixmapItem();
            buff[1]->setPixmap(QPixmap(":/images/healed.png"));
            buff[1]->setPos(190,13+SCREEN_HEIGHT);
            buff[1]->setZValue(40);

        }
        else if(game->player2->getType() == 5){
            buff[1] = new QGraphicsPixmapItem();
            buff[1]->setPixmap(QPixmap(":/images/shield.png"));
            buff[1]->setPos(190,13+SCREEN_HEIGHT);
            buff[1]->setZValue(40);
        }
        else
            buff[1] = nullptr;
    }

    Blood->setBrush(QBrush(Qt::red));
    BloodBase->setBrush(QBrush(Qt::darkRed));
    PowerBar->setBrush(QBrush(Qt::blue));
    PowerBarBase->setBrush(QBrush(Qt::darkBlue));

    this->setPen(QPen(Qt::darkGray,3,Qt::SolidLine));
    Blood->setPen(QPen(Qt::NoPen));
    BloodBase->setPen(QPen(Qt::NoPen));
    PowerBar->setPen(QPen(Qt::NoPen));
    PowerBarBase->setPen(QPen(Qt::NoPen));

}

State_Box::~State_Box()
{
    for(int i = 0; i < max_bullet; i++){
        delete magazine[i];
        magazine[i] = nullptr;
    }
    delete Blood;
    Blood = nullptr;
    delete BloodBase;
    BloodBase = nullptr;
    delete PowerBar;
    PowerBar = nullptr;
    delete PowerBarBase;
    PowerBarBase = nullptr;
    delete buff[0];
    buff[0] = nullptr;
    delete buff[1];
    buff[1] = nullptr;
}

void State_Box::ChangeBlood(double state){
    if (this->index == 1){
        Blood->setRect((30 + SCREEN_WIDTH/2) + ( Blood_Width * (1 - state)),50 + SCREEN_HEIGHT, Blood_Width * state,30);
    }
    else if (this->index == 2){
        Blood->setRect(30 ,50 + SCREEN_HEIGHT, this->Blood_Width * state, 30);
    }
}

void State_Box::ChangePower(double state)
{
    if (this->index == 1){
        PowerBar->setRect((29 + SCREEN_WIDTH/2) + ( Blood_Width * (1 - state)),80 + SCREEN_HEIGHT, Blood_Width * state,10);
    }
    else if (this->index == 2){
        PowerBar->setRect(29 ,80 + SCREEN_HEIGHT, Blood_Width * state, 10);
    }
}


void State_Box::AddBullet(){
    if(Bullet_Num < max_bullet){
        game->scene()->addItem(magazine[Bullet_Num]);
        Bullet_Num ++;
    }
}

void State_Box::CostBullet(){
    if(Bullet_Num > 0){
        Bullet_Num --;
        game->scene()->removeItem(magazine[Bullet_Num]);
    }
}

