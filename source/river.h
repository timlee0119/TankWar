#ifndef RIVER_H
#define RIVER_H

#include "wall.h"

class River:public Wall{
public:
    River(int posX, int posY, int width, int height, QGraphicsItem * parent=0);
};

#endif // RIVER_H
