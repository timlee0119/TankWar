#ifndef WALL_H
#define WALL_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QGraphicsItem>

class Wall: public QGraphicsRectItem{
public:
    Wall(QGraphicsItem *parent=0);
    Wall(int posX, int posY, int width, int height, QGraphicsItem * parent=0);
    int posX,posY;
};

#endif // WALL_H
