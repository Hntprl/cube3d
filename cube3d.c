/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:54:27 by amarouf           #+#    #+#             */
/*   Updated: 2024/12/23 17:07:33 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void ft_draw_block(t_mlx *mlx, int x, int y, int color)
{
	int i = 0;
	int j = 0;
	while (i < mlx->map->block_size)
	{
		j = 0;
		while (j < mlx->map->block_size)
		{
			put_pixel(mlx->addr, x + i, y + j, color);
			j ++;
		}
		i ++;
	}
}	

void draw_map(t_mlx *mlx)
{
	static int flag;
	int i = 0;
	int j = 0;
	int x = 0;
	int y = 0;
	while (i < mlx->map->rows && mlx->map->map[i])
	{
		j = 0;
		x = 0;
		while (j < mlx->map->columns && mlx->map->map[i][j])
		{
			if (mlx->map->map[i][j] == '1')
				ft_draw_block(mlx, x, y, 16777215);
			if (mlx->map->map[i][j] == '0')
				ft_draw_block(mlx, x, y, 0);
			if (mlx->map->map[i][j] == 'P')
			{
				if (flag == 0)
				{
					mlx->addr->p->x = x;
					mlx->addr->p->y = y;
					flag = 1;
				}
				ft_draw_block(mlx, mlx->addr->p->x, mlx->addr->p->y, 16711680);
			}
			x += mlx->map->block_size;
			j ++;
		}
		y += mlx->map->block_size;
		i ++;
	}
}

int ft_cube(void *param)
{
	t_mlx *mlx = (t_mlx *)param;
	
	mlx->image =  mlx_new_image(mlx->ptr, mlx->cube->width, mlx->cube->height);
	mlx->addr->pixels = mlx_get_data_addr(mlx->image, &mlx->addr->bits_per_pixel
	, &mlx->addr->size_line, &mlx->addr->endian);
	draw_map(mlx);
	ft_draw_block(mlx, mlx->addr->p->x, mlx->addr->p->y, 16711680);
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image, 0, 0);
	mlx_destroy_image ( mlx->ptr, mlx->image );
	return (0);
}

t_map *read_map(void)
{
	int fd = open("maps/mapp.cub", O_RDONLY, 0777);
	int i = 0;
	t_map *map = malloc(sizeof(t_map));
	map->rows = 12;
	map->block_size = 40;
	map->columns = 58;
	map->map = malloc(sizeof(char *) * map->rows);
	while (i < map->rows)
	{
		map->map[i] = get_next_line(fd);
		i ++;
	}
	return (map);
}

int main ()
{
	t_cube cube;
	t_p p;
	t_mlx mlx;
	t_addr addr;
	t_map *map;
	
	mlx.addr = &addr;
	addr.p = &p;
	p.rotation_angle = 0;
	map = read_map();
	cube.height = map->rows * map->block_size;
	cube.width = map->columns * map->block_size;
	mlx.map = map;
	mlx.cube = &cube;
	mlx.ptr = mlx_init();
	mlx.window =  mlx_new_window(mlx.ptr, cube.width, cube.height, "Map");
	ft_cube(&mlx);
	event_handling(&mlx);
}