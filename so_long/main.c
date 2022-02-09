/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjkim <yeonjkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:49:18 by yeonjkim          #+#    #+#             */
/*   Updated: 2022/02/09 15:22:54 by yeonjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	so_long_error(int errorcode)
{
	if (errorcode == 1)
		write(1, "Error\ninvalid main arguments.\n", 31);
	else if (errorcode == 2)
		write(1, "Error\nfile open error.\n", 24);
	else if (errorcode == 3)
		write(1, "Error\nfile read error.\n", 24);
	else if (errorcode == 4)
		write(1, "Error\nmap has invalid char.\n", 29);
	else if (errorcode == 5)
		write(1, "Error\nmap is not rectangle.\n", 29);
	else if (errorcode == 6)
		write(1, "Error\nmap must have one player.\n", 33);
	else if (errorcode == 7)
		write(1, "Error\ncollection must be greater than or equal to 1.\n", 54);
	else if (errorcode == 8)
		write(1, "Error\nmap must have exit.\n", 27);
	else if (errorcode == 9)
		write(1, "Error\nmap must be surrounded by wall.\n", 39);
	exit(0);
}

void	map_parsing(int fd, char ***map)
{
	char	*line;
	char	*split;
	char	*new;
	int		gnl;

	gnl = get_next_line(fd, &line);
	split = ft_strdup("\0");
	while (gnl != -1)
	{
		new = ft_strjoin(line, "\n\0");
		free(line);
		line = new;
		new = ft_strjoin(split, line);
		free(split);
		split = new;
		free(line);
		if (gnl == 0)
			break ;
		gnl = get_next_line(fd, &line);
	}
	if (gnl == -1)
		so_long_error(3);
	(*map) = ft_split(split, '\n');
	free(split);
}

void	map_arg_first_init(struct map_arg *m)
{
	m->collect = 0;
	m->current_i = -1;
	m->current_j = -1;
	m->exit = 0;
	m->gather = 0;
	m->length = 0;
	m->width = 0;
}

int	main(int argc, char **argv)
{
	struct map_arg	m;
	int				fd;
	char			**map;

	fd = 0;
	map_arg_first_init(&m);
	if (is_valid_argv(argc, argv) == FALSE)
		so_long_error(1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		so_long_error(2);
	map_parsing(fd, &map);
	is_valid_map(map, &m);
	show_window(&m, map);
	return (0);
}
