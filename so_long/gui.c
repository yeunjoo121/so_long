/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjkim <yeonjkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:10:31 by yeonjkim          #+#    #+#             */
/*   Updated: 2022/02/09 21:09:09 by yeonjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void key_arg_init(struct key_arg *key, struct map_arg *m)
{
    key->current_i = m->current_i;
    key->current_j = m->current_j;
    key->prev_i = m->current_i;
    key->prev_j = m->current_j;
}

void print_tile(struct map_arg *m, char **map, struct draw_arg draw, int index)
{
    int i;
    int j;

    i = 0;
    while (i < m->length)
    {
        j = 0;
        while (j < m->width)
        {
            if (map[i][j] == '1')
                mlx_put_image_to_window(draw.mlx, draw.win, draw.wall[index], j * 32, i * 32);//가로 세로 순서
            else if (map[i][j] == 'P')
                mlx_put_image_to_window(draw.mlx, draw.win, draw.player[1], j * 32, i * 32);//가로 세로 순서
            else if (map[i][j] == 'C')
                mlx_put_image_to_window(draw.mlx, draw.win, draw.collection[index], j * 32, i * 32);//가로 세로 순서
            else if (map[i][j] == 'E')
                mlx_put_image_to_window(draw.mlx, draw.win, draw.exit, j * 32, i * 32);//가로 세로 순서
            j++;
        }
        i++;
    }
}

void draw_prev(struct key_arg *key)
{
    void *mlx = key->draw->mlx;
    void *win = key->draw->win;
    
    if ((*(key->map))[key->prev_i][key->prev_j] == 'E')
    {
        mlx_put_image_to_window(key->draw->mlx, key->draw->win, 
        key->draw->exit, key->prev_j * 32, key->prev_i * 32);
    }
    else if ((*(key->map))[key->prev_i][key->prev_j] == '0')
    {
        mlx_put_image_to_window(key->draw->mlx, key->draw->win, 
        key->draw->black, key->prev_j * 32, key->prev_i * 32);
    }
}

void draw_current(struct key_arg *key, int act)
{
    if ((*(key->map))[key->current_i][key->current_j] == 'C')
    {
        key->map_param->gather++;
        write(1, "collect : ", 11);
        ft_putnbr_fd(key->map_param->gather, 1);
        write(1, "\n", 2);
        (*(key->map))[key->current_i][key->current_j] = '0';
        mlx_put_image_to_window(key->draw->mlx, key->draw->win, 
        key->draw->black, key->current_j * 32, key->current_i * 32);
        mlx_put_image_to_window(key->draw->mlx, key->draw->win, 
        key->draw->player[act], key->current_j * 32, key->current_i * 32);
    }
    else if ((*(key->map))[key->current_i][key->current_j] == 'E')
    {
        if (key->map_param->gather == key->map_param->collect)//다 모았으면
            exit(0);
        else
            mlx_put_image_to_window(key->draw->mlx, key->draw->win, 
            key->draw->player[act], key->current_j * 32, key->current_i * 32);
    }
    else
        mlx_put_image_to_window(key->draw->mlx, key->draw->win, 
        key->draw->player[act], key->current_j * 32, key->current_i * 32);
}

void print_tile_move(struct key_arg *key)
{
    if (key->current_i > key->prev_i)//s
    {
        draw_prev(key);
        draw_current(key, 2);
    }
    else if (key->current_i < key->prev_i)//w
    {
        draw_prev(key);
        draw_current(key, 3);
    }
    else if (key->current_j > key->prev_j)//d
    {
        draw_prev(key);
        draw_current(key, 1);
    }
    else if (key->current_j < key->prev_j)//a
    {
        draw_prev(key);
        draw_current(key, 0);
    }
}

int key_press(int keycode, struct key_arg *key)
{
    if (keycode == KEY_W)
    {
        if (key->current_i - 1 >= 0 && (*(key->map))[key->current_i - 1][key->current_j] != '1')
        {
            key->prev_i = key->current_i;
            key->prev_j = key->current_j;
            key->current_i = key->current_i - 1;
            print_tile_move(key);
        }
    }
    if (keycode == KEY_D)
    {
        if (key->current_j + 1 <= key->map_param->width && (*(key->map))[key->current_i][key->current_j + 1] != '1')
        {
            key->prev_i = key->current_i;
            key->prev_j = key->current_j;
            key->current_j = key->current_j + 1;
            print_tile_move(key);
        }
    }
    if (keycode == KEY_A)
    {
        if (key->current_j - 1 >= 0 && (*(key->map))[key->current_i][key->current_j - 1] != '1')
        {
            key->prev_i = key->current_i;
            key->prev_j = key->current_j;
            key->current_j = key->current_j - 1;
            print_tile_move(key);
        }
    }
    if (keycode == KEY_S)
    {
        if (key->current_i + 1 <= key->map_param->length && (*(key->map))[key->current_i + 1][key->current_j] != '1')
        {
            key->prev_i = key->current_i;
            key->prev_j = key->current_j;
            key->current_i = key->current_i + 1;
            print_tile_move(key);
        }
    }
    else if (keycode == KEY_ESC)
        exit(0);
    return (0);
}

int xkey_clicked()
{
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
    mlx_hook(draw.win, X_EVENT_KEY_EXIT, 0, &xkey_clicked, 0);
    mlx_loop(draw.mlx);
}