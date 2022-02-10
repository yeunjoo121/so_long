/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjkim <yeonjkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:41:06 by yeonjkim          #+#    #+#             */
/*   Updated: 2022/02/09 23:33:41 by yeonjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_tile(t_map_arg *m, char **map, t_draw_arg draw, int ind)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->length)
	{
		j = 0;
		while (j < m->width)
		{
			if (map[i][j] == '1')
				mlx_put_image_to_window(draw.mlx, draw.win,
					draw.wall[ind], j * 32, i * 32);
			else if (map[i][j] == 'P')
				mlx_put_image_to_window(draw.mlx, draw.win,
					draw.player[1], j * 32, i * 32);
			else if (map[i][j] == 'C')
				mlx_put_image_to_window(draw.mlx, draw.win,
					draw.collect[ind], j * 32, i * 32);
			else if (map[i][j] == 'E')
				mlx_put_image_to_window(draw.mlx, draw.win,
					draw.exit, j * 32, i * 32);
			j++;
		}
		i++;
	}
}

void	draw_prev(t_key_arg *key, int i, int j)
{
	void	*mlx;
	void	*win;

	mlx = key->draw->mlx;
	win = key->draw->win;
	if ((*(key->map))[i][j] == 'E')
	{
		mlx_put_image_to_window(key->draw->mlx, key->draw->win,
			key->draw->exit, j * 32, i * 32);
	}
	else if ((*(key->map))[i][j] == '0')
	{
		mlx_put_image_to_window(key->draw->mlx, key->draw->win,
			key->draw->black, j * 32, i * 32);
	}
}

void	draw_current(t_key_arg *key, int act, int i, int j)
{
	if ((*(key->map))[i][j] == 'C')
	{
		key->map_param->gather++;
		write(1, "collect : ", 11);
		ft_putnbr_fd(key->map_param->gather, 1);
		write(1, "\n", 2);
		(*(key->map))[i][j] = '0';
		mlx_put_image_to_window(key->draw->mlx, key->draw->win,
			key->draw->black, j * 32, i * 32);
		mlx_put_image_to_window(key->draw->mlx, key->draw->win,
			key->draw->player[act], j * 32, i * 32);
	}
	else if ((*(key->map))[i][j] == 'E')
	{
		if (key->map_param->gather == key->map_param->collect)
			exit(0);
		else
			mlx_put_image_to_window(key->draw->mlx, key->draw->win,
				key->draw->player[act], j * 32, i * 32);
	}
	else
		mlx_put_image_to_window(key->draw->mlx, key->draw->win,
			key->draw->player[act], j * 32, i * 32);
}

void	print_tile_move(t_key_arg *key)
{
	if (key->current_i > key->prev_i)
	{
		draw_prev(key, key->prev_i, key->prev_j);
		draw_current(key, 2, key->current_i, key->current_j);
	}
	else if (key->current_i < key->prev_i)
	{
		draw_prev(key, key->prev_i, key->prev_j);
		draw_current(key, 3, key->current_i, key->current_j);
	}
	else if (key->current_j > key->prev_j)
	{
		draw_prev(key, key->prev_i, key->prev_j);
		draw_current(key, 1, key->current_i, key->current_j);
	}
	else if (key->current_j < key->prev_j)
	{
		draw_prev(key, key->prev_i, key->prev_j);
		draw_current(key, 0, key->current_i, key->current_j);
	}
}
