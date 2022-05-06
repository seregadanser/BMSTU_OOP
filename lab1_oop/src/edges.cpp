#include "../include/edges.h"

static errors check_arr(connections_arr &arr)
{
    errors err = OK;
    if (arr.arr == nullptr)
        err = MEMORY_ERROR;
    return err;
}

static errors alloc_edge_arr(connections_arr &arr)
{
    arr.arr = new connections[arr.size];
    errors err = OK;
    err = check_arr(arr);
    return err;
}

void init_edge_arr(connections_arr &arr)
{
    arr.arr = nullptr;
    arr.size = 0;
}

void destruct_edge_arr(connections_arr &arr)
{
    delete[] arr.arr;
    arr.arr = nullptr;
}

errors check_edges(connections_arr &arr, int &max_len)
{
    errors err = OK;
    err = check_arr(arr);

    for (int i = 0; err == OK && i < arr.size; i++)
    {
        connections c = arr.arr[i];
        if (c.from >= max_len || c.to >= max_len)
            err = INVALID_CONNECTION;
    }
    return err;
}

static errors read_array_edge(connections_arr &arr, file_ptr f)
{
    errors err = OK;
    for (int i = 0; err == OK && i < arr.size; i++)
    {
        if (fscanf(f, "%d %d", &arr.arr[i].from, &arr.arr[i].to) != 2)
            err = READ_FILE_ERR;
        if (arr.arr[i].from < 0 || arr.arr[i].to < 0)
            err = INVALID_CONNECTION;
    }
    return err;
}

static errors read_amount(connections_arr &arr, file_ptr f)
{
    errors err = OK;
    if (fscanf(f, "%d", &arr.size) != 1)
        err = READ_FILE_ERR;
    if (arr.size <= 0)
        err = INVALID_VALUE_SIZE;
    return err;
}

errors fill_edge_array(connections_arr &arr, file_ptr f)
{
    errors err = OK;
    err = read_amount(arr, f);
    if (err == OK)
    {
        err = alloc_edge_arr(arr);
        if (err == OK)
        {
            err = read_array_edge(arr, f);
            if (err != OK)
                destruct_edge_arr(arr);
        }
    }
    return err;
}
