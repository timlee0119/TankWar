#include "river.h"
#include <QBrush>

River::River(int posX, int posY, int width, int height, QGraphicsItem *parent):Wall(posX,posY,width,height,parent){
    setBrush(QBrush(QImage(":/images/origin_river.png")));
}
