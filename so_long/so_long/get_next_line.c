/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjkim <yeonjkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:41:41 by yeonjkim          #+#    #+#             */
/*   Updated: 2022/02/09 14:46:45 by yeonjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	isin_newline(char *str)
{
	int		index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '\n')
		{
			return (index);
		}
		index++;
	}
	return (-1);
}

int	ft_error(char **backup)
{
	while (*backup != 0)
	{
		free(*backup);
		*backup = 0;
	}
	return (-1);
}

int	get_one_line(char **backup, char **line, int cut)
{
	char	*temp;

	(*backup)[cut] = '\0';
	*line = ft_strdup(*backup);
	if (!(*line))
	{
		return (ft_error(backup));
	}
	temp = ft_strdup(*backup + cut + 1);
	if (!temp)
	{
		return (ft_error(backup));
	}
	free(*backup);
	*backup = temp;
	return (1);
}

int	get_last(char **backup, char **line)
{
	int	cut;

	if (!(*backup))
	{
		*line = ft_strdup("");
		return (0);
	}
	else
	{
		cut = isin_newline(*backup);
		if (cut >= 0)
		{
			return (get_one_line(backup, line, cut));
		}
		*line = ft_strdup(*backup);
		if (!*line)
		{
			return (ft_error(backup));
		}
		free(*backup);
		*backup = 0;
		return (0);
	}
}

int	get_next_line(int fd, char **line)
{
	static char		*backup[OPEN_MAX];
	char			buf[BUFFER_SIZE + 1];
	int				readsize;
	int				cut;

	if ((fd < 0) || (line == 0) || (BUFFER_SIZE <= 0))
		return (-1);
	readsize = read(fd, buf, BUFFER_SIZE);
	while (readsize > 0)
	{
		buf[readsize] = '\0';
		backup[fd] = ft_strjoin_gnl(backup[fd], buf);
		cut = isin_newline(backup[fd]);
		if (cut >= 0)
			return (get_one_line(&backup[fd], line, cut));
		readsize = read(fd, buf, BUFFER_SIZE);
	}
	if (readsize < 0)
	{
		return (ft_error(&backup[fd]));
	}
	return (get_last(&backup[fd], line));
}
