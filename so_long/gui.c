#include "so_long.h"
#include <stdio.h>

void print_tile(struct map_arg *m, char **map, struct draw_arg draw)
{
    int i = 0;
    int j = 0;
    while (i < m->length)
    {
        j = 0;
        while (j < m->width)
        {
            if (map[i][j] == '1')//벽
                mlx_put_image_to_window(draw.mlx, draw.win, draw.wall, j * 32, i * 32);//가로 세로 순서
            else if (map[i][j] == 'P')//플레이어
                mlx_put_image_to_window(draw.mlx, draw.win, draw.player, j * 32, i * 32);//가로 세로 순서
            else if (map[i][j] == 'C')//수집품
                mlx_put_image_to_window(draw.mlx, draw.win, draw.collection, j * 32, i * 32);//가로 세로 순서
            else if (map[i][j] == 'E')//출구
                mlx_put_image_to_window(draw.mlx, draw.win, draw.exit, j * 32, i * 32);//가로 세로 순서
            j++;
        }
        i++;
    }
}

void show_window(struct map_arg *m, char **map)
{
    struct draw_arg draw;
    int		img_width;
    int 	img_height;

    draw.mlx = mlx_init();
    draw.win = mlx_new_window(draw.mlx, 32 * (m->width), 32 * (m->length), "Bubble Bubble");
    draw.wall = mlx_xpm_file_to_image(draw.mlx, "./sprite/wall1.xpm", &img_width, &img_height);
    draw.collection = mlx_xpm_file_to_image(draw.mlx, "./sprite/strawberry.xpm", &img_width, &img_height);
    draw.player = mlx_xpm_file_to_image(draw.mlx, "./sprite/left.xpm", &img_width, &img_height);
    draw.exit = mlx_xpm_file_to_image(draw.mlx, "./sprite/door.xpm", &img_width, &img_height);
    print_tile(m, map, draw);
    mlx_loop(draw.mlx);
}