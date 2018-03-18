#ifndef PLAYERCONTROL_H
#define PLAYERCONTROL_H
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QObject>

class PlayerControler:public QObject, public QGraphicsRectItem{
    Q_OBJECT
public:
    PlayerControler();
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
};

#endif // PLAYERCONTROL_H
