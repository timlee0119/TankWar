#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>

class Bullet: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Bullet(int type, double angle, QGraphicsItem * parent=0);
    ~Bullet();
public slots:
    void move();
protected:
    double speed;
    double angle;
    bool reflect = false;
    int tankType;
    QTimer * timer;
signals:
    void collide();
};

#endif // BULLET_H
