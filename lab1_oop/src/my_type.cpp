#include "../include/my_type.h"

point new_point(double x, double y, double z)
{
    point p;
    p.x = x;
    p.y = y;
    p.z = z;
    return p;
}

static errors alloc_my_type_arr(point_arr &arr)
{
    arr.arr = new point[arr.size];
    errors err = OK;
    if (arr.arr == nullptr)
        err = MEMORY_ERROR;
    return err;
}

void init_my_type_arr(point_arr &arr)
{
    arr.arr = nullptr;
    arr.size = 0;
}

void destruct_my_type_arr(point_arr &arr)
{
    delete[] arr.arr;
    arr.arr = nullptr;
}

static errors read_array_points(point_arr &arr, file_ptr f)
{
    errors err = OK;
    point p;
    for (int i = 0; err == OK && i < arr.size; i++)
    {
        if (fscanf(f, "%lf %lf %lf", &p.x, &p.y, &p.z) != 3)
            err = READ_FILE_ERR;
        arr.arr[i] = p;
    }
    return err;
}

static errors read_amount(point_arr &arr, file_ptr f)
{
    errors err = OK;
    if (fscanf(f, "%d", &arr.size) != 1)
        err = READ_FILE_ERR;
    if (arr.size <= 0)
        err = INVALID_VALUE_SIZE;
    return err;
}

errors fill_point_array(point_arr &arr, file_ptr f)
{
    errors err = OK;
    err = read_amount(arr, f);
    if (err == OK)
    {
        err = alloc_my_type_arr(arr);
        if (err == OK)
        {
            err = read_array_points(arr, f);
            if (err != OK)
                destruct_my_type_arr(arr);
        }
    }
    return err;
}

int get_number_of_points(point_arr &arr)
{
    return arr.size;
}
