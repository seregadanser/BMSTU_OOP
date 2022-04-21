#ifndef FIGURE_H
#define FIGURE_H

#include <stdlib.h>
#include <stdio.h>
#include "my_type.h"
#include "my_math.h"
#include "errors.h"
#include "edges.h"

#include "draw.h"

typedef struct 
{
    point_arr points_arr;
    connections_arr conect_arr;
}figure;

typedef const char* filename_ptr;
typedef char* filename_ptr1;

//errors create_figure( figure &fig, filename_ptr fn);
errors create_figure(figure &figure1, filename_ptr filename);
figure init();
void destroy_figure(figure &fig);

errors rotate_figure(figure &fig, const rotate &coeff);
errors move_figure(figure &fig, const movet &coeff);
errors scale_figure(figure &fig, const scale &coeff);

errors draw_figure(const figure &my_f, const  canvas &pp);

#endif