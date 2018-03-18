#include "wall.h"
#include "Game.h"
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QBrush>
#include <QPen>
extern Game * game;

Wall::Wall(QGraphicsItem *parent){
    (void) parent;
    setBrush(QBrush(QImage(":/images/wall.png")));
}

Wall::Wall(int posX, int posY, int width, int height, QGraphicsItem *parent){
    (void) parent;
    setRect(posX, posY, width, height);
    setBrush(QBrush(QImage(":/images/wall.png")));
    setPen(QPen(Qt::white, 4, Qt::NoPen));
    game->gameScene->addItem(this);
    this->posX = posX;
    this->posY = posY;
}

