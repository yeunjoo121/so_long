#include "so_long.h"
#include "./gnl/get_next_line.h"

int             ft_strcmp(const char *s1, const char *s2)
{
    int          index;
    unsigned char   *cp1;
    unsigned char   *cp2;

    cp1 = (unsigned char*)s1;
    cp2 = (unsigned char*)s2;
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

char    *ft_strjoin(char const *s1, char const *s2)
{
        size_t  sindex1;
        size_t  sindex2;
        size_t  index;
        size_t  strindex;
        char    *str;

        sindex1 = ft_strlen(s1);
        sindex2 = ft_strlen(s2);
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
        return (str);
}