#ifndef STATE_BOX_H
#define STATE_BOX_H
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QObject>
#include "setting.h"

class State_Box:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    State_Box(int index, int type, QGraphicsItem * parent = 0);
    ~State_Box();
    void CostBullet();
    void ChangeBlood(double);
    void ChangePower(double);
    QGraphicsPixmapItem * magazine[7];
    QGraphicsPixmapItem * buff[2];
public slots:
    void AddBullet();
private:
    QGraphicsRectItem *  Blood;
    QGraphicsRectItem *  BloodBase;
    QGraphicsRectItem *  PowerBar;
    QGraphicsRectItem *  PowerBarBase;
    int Blood_Width;
    int index;
    int Bullet_Num;
    int max_bullet;
};


#endif // STATE_BOX_H
