#include "so_long.h"
#include <stdio.h>

void key_arg_init(struct key_arg *key_param, struct map_arg *m)
{
    key_param->current_i = m->current_i;
    key_param->current_j = m->current_j;
    key_param->prev_i = m->current_i;
    key_param->prev_j = m->current_j;
}

void print_tile(struct map_arg *m, char **map, struct draw_arg draw, int imgindex)
{
    int i = 0;
    int j = 0;
    while (i < m->length)
    {
        j = 0;
        while (j < m->width)
        {
            if (map[i][j] == '1')//벽
                mlx_put_image_to_window(draw.mlx, draw.win, draw.wall[imgindex], j * 32, i * 32);//가로 세로 순서
            else if (map[i][j] == 'P')//플레이어
                mlx_put_image_to_window(draw.mlx, draw.win, draw.player[1], j * 32, i * 32);//가로 세로 순서
            else if (map[i][j] == 'C')//수집품
                mlx_put_image_to_window(draw.mlx, draw.win, draw.collection[imgindex], j * 32, i * 32);//가로 세로 순서
            else if (map[i][j] == 'E')//출구
                mlx_put_image_to_window(draw.mlx, draw.win, draw.exit, j * 32, i * 32);//가로 세로 순서
            j++;
        }
        i++;
    }
}

void draw_prev(struct key_arg *key_param)
{
    if ((*(key_param->map))[key_param->prev_i][key_param->prev_j] == 'E')
    {
        mlx_put_image_to_window(key_param->draw->mlx, key_param->draw->win, key_param->draw->exit, key_param->prev_j * 32, key_param->prev_i * 32);
    }
    else if ((*(key_param->map))[key_param->prev_i][key_param->prev_j] == '0')
    {
        mlx_put_image_to_window(key_param->draw->mlx, key_param->draw->win, key_param->draw->black, key_param->prev_j * 32, key_param->prev_i * 32);
    }
}

void draw_current(struct key_arg *key_param, int act)
{
    if ((*(key_param->map))[key_param->current_i][key_param->current_j] == 'C')
    {
        key_param->map_param->gather++;
        (*(key_param->map))[key_param->current_i][key_param->current_j] = '0';
        mlx_put_image_to_window(key_param->draw->mlx, key_param->draw->win, key_param->draw->black, key_param->current_j * 32, key_param->current_i * 32);
        mlx_put_image_to_window(key_param->draw->mlx, key_param->draw->win, key_param->draw->player[act], key_param->current_j * 32, key_param->current_i * 32);
    }
    else if ((*(key_param->map))[key_param->current_i][key_param->current_j] == 'E')
    {
        if (key_param->map_param->gather == key_param->map_param->collect)//다 모았으면
        {
            exit(0);
        }
        else
        {
            mlx_put_image_to_window(key_param->draw->mlx, key_param->draw->win, key_param->draw->player[act], key_param->current_j * 32, key_param->current_i * 32);
        }
    }
    else//'0'일 때
    {
        mlx_put_image_to_window(key_param->draw->mlx, key_param->draw->win, key_param->draw->player[act], key_param->current_j * 32, key_param->current_i * 32);
    }
}

void print_tile_move(struct key_arg *key_param)
{
    if (key_param->current_i > key_param->prev_i)//s
    {
        draw_prev(key_param);
        draw_current(key_param, 2);
    }
    else if (key_param->current_i < key_param->prev_i)//w
    {
        draw_prev(key_param);
        draw_current(key_param, 3);
    }
    else if (key_param->current_j > key_param->prev_j)//d
    {
        draw_prev(key_param);
        draw_current(key_param, 1);
    }
    else if (key_param->current_j < key_param->prev_j)//a
    {
        draw_prev(key_param);
        draw_current(key_param, 0);
    }
}

int key_press(int keycode, struct key_arg *key_param)
{
    if (keycode == KEY_W)
    {
        if (key_param->current_i - 1 >= 0 && (*(key_param->map))[key_param->current_i - 1][key_param->current_j] != '1')
        {
            key_param->prev_i = key_param->current_i;
            key_param->prev_j = key_param->current_j;
            key_param->current_i = key_param->current_i - 1;
            print_tile_move(key_param);
        }
    }
    if (keycode == KEY_D)
    {
        if (key_param->current_j + 1 <= key_param->map_param->width && (*(key_param->map))[key_param->current_i][key_param->current_j + 1] != '1')
        {
            key_param->prev_i = key_param->current_i;
            key_param->prev_j = key_param->current_j;
            key_param->current_j = key_param->current_j + 1;
            print_tile_move(key_param);
        }
    }
    if (keycode == KEY_A)
    {
        if (key_param->current_j - 1 >= 0 && (*(key_param->map))[key_param->current_i][key_param->current_j - 1] != '1')
        {
            key_param->prev_i = key_param->current_i;
            key_param->prev_j = key_param->current_j;
            key_param->current_j = key_param->current_j - 1;
            print_tile_move(key_param);
        }
    }
    if (keycode == KEY_S)
    {
        if (key_param->current_i + 1 <= key_param->map_param->length && (*(key_param->map))[key_param->current_i + 1][key_param->current_j] != '1')
        {
            key_param->prev_i = key_param->current_i;
            key_param->prev_j = key_param->current_j;
            key_param->current_i = key_param->current_i + 1;
            print_tile_move(key_param);
        }
    }
    else if (keycode == KEY_ESC)
        exit(0);
    return (0);
}

void show_window(struct map_arg *m, char **map)
{
    struct key_arg key_param;
    struct draw_arg draw;
    int		img_width;
    int 	img_height;

    key_arg_init(&key_param, m);
    draw.mlx = mlx_init();
    draw.win = mlx_new_window(draw.mlx, 32 * (m->width), 32 * (m->length), "Bubble Bubble");
    draw.wall[0] = mlx_xpm_file_to_image(draw.mlx, "./sprite/wall1.xpm", &img_width, &img_height);
    draw.wall[1] = mlx_xpm_file_to_image(draw.mlx, "./sprite/wall2.xpm", &img_width, &img_height);
    draw.collection[0] = mlx_xpm_file_to_image(draw.mlx, "./sprite/strawberry.xpm", &img_width, &img_height);
    draw.collection[1] = mlx_xpm_file_to_image(draw.mlx, "./sprite/banana.xpm", &img_width, &img_height);
    draw.player[0] = mlx_xpm_file_to_image(draw.mlx, "./sprite/left.xpm", &img_width, &img_height);
    draw.player[1] = mlx_xpm_file_to_image(draw.mlx, "./sprite/right.xpm", &img_width, &img_height);
    draw.player[2] = mlx_xpm_file_to_image(draw.mlx, "./sprite/down.xpm", &img_width, &img_height);
    draw.player[3] = mlx_xpm_file_to_image(draw.mlx, "./sprite/up.xpm", &img_width, &img_height);
    draw.exit = mlx_xpm_file_to_image(draw.mlx, "./sprite/door.xpm", &img_width, &img_height);
    draw.black = mlx_xpm_file_to_image(draw.mlx, "./sprite/black.xpm", &img_width, &img_height);
    key_param.draw = &draw;
    key_param.imgindex = (m->length + m->width) % 2;
    key_param.map = &map;
    key_param.map_param = m;
    print_tile(m, map, draw, key_param.imgindex);
    (*key_param.map)[key_param.current_i][key_param.current_j] = '0';
    mlx_hook(draw.win, X_EVENT_KEY_PRESS, 0, &key_press, &key_param);
    mlx_loop(draw.mlx);
}