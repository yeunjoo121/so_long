/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjkim <yeonjkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:27:44 by yeonjkim          #+#    #+#             */
/*   Updated: 2022/02/09 14:41:00 by yeonjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

size_t	ft_strlen(const char *str)
{
	size_t		index;

	index = 0;
	while (str[index] != '\0')
	{
		index++;
	}
	return (index);
}

char	*ft_strdup(const char *s1)
{
	char		*p;
	size_t		slen;
	size_t		index;

	index = 0;
	slen = ft_strlen(s1);
	p = (char *)malloc(sizeof(char) * (slen + 1));
	if (!p)
	{
		return (0);
	}
	while (index < slen)
	{
		p[index] = s1[index];
		index++;
	}
	p[index] = '\0';
	return (p);
}

void	ft_strjoin_init(char *s1, size_t *sindex1, size_t *i, size_t *stri)
{
	(*sindex1) = ft_strlen(s1);
	(*i) = 0;
	(*stri) = 0;
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	sindex1;
	size_t	sindex2;
	size_t	index;
	size_t	strindex;
	char	*str;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1))
		return (ft_strdup(s2));
	else if (!(s2))
		return (ft_strdup(s1));
	ft_strjoin_init(s1, &sindex1, &index, &strindex);
	sindex2 = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (sindex1 + sindex2 + 1));
	if (!str)
		return (NULL);
	while (index < sindex1)
		str[strindex++] = s1[index++];
	index = 0;
	while (index < sindex2)
		str[strindex++] = s2[index++];
	str[strindex] = '\0';
	free(s1);
	return (str);
}
