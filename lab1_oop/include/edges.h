#ifndef EDGES_H
#define EDGES_H

#include "errors.h"

typedef struct
{
    int from;
    int to;
}connections;
typedef connections* connections_arr_ptr;

typedef struct
{
    connections_arr_ptr arr;
    int size;
} connections_arr;

typedef FILE* file_ptr;

void destruct_edge_arr(connections_arr &arr);
errors fill_edge_array(connections_arr &arr, file_ptr f);
void init_edge_arr(connections_arr &arr);
errors check_edges(connections_arr &arr, int &max_len);

#endif