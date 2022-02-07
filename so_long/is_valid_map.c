#include "./so_long.h"
#include "./gnl/get_next_line.h"

int is_valid_char(char c)
{
    if (c != '1' && c != '0' && c != 'E' && c != 'C' && c != 'P')
    {
        return (FALSE);
    }
    return (TRUE);
}

void is_surrounded_by_wall(char **map, int width, int length)
{
    int i;
    int j;

    j = 0;
    while (map[0][j])//첫번째 줄 검사
    {
        if (map[0][j] != '1')
            so_long_error(9);
        j++;
    }
    j = 0;
    while (map[length - 1][j])//마지막 줄 검사
    {
        if (map[length - 1][j] != '1')
            so_long_error(9);
        j++;
    }
    j = 0;
    i = 1;
    while (i < length - 1)//첫번째와 마지막이 1인지 확인
    {
        if (map[i][0] != '1' || map[i][width - 1] != '1')
            so_long_error(9);
        i++;
    }
}

void map_arg_init(int i, int j, char **map, struct map_arg *m, int *playerflag)
{
    if (map[i][j] == 'C')
        (m->collect)++;
    else if (map[i][j] == 'P')
    {
        if ((*playerflag) == 1)
            so_long_error(6);
        m->current_x = i;
        m->current_y = j;
        (*playerflag) = 1;
    }
    else if (map[i][j] == 'E')
    {
        (m->exit)++;
    }
}

void is_rectangle(char **map, struct map_arg *m)
{
    int x;
    int y;
    int width;

    x = 0;
    width = ft_strlen(map[x]);
    while (map[x])
    {
        y = 0;
        while(map[x][y])
        {
            y++;
        }
        if (width != y)
            so_long_error(5);
        x++;
    }
    m->width = width;
    m->length = x;
}

void is_all_valid_char(char **map, int width, int length, struct map_arg *m)
{
    int i;
    int j;
    int playerflag;

    i = 0;
    j = 0;
    playerflag = 0;
    while(i < length)
    {
        j = 0;
        while (j < width)
        {
            if (is_valid_char(map[i][j]) == FALSE)
                so_long_error(4);
            map_arg_init(i, j, map, m, &playerflag);
            j++;
        }
        i++;
    }
    if (m->collect == 0)
        so_long_error(7);
    if (m->exit == 0)
        so_long_error(8);
    if (playerflag == 0)
        so_long_error(6);
}