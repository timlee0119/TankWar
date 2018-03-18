#ifndef TURRET_H
#define TURRET_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QMediaPlayer>

class Turret:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Turret(QGraphicsItem * parent = 0);
    ~Turret();
public slots:
    void creatBullet();
    void rotate();
    void playBounce();
private:
    double angle;
    QTimer * timerR;
    QTimer * timerB;

    QMediaPlayer * bounce[6];
    int bounce_order;
    QMediaPlayer * bulletSound[6];
    int bulletSound_order;
    QMediaPlayer * injuring;
};

#endif // TURRET_H
