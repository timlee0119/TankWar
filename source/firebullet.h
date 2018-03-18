#ifndef FIREBULLET_H
#define FIREBULLET_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>

class Firebullet: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Firebullet(double angle, QGraphicsItem * parent = 0);
    ~Firebullet();
public slots:
    void move();
private:
    int tankType;
    double speed;
    double angle;
    bool reflect = false;
    QTimer * timer;
signals:
    void collide();
};

#endif // FIREBULLET_H
