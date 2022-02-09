#include "./so_long.h"
#include <stdio.h>

//error code end
void so_long_error(int errorcode)
{
    if (errorcode == 1)
        write(1, "[error] invalid main arguments.\n", 32);
    else if (errorcode == 2)
        write(1, "[error] file open error.\n", 26);
    else if (errorcode == 3)
        write(1, "[error] file read error.\n", 26);
    else if (errorcode == 4)
        write(1, "[error] map has invalid char.\n", 31);
    else if (errorcode == 5)
        write(1, "[error] map is not rectangle.\n", 31);
    else if (errorcode == 6)
        write(1, "[error] map must have one player.\n", 35);
    else if (errorcode == 7)
        write(1, "[error] collection must be greater than or equal to 1.\n", 56);
    else if (errorcode == 8)
        write(1, "[error] map must have exit.\n", 29);
    else if (errorcode == 9)
        write(1, "[error] map must be surrounded by wall.\n", 41);
    exit(0);
}

void is_valid_map(char **map, struct map_arg *m)
{
    is_rectangle(map, m);
    is_all_valid_char(map, m->width, m->length, m);
    is_surrounded_by_wall(map, m->width, m->length);
}

//argv error end
int is_valid_argv(int argc, char **argv)
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
//map parsing end
void map_parsing(int fd, char ***map)//이차원배열의 주소 전달
{
    char *line;//get_next_line으로 받아오는 문자열
    char *split;//나중에 split할 최종 문자열
    char *new;//temp변수
    int gnl;

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
            break;
        gnl = get_next_line(fd, &line);
    }
    if (gnl == -1)
        so_long_error(3);
    (*map) = ft_split(split, '\n');
    free(split);
}

void map_arg_first_init(struct map_arg *m)
{
    m->collect = 0;
    m->current_i = 0;
    m->current_j = 0;
    m->exit = 0;
    m->gather = 0;
    m->length = 0;
    m->width = 0;
}

int main(int argc, char **argv)
{
    int fd = 0;//파일 디스크립터
    char **map = 0;
    struct map_arg m;

    map_arg_first_init(&m);
    if (is_valid_argv(argc, argv) == FALSE)
        so_long_error(1);//invalid main arguments
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)//파일 찾지 못함
        so_long_error(2);
    map_parsing(fd, &map);
    is_valid_map(map, &m);
    show_window(&m, map);
    return (0);
}