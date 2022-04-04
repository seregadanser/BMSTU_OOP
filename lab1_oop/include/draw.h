#ifndef DRAW_H
#define DRAW_H

#include "draw_withQT.h"
#include "edges.h"
#include "errors.h"

errors draw_lines_with_connections(const point_arr &pa, const connections_arr &ca, const canvas &canvas);

#endif
