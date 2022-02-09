/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjkim <yeonjkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:10:11 by yeonjkim          #+#    #+#             */
/*   Updated: 2022/02/09 15:10:12 by yeonjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int				index;
	unsigned char	*cp1;
	unsigned char	*cp2;

	cp1 = (unsigned char *)s1;
	cp2 = (unsigned char *)s2;
	index = 0;
	while (cp1[index] != '\0')
	{
		if (cp1[index] != cp2[index])
		{
			return (cp1[index] - cp2[index]);
		}
		index++;
	}
	if (cp1[index] == '\0')
	{
		return (cp1[index] - cp2[index]);
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	sindex1;
	size_t	sindex2;
	size_t	index;
	size_t	strindex;
	char	*str;

	sindex1 = ft_strlen(s1);
	sindex2 = ft_strlen(s2);
	index = 0;
	strindex = 0;
	str = (char *)malloc(sizeof(char) * (sindex1 + sindex2 + 1));
	if (!str)
		return (NULL);
	while (index < sindex1)
		str[strindex++] = s1[index++];
	index = 0;
	while (index < sindex2)
		str[strindex++] = s2[index++];
	str[strindex] = '\0';
	return (str);
}

void	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return ;
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-n, fd);
	}
	else if (n < 10 && n >= 0)
	{
		ft_putchar_fd(n + '0', fd);
	}
	else if (n > 0)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}
