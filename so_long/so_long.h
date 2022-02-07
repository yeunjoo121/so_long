#ifndef SO_LONG_H
# define SO_LONG_H

# define TRUE   1
# define FALSE  0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 32
# endif

#include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include "./mlx/mlx.h"

struct map_arg
{
    int collect;
    int gather;
    int current_x;
    int current_y;
    int width;
    int length;
    int exit;
};

struct draw_arg
{
    void *mlx;
    void *win;
    void *wall;
    void *collection;
    void *player;
    void *exit;
};

int     get_next_line(int fd, char **line);

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_strjoin_gnl(char *s1, char *s2);
int     ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
char    *ft_strjoin(char const *s1, char const *s2);
int is_valid_char(char c);
void is_surrounded_by_wall(char **map, int width, int length);
void map_arg_init(int i, int j, char **map, struct map_arg *m, int *playerflag);
void is_rectangle(char **map, struct map_arg *m);
void is_all_valid_char(char **map, int width, int length, struct map_arg *m);
void so_long_error(int errorcode);
void is_valid_map(char **map, struct map_arg *m);
int is_valid_argv(int argc, char **argv);
void map_parsing(int fd, char ***map);

//gui.c
void show_window(struct map_arg *m, char **map);

#endif