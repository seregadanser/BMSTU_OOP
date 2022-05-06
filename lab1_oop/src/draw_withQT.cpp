#include "../include/draw_withQT.h"

void draw_line(const point pt1, const point pt2, const canvas &canvas)
{
    /*QPen *arr = new QPen[5];
    arr[1].setColor(Qt::red);
    arr[1].setWidth(3);
    arr[2].setColor(Qt::black);
    arr[2].setWidth(3);
    arr[3].setColor(Qt::white);
    arr[3].setWidth(3);
    arr[4].setColor(Qt::yellow);
    arr[4].setWidth(3);
    arr[0].setColor(Qt::green);
    arr[0].setWidth(3);
    //arr[1].setJoinStyle()*/
    QPen pen(Qt::red, 3, Qt::CustomDashLine, Qt::SquareCap, Qt::MiterJoin);
    QGraphicsScene *scene = canvas.scene;
    scene->addLine(pt1.x, -pt1.y, pt2.x, -pt2.y, pen);
    //delete[] arr;
}

void clear_scene(const canvas &canvas)
{
    canvas.scene->clear();
}