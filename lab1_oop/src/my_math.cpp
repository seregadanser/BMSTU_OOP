#include "../include/my_math.h"

static double to_radians(const double angle)
{
    return angle * M_PI / 180.0;
}

/*static void turn_x(point &pointt, const point &center, const double &angle)
{
    double temp_y = pointt.y;
    double temp_z = pointt.z;
    pointt.y = center.y + (temp_y - center.y) * cos(to_radians(angle)) - (temp_z - center.z) * sin(to_radians(angle));
    pointt.z = center.z + (temp_y - center.y) * sin(to_radians(angle)) + (temp_z - center.z) * cos(to_radians(angle));
}

static void turn_y(point &pointt, const point &center, const double &angle)
{
    double temp_x = pointt.x;
    double temp_z = pointt.z;
    pointt.x = center.x + (temp_x - center.x) * cos(to_radians(angle)) + (temp_z - center.z) * sin(to_radians(angle));
    pointt.z = center.z - (temp_x - center.x) * sin(to_radians(angle)) + (temp_z - center.z) * cos(to_radians(angle));
}

static void turn_z(point &pointt, const point &center, const double &angle)
{
    double temp_x = pointt.x;
    double temp_y = pointt.y;
    pointt.x = center.x + (temp_x - center.x) * cos(to_radians(angle)) + (temp_y - center.y) * sin(to_radians(angle));
    pointt.y = center.y - (temp_x - center.x) * sin(to_radians(angle)) + (temp_y - center.y) * cos(to_radians(angle));
}

static void turn_point(point &pointt, const rotate &coefs)
{
    turn_x(pointt, coefs.center, coefs.angleX);
    turn_y(pointt, coefs.center, coefs.angleY);
    turn_z(pointt, coefs.center, coefs.angleZ);
}
*/

static void move_point(point &point, const movet &coefs)
{
    point.x += coefs.x;
    point.y += coefs.y;
    point.z += coefs.z;
}

static void move_to_origin(point &pointt, const point &center)
{
    movet move_to_origin;
    move_to_origin.x = -center.x;
    move_to_origin.y = -center.y;
    move_to_origin.z = -center.z;
    move_point(pointt, move_to_origin);
}

static void move_to_center(point &pointt, const point &center)
{
    movet move_to_origin;
    move_to_origin.x = center.x;
    move_to_origin.y = center.y;
    move_to_origin.z = center.z;
    move_point(pointt, move_to_origin);
}

static void RotatePointX(point &pointt, const double &angle)
{
    double temp_y = pointt.y;
    pointt.y = pointt.y * cos(to_radians(angle)) - pointt.z * sin(to_radians(angle));
    pointt.z = temp_y * sin(to_radians(angle)) + pointt.z * cos(to_radians(angle));
}

static void RotatePointY(point &pointt, const double &angle)
{
    double temp_x = pointt.x;
    pointt.x = pointt.x * cos(to_radians(angle)) + pointt.z * sin(to_radians(angle));
    pointt.z = -temp_x * sin(to_radians(angle)) + pointt.z * cos(to_radians(angle));
}

static void RotatePointZ(point &pointt, const double &angle)
{
    double temp_x = pointt.x;
    pointt.x = pointt.x * cos(to_radians(angle)) - pointt.y * sin(to_radians(angle));
    pointt.y = temp_x * sin(to_radians(angle)) + pointt.y * cos(to_radians(angle));
}

static void turn_point(point &pointt, const rotate &coefs)
{
    move_to_origin(pointt, coefs.center);

    RotatePointX(pointt, coefs.angleX);
    RotatePointY(pointt, coefs.angleY);
    RotatePointZ(pointt, coefs.angleZ);

    move_to_center(pointt, coefs.center);
}

static void scale_point(point &pointt, const point &center, const scale &coefs)
{
    pointt.x = coefs.x * pointt.x + (1 - coefs.x) * center.x;
    pointt.y = coefs.y * pointt.y + (1 - coefs.y) * center.y;
    pointt.z = coefs.z * pointt.z + (1 - coefs.z) * center.z;
}

errors scale_points(point_arr &arr, const scale &coefs)
{
    errors err = OK;
    if (arr.arr == nullptr || arr.size <= 0)
        err = INVALID_FIURE;
    else
        for (int i = 0; i < arr.size; i++)
        {
            scale_point(arr.arr[i], coefs.center, coefs);
        }
    return err;
}

errors rotate_points(point_arr &arr, const rotate &coeff)
{
    errors err = OK;
    if (arr.arr == nullptr || arr.size <= 0)
        err = INVALID_FIURE;
    else
        for (int i = 0; i < arr.size; i++)
        {
            turn_point(arr.arr[i], coeff);
        }
    return err;
}

errors move_points(point_arr &arr, const movet &coeff)
{
    errors err = OK;
    if (arr.arr == nullptr || arr.size <= 0)
        err = INVALID_FIURE;
    else
        for (int i = 0; i < arr.size; i++)
        {
            move_point(arr.arr[i], coeff);
        }
    return err;
}

