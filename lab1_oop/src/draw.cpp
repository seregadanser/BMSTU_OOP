#include "../include/draw.h"

static void draw_line_with_connection(const point_arr &pa, const connections &ca, const canvas &canvas)
{
    draw_line(pa.arr[ca.from], pa.arr[ca.to], canvas);
}

errors draw_lines_with_connections(const point_arr &pa, const connections_arr &ca, const canvas &canvas)
{
    errors err = OK;
    if (pa.arr == nullptr || ca.arr == nullptr)
        err = INVALID_FIURE;
    else
    {
        for (int i = 0; i < ca.size; i++)
            {
                draw_line_with_connection(pa, ca.arr[i], canvas);
            }
    }
    return err;
}
