/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjkim <yeonjkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:10:31 by yeonjkim          #+#    #+#             */
/*   Updated: 2022/02/09 23:35:59 by yeonjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	key_arg_init(t_key_arg *key, t_map_arg *m)
{
	key->current_i = m->current_i;
	key->current_j = m->current_j;
	key->prev_i = m->current_i;
	key->prev_j = m->current_j;
}

int	xkey_clicked(void)
{
	exit(0);
	return (0);
}

void	draw_init(t_draw_arg *d, t_map_arg *m, int *w, int *h)
{
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx,
			32 * (m->width), 32 * (m->length), "Bubble Bubble");
	d->wall[0] = mlx_xpm_file_to_image(d->mlx, "./sprite/wall1.xpm", w, h);
	d->wall[1] = mlx_xpm_file_to_image(d->mlx, "./sprite/wall2.xpm", w, h);
	d->wall[2] = mlx_xpm_file_to_image(d->mlx, "./sprite/wall3.xpm", w, h);
	d->wall[3] = mlx_xpm_file_to_image(d->mlx, "./sprite/wall4.xpm", w, h);
	d->wall[4] = mlx_xpm_file_to_image(d->mlx, "./sprite/wall5.xpm", w, h);
	d->collect[0] = mlx_xpm_file_to_image(d->mlx,
			"./sprite/strawberry.xpm", w, h);
	d->collect[1] = mlx_xpm_file_to_image(d->mlx, "./sprite/banana.xpm", w, h);
	d->collect[2] = mlx_xpm_file_to_image(d->mlx,
			"./sprite/watermelon.xpm", w, h);
	d->collect[3] = mlx_xpm_file_to_image(d->mlx, "./sprite/cake.xpm", w, h);
	d->collect[4] = mlx_xpm_file_to_image(d->mlx, "./sprite/cherry.xpm", w, h);
	d->player[0] = mlx_xpm_file_to_image(d->mlx, "./sprite/left.xpm", w, h);
	d->player[1] = mlx_xpm_file_to_image(d->mlx, "./sprite/right.xpm", w, h);
	d->player[2] = mlx_xpm_file_to_image(d->mlx, "./sprite/down.xpm", w, h);
	d->player[3] = mlx_xpm_file_to_image(d->mlx, "./sprite/up.xpm", w, h);
	d->exit = mlx_xpm_file_to_image(d->mlx, "./sprite/door.xpm", w, h);
	d->black = mlx_xpm_file_to_image(d->mlx, "./sprite/black.xpm", w, h);
}

void	show_window(t_map_arg *m, char **map)
{
	t_key_arg	key_param;
	t_draw_arg	draw;
	int			img_width;
	int			img_height;

	key_arg_init(&key_param, m);
	draw_init(&draw, m, &img_width, &img_height);
	key_param.draw = &draw;
	key_param.imgindex = (m->length + m->width) % 4;
	key_param.map = &map;
	key_param.map_param = m;
	key_param.movement = 0;
	print_tile(m, map, draw, key_param.imgindex);
	(*key_param.map)[key_param.current_i][key_param.current_j] = '0';
	mlx_hook(draw.win, X_EVENT_KEY_PRESS, 0, &key_press, &key_param);
	mlx_hook(draw.win, X_EVENT_KEY_EXIT, 0, &xkey_clicked, 0);
	mlx_loop(draw.mlx);
}
