#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsItem>
#include <QObject>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTimer>
#include "playercontroler.h"

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    friend class PlayerControler;
public:
    Player(int, int, double, QGraphicsItem * parent=0);
    ~Player();
    int getHealth() { return this->health; }
    int getType() { return this->type;}
    void usePower();
    void move();
    void fireInjured();

public slots:
    void setNewPosition();
    void createBullet();
    void addBullet();
    void injured(int);
    void power_Recover();
    double getBloodRate();
    double getPowerRate();
    void playBounce();
    void lazerAnimation();
    void dotInjured();
    void thornOut();
    void recoverOut();
    void deleteSword();
    void recover();
    void changeInjuredImage();
private:
    // which player
    int id;
    // base on tonk's type
    int type;
    int damage;
    double health;
    int Max_Health;
    double power;
    int Max_Power;
    double recoverAmount;
    int magazine;
    // tnak information
    double angle;
    double speed;
    double oldX;
    double oldY;
    double oldAngle;
    bool direction[2]; // record the angle situation, 0 for left, 1 for right
    bool moving[2]; // record the moving situation, 0 for toward, 1 for backward
    bool powerUp;

    QTimer * timerP;
    QTimer * timerF;
    QTimer * timerH;
    QTimer * timerT;

    //QMediaPlayer * bulletSound;
    QMediaPlayer * bounce[6];
    int bounce_order;
    QMediaPlayer * bulletSound[6];
    int bulletSound_order;
    QMediaPlayer * injuring;
    // hero power sound
    QMediaPlaylist * heroPowerList[6];
    QMediaPlayer * heroPower;

    // lazer animation
    int lazerAnimation_Count;
    QGraphicsRectItem* lazer;
    // flame bullet
    int flameDot;
    // thorn sheild
    bool thorn;
    // sword skill
    QGraphicsPixmapItem * sword;
    // recover
    int recoverCount;
    // dash
    bool fordash;

    // images
    QPixmap * tankImages[6];
    QPixmap * tankInjuredImages[6];

signals:
    void dead(int loser);
};

#endif // PLAYER_H
