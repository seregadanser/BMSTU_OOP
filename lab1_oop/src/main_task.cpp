#include "../include/main_task.h"

errors main_task(const task &new_task)
{
    static figure main_figure = init();
    errors err = OK;
    switch (new_task.action)
    {
    case LOAD:
        err = create_figure(main_figure, new_task.fn);
        break;
    case MOVE:
        err = move_figure(main_figure, new_task.mov);
        break;
    case ROTATE:
        err = rotate_figure(main_figure, new_task.rot);
        break;
    case SCALE:
        err = scale_figure(main_figure, new_task.sca);
        break;
    case DRAW:
        err = draw_figure(main_figure, new_task.p);
        break;
    case CLEAN:
        destroy_figure(main_figure);
        break;
    default:
        break;
    }
    return err;
}