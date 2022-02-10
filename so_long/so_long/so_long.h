/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonjkim <yeonjkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 22:15:59 by yeonjkim          #+#    #+#             */
/*   Updated: 2022/02/09 23:37:49 by yeonjkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_EXIT	17
# define KEY_ESC	53
# define KEY_Q	12
# define KEY_W	13
# define KEY_E	14
# define KEY_R	15
# define KEY_A	0
# define KEY_S	1
# define KEY_D	2

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "./mlx/mlx.h"

typedef struct s_draw_arg
{
	void	*mlx;
	void	*win;
	void	*wall[5];
	void	*collect[5];
	void	*player[4];
	void	*exit;
	void	*black;
}	t_draw_arg;

typedef struct s_map_arg
{
	int	collect;
	int	gather;
	int	current_i;
	int	current_j;
	int	width;
	int	length;
	int	exit;
}	t_map_arg;

typedef struct s_key_arg
{
	char		***map;
	t_draw_arg	*draw;
	t_map_arg	*map_param;
	int			imgindex;
	int			current_i;
	int			current_j;
	int			prev_i;
	int			prev_j;
	int			movement;
}	t_key_arg;

int			get_next_line(int fd, char **line);
size_t		ft_strlen(const char *str);
char		*ft_strdup(const char *s1);
char		*ft_strjoin_gnl(char *s1, char *s2);
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *s1, char const *s2);
int			is_valid_char(char c);
void		is_surrounded_by_wall(char **map, int width, int length);
void		map_arg_init(int i, int j, char **map, t_map_arg *m);
void		is_rectangle(char **map, t_map_arg *m);
void		is_all_valid_char(char **map, int width, int length, t_map_arg *m);
void		so_long_error(int errorcode);
void		is_valid_map(char **map, t_map_arg *m);
int			is_valid_argv(int argc, char **argv);
void		map_parsing(int fd, char ***map);
void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(int n, int fd);
void		key_arg_init(t_key_arg *key, t_map_arg *m);
int			xkey_clicked(void);
void		draw_init(t_draw_arg *d, t_map_arg *m, int *w, int *h);
void		show_window(t_map_arg *m, char **map);
void		print_tile_move(t_key_arg *key);
void		draw_current(t_key_arg *key, int act, int i, int j);
void		draw_prev(t_key_arg *key, int i, int j);
void		print_tile(t_map_arg *m, char **map, t_draw_arg draw, int index);
void		wkey_press(t_key_arg *key);
void		skey_press(t_key_arg *key);
void		akey_press(t_key_arg *key);
void		dkey_press(t_key_arg *key);
int			key_press(int keycode, t_key_arg *key);

#endif
