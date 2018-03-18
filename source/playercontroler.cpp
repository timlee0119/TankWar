#include <QKeyEvent>
#include <cmath>
#include <QDebug>
#include "setting.h"
#include "playercontroler.h"
#include "Player.h"
#include "Game.h"
#include "Bullet.h"

#define PI 3.14159265

extern Game * game;

PlayerControler::PlayerControler(){
    setRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
}

void PlayerControler::keyPressEvent(QKeyEvent *event){
    /***for the player1***/
    if(game->player1->getBloodRate() > 0){
        // move the player left and right
        if (event->key() == Qt::Key_Left){
            //qDebug() << "left!!!";
            if (!game->player1->direction[0])
                game->player1->direction[0] = true;
        }
        else if (event->key() == Qt::Key_Right){
            if (!game->player1->direction[1])
                game->player1->direction[1] = true;
        }// move the player toward and backward
        else if (event->key() == Qt::Key_Up){
            if (!game->player1->moving[0])
                game->player1->moving[0] = true;
        }
        else if (event->key() == Qt::Key_Down){
            if (!game->player1->moving[1])
                game->player1->moving[1] = true;
        }
        // shoot with slash
        else if (event->key() == Qt::Key_Slash){
            // shoot
            // create one bullet because at least player shoot a bullet
            game->player1->createBullet();
            game->box1->CostBullet();
        }
        // hero power
        else if (event->key() == Qt::Key_Period){
            game->player1->usePower();
        }
    }
    /***for the player2***/
    if(game->player2->getBloodRate() > 0){
        // move the player left and right
        if (event->key() == Qt::Key_A){
            //qDebug() << "left!!!";
            if (!game->player2->direction[0])
                game->player2->direction[0] = true;
        }
        else if (event->key() == Qt::Key_D){
            if (!game->player2->direction[1])
                game->player2->direction[1] = true;
        }// move the player toward and backward
        else if (event->key() == Qt::Key_W){
            if (!game->player2->moving[0])
                game->player2->moving[0] = true;
        }
        else if (event->key() == Qt::Key_S){
            if (!game->player2->moving[1])
                game->player2->moving[1] = true;
        }
        else if (event->key() == Qt::Key_Q){
            // shoot
            // create one bullet because at least player shoot a bullet
            game->player2->createBullet();
            game->box2->CostBullet();
        }
        // hero power
        else if (event->key() == Qt::Key_1){
            game->player2->usePower();
        }
    }

    // cheat
    if (event->key() == Qt::Key_Y){
        game->player1->power = game->player1->Max_Power;
        game->player2->power = game->player2->Max_Power;
    }
}

void PlayerControler::keyReleaseEvent(QKeyEvent *event){
    /***for the player1***/
    if(game->player1->getBloodRate() > 0){
        // stop moving the player left and right
        if (event->key() == Qt::Key_Left){
            //qDebug() << "Release left!!!";
            game->player1->direction[0] = false;
        }
        else if (event->key() == Qt::Key_Right){
            game->player1->direction[1] = false;
        }// stop moving the player toward and backward
        else if (event->key() == Qt::Key_Up){
            game->player1->moving[0] = false;
        }
        else if (event->key() == Qt::Key_Down){
            game->player1->moving[1] = false;
        }
    }
    /***for the player2***/
    if(game->player2->getBloodRate() > 0){
        if (event->key() == Qt::Key_A){
            //qDebug() << "Release left!!!";
            game->player2->direction[0] = false;
        }
        else if (event->key() == Qt::Key_D){
            game->player2->direction[1] = false;
        }// stop moving the player toward and backward
        else if (event->key() == Qt::Key_W){
            game->player2->moving[0] = false;
        }
        else if (event->key() == Qt::Key_S){
            game->player2->moving[1] = false;
        }
    }
}
