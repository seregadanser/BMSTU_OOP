#ifndef TASK_H
#define TASK_H

#include "my_figure.h"
#include "errors.h"

enum action_t
    {
        MOVE,
        ROTATE,
        SCALE,
        LOAD, 
        CLEAN,
        DRAW
    };

typedef struct
{
    enum action_t action;
    union 
    {
        filename_ptr fn;
        rotate rot;
        movet mov;
        scale sca;
        canvas p;
    };
    
} task;

errors main_task(const task &new_task);

#endif