#include "../include/my_figure.h"

static void copy_figure(figure &to, figure &from)
{
    to = from;
}

static errors check_figure(figure &fig)
{
    int number_of_points = get_number_of_points(fig.points_arr);
    errors err = check_edges(fig.conect_arr, number_of_points);
    return err;
}

static errors load_temp_fugure(figure &temp_figure, file_ptr f)
{
    errors error = OK;
    error = fill_point_array(temp_figure.points_arr, f);

    if (error == OK)
    {
        error = fill_edge_array(temp_figure.conect_arr, f);
        if (error != OK)
        {
            destruct_my_type_arr(temp_figure.points_arr);
        }
    }
    return error;
}

errors create_figure(figure &figure1, filename_ptr filename)
{
    figure tmp_figure = init();
    file_ptr f = fopen(filename, "r");
    errors error_code = OK;

    if (f == nullptr)
        error_code = OPEN_FILE_ERR;

    if (error_code == OK)
    {
        error_code = load_temp_fugure(tmp_figure, f);
        fclose(f);
    }

    if (error_code == OK)
    {
        error_code = check_figure(tmp_figure);
        if (error_code != OK)
            destroy_figure(tmp_figure);
    }
    
    if (error_code == OK)
    {
        destroy_figure(figure1);
        copy_figure(figure1, tmp_figure);
    }

    return error_code;
}

figure init()
{
    static figure f;
    init_my_type_arr(f.points_arr);
    init_edge_arr(f.conect_arr);
    return f;
}

void destroy_figure(figure &fig)
{
    destruct_my_type_arr(fig.points_arr);
    destruct_edge_arr(fig.conect_arr);
}

errors draw_figure(const figure &my_f, const canvas &pp)
{
    clear_scene(pp);
    return draw_lines_with_connections(my_f.points_arr, my_f.conect_arr, pp);
}

errors rotate_figure(figure &fig, const rotate &coeff)
{
    return rotate_points(fig.points_arr, coeff);
}

errors move_figure(figure &fig, const movet &coeff)
{
    return move_points(fig.points_arr, coeff);
}

errors scale_figure(figure &fig, const scale &coeff)
{
    return scale_points(fig.points_arr, coeff);
}
