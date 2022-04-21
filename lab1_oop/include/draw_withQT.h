#ifndef DRAW_QT_H
#define DRAW_QT_H

#include <QGraphicsScene>
#include <QPen>
#include "my_type.h"
#include <random>

typedef struct
{
    QGraphicsScene *scene;
    double width;
    double height;
} canvas;

void draw_line(const point pt1, const point pt2, const canvas &canvas);
void clear_scene(const canvas &canvas);


#endif
