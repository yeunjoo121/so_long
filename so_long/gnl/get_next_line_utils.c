#include "get_next_line.h"

size_t		ft_strlen(const char *str)
{
	size_t		index;

	index = 0;
	while (str[index] != '\0')
	{
		index++;
	}
	return (index);
}

char			*ft_strdup(const char *s1)
{
	char		*p;
	size_t		slen;
	size_t		index;

	index = 0;
	slen = ft_strlen(s1);
	if (!(p = (char*)malloc(sizeof(char) * (slen + 1))))
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

void ft_strjoin_init(char *s1, char *s2, size_t sindex1, size_t sindex2)
{
	sindex1 = ft_strlen(s1);
	sindex2 = ft_strlen(s2);
}
char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	sindex1;
	size_t	sindex2;
	size_t	index;
	size_t	strindex;
	char	*str;
	
	if (!(s1) && !(s2))
		return NULL;
	else if (!(s1))
		return (ft_strdup(s2));
	else if (!(s2))
		return (ft_strdup(s1));
	ft_strjoin_init(s1, s2, sindex1, sindex2);
	index = 0;
	strindex = 0;
	if (!(str = (char*)malloc(sizeof(char) * (sindex1 + sindex2 + 1))))
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