/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjkim <yeonjkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:10:22 by yeonjkim          #+#    #+#             */
/*   Updated: 2022/02/09 15:10:23 by yeonjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	is_valid_map(char **map, struct map_arg *m)
{
	is_rectangle(map, m);
	is_all_valid_char(map, m->width, m->length, m);
	is_surrounded_by_wall(map, m->width, m->length);
}

int	is_valid_argv(int argc, char **argv)
{
	if (argc != 2)
	{
		return (FALSE);
	}
	if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".ber") != 0)
	{
		return (FALSE);
	}
	return (TRUE);
}
