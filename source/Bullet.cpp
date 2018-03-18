#include "Bullet.h"
#include "Game.h"
#include "setting.h"
#include "wall.h"
#include "state_box.h"
#include "firebullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <cmath>
#define PI 3.14159265
#include <QDebug>

extern Game * game; // there is an external global object called game

Bullet::Bullet(int type, double angle, QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    // drew the bullet
    setPixmap(QPixmap(":/images/bullet.png"));

    this->angle = angle;
    this->tankType = type;
    this->speed = BULLET_SPEED[this->tankType-1];

    // make/connect a timer to move() the bullet every so often
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));

    // start the timer
    timer->start(1000/BULLET_REFRESH_RATE);
}

Bullet::~Bullet()
{
    delete timer;
    timer = nullptr;
}

void Bullet::move(){
    // get a list of all the items currently colliding with this bullet
    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Player))
        {
            Player * player;
            if(colliding_items[i] == game->player1){
                player = game->player1;
            }
            else{
                player = game->player2;
            }

            player->injured(BULLET_DAMAGE[this->tankType-1]);

            scene()->removeItem(this);
            delete this;

            // return (all code below refers to a non existint bullet)
            return;
        }

        if (typeid(*(colliding_items[i])) == typeid(Wall))
        {
            emit collide();

            int num = game->Wall_Number[game->mapType - 1];
            Wall* now;
            for(int j = 0; j < num; j ++){
                if(colliding_items[i] == game->w[j]){
                    now = game->w[j];
                    break;
                }
            }

            if(reflect){
                scene()->removeItem(this);
                delete this;
                return;
            }
            else
                reflect = true;

            double ox = this->pos().x()+6;//the x when the bullet touch the wall
            double oy = this->pos().y()+6;//the y when the bullet touch the wall

            double tan = now->rect().height()/now->rect().width();//the tangent line of the wall(left up & right down)
            double ntan = 0;
            if(now->pos().x() == ox)//when the tangent line do not exist , set it to -1
                ntan = -1;
            else
                ntan = (now->posY-oy)/(now->posX-ox);//else set the tangent
            if(ntan > tan || (ntan < 0 && (now->posY-oy) > 0))
                angle = 180 - angle;
            else
                angle = 360 - angle;
        }

        if (typeid(*(colliding_items[i])) == typeid(Bullet) || typeid(*(colliding_items[i])) == typeid(Firebullet))
        {
            emit collide();

            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);
            delete colliding_items[i];
            delete this;
            return;
        }
        if (typeid(*(colliding_items[i])) == typeid(Turret))
        {
            emit collide();
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    // if there was no collision with an Enemy, move the bullet forward
    double nx = pos().x()+speed*sin((angle/180)*PI);
    double ny = pos().y()-speed*cos((angle/180)*PI);
    setPos(nx,ny);
}
