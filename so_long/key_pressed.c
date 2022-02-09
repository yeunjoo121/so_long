/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjkim <yeonjkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 21:34:44 by yeonjkim          #+#    #+#             */
/*   Updated: 2022/02/09 21:34:52 by yeonjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	wkey_press(struct key_arg *key)
{
	key->prev_i = key->current_i;
	key->prev_j = key->current_j;
	key->current_i = key->current_i - 1;
	print_tile_move(key);
}

void	dkey_press(struct key_arg *key)
{
	key->prev_i = key->current_i;
	key->prev_j = key->current_j;
	key->current_j = key->current_j + 1;
	print_tile_move(key);
}

void	akey_press(struct key_arg *key)
{
	key->prev_i = key->current_i;
	key->prev_j = key->current_j;
	key->current_j = key->current_j - 1;
	print_tile_move(key);
}

void	skey_press(struct key_arg *key)
{
	key->prev_i = key->current_i;
	key->prev_j = key->current_j;
	key->current_i = key->current_i + 1;
	print_tile_move(key);
}

int	key_press(int keycode, struct key_arg *key)
{
	if (keycode == KEY_W)
		if (key->current_i - 1 >= 0
			&& (*(key->map))[key->current_i - 1][key->current_j] != '1')
			wkey_press(key);
	if (keycode == KEY_D)
		if (key->current_j + 1 <= key->map_param->width
			&& (*(key->map))[key->current_i][key->current_j + 1] != '1')
			dkey_press(key);
	if (keycode == KEY_A)
		if (key->current_j - 1 >= 0
			&& (*(key->map))[key->current_i][key->current_j - 1] != '1')
			akey_press(key);
	if (keycode == KEY_S)
		if (key->current_i + 1 <= key->map_param->length
			&& (*(key->map))[key->current_i + 1][key->current_j] != '1')
			skey_press(key);
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}
