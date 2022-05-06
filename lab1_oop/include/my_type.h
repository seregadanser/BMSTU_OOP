#ifndef TYPE_H
#define TYPE_H

#include "errors.h"


typedef struct
{
    double x;
    double y;
    double z;
} point;

typedef point* point_arr_ptr;

typedef struct
{
    point_arr_ptr arr;
    int size;
} point_arr;

typedef FILE* file_ptr;

point new_point(double x, double y, double z);

void init_my_type_arr(point_arr &arr);
void destruct_my_type_arr(point_arr &arr);
errors fill_point_array(point_arr &arr, file_ptr f);
int get_number_of_points(point_arr &arr);

#endif