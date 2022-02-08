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

#define X_EVENT_KEY_PRESS		2
#define X_EVENT_KEY_release		3
#define X_EVENT_KEY_EXIT		17 //exit key code

//Mac key code example
//All the key code example other than below is described on the site linked in READEME.md
#define KEY_ESC			53
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

#include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
#include "./mlx/mlx.h"

struct draw_arg
{
    void *mlx;
    void *win;
    void *wall[5];
    void *collection[5];
    void *player[4];
    void *exit;
    void *black;
};

struct map_arg
{
    int collect;
    int gather;
    int current_i;
    int current_j;
    int width;
    int length;
    int exit;
};

struct key_arg
{
    char ***map;
    struct draw_arg *draw;
    struct map_arg *map_param;
    int imgindex;
    int current_i;
    int current_j;
    int prev_i;
    int prev_j;
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
void    ft_putchar_fd(char c, int fd);
void    ft_putnbr_fd(int n, int fd);

//gui.c
void show_window(struct map_arg *m, char **map);

#endif