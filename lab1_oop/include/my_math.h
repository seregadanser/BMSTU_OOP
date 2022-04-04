#ifndef MATH_H
#define MATH_H

#include "my_type.h"
//#include <math.h>
#include <cmath>

#define PI 3.1415

typedef struct
{
    double angleX;
    double angleY;
    double angleZ;
    point center;
} rotate;

typedef struct
{
    double x;
    double y;
    double z;
} movet;

typedef struct
{
    double x;
    double y;
    double z;
    point center;
} scale;

errors scale_points(point_arr &arr, const scale &coefs);
errors rotate_points(point_arr &arr, const rotate &coeff);
errors move_points(point_arr &arr, const movet &coeff);

#endif