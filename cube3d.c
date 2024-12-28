/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:54:27 by amarouf           #+#    #+#             */
/*   Updated: 2024/12/28 14:13:26 by amarouf          ###   ########.fr       */
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

void set_player_direction(char c, t_mlx *mlx)
{
	if (c == 'N')
		mlx->p->direction = 0;
	if (c == 'S')
		mlx->p->direction = 180;
	if (c == 'E')
		mlx->p->direction = 90;
	if (c == 'W')
		mlx->p->direction = 270;
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
			if (mlx->map->map[i][j] == 'N' || mlx->map->map[i][j] == 'S' || mlx->map->map[i][j] == 'E' || mlx->map->map[i][j] == 'W')
			{
				if (flag == 0)
				{
					mlx->p->x = x;
					mlx->p->y = y;
					flag = 1;
				}
				// set_player_direction(mlx->map->map[i][j], mlx);c
				ft_draw_block(mlx, mlx->p->x, mlx->p->y, 3093247);
			}
			x += mlx->map->block_size;
			j ++;
		}
		y += mlx->map->block_size;
		i ++;
	}
}
// x20 y12
void bresenham(t_mlx *mlx, int x, int y, int x2, int y2)
{
	int e2;
	int dx = abs(x2 - mlx->p->x);
	int dy = abs(y2 - mlx->p->y);
	int error;
	int sx;
	int sy;
	
	if (mlx->p->x < x2)
		sx = 1;
	else
		sx = -1;

	if (mlx->p->y < y2)
		sy = 1;
	else
		sy = -1;
	error = dx - dy;
	while (x != x2 || y != y2)
	{
		put_pixel(mlx->addr, x, y, 16711680);
		e2 = error * 2;
		if (e2 > -dy)
		{
			error -= dy;
			x += sx;
		}
		if (e2 < dx)
		{
			error += dx;
			y += sy;
		}
	}
}

void draw_grid(t_mlx *mlx)
{
	int i = 0;
	int x = 0;
	int y = 0;
	int x2 = mlx->cube->width;
	int y2 = mlx->cube->height;

	while (i < mlx->map->rows)
	{
		x = 0;
		y += mlx->map->block_size;
		while (x < x2)
		{
			put_pixel(mlx->addr, x, y, 16711680);
			x ++;
		}
		i ++;
	}
	i = 0;
	while (i < mlx->map->columns)
	{
		y = 0;
		x += mlx->map->block_size;
		while (y < y2)
		{
			put_pixel(mlx->addr, x, y, 16711680);
			y ++;
		}
		i ++;
	}
}

void	draw_lines(t_mlx *mlx, int x, int y)
{
	int pov = 90 / 2;
	float adj = 100;
	float hyp = adj / sin(convert_to_radian(pov));
	float opp = adj * tan(convert_to_radian(pov));
	bresenham(mlx, x, y, x, y - adj);
	bresenham(mlx, x, y, x - opp, y - hyp);
	bresenham(mlx, x, y, x + opp, y - hyp);
}


int	ft_cube(void *param)
{
	t_mlx *mlx = (t_mlx *)param;
	
	mlx->image =  mlx_new_image(mlx->ptr, mlx->cube->width, mlx->cube->height);
	mlx->addr->pixels = mlx_get_data_addr(mlx->image, &mlx->addr->bits_per_pixel
	, &mlx->addr->size_line, &mlx->addr->endian); 
	draw_map(mlx);
	// draw_grid(mlx);
	draw_lines(mlx, mlx->p->x, mlx->p->y);
	ft_draw_block(mlx, mlx->p->x, mlx->p->y, 3093247);
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
	t_player p;
	t_mlx mlx;
	t_addr addr;
	t_map *map;
	
	mlx.addr = &addr;
	mlx.p = &p;
	p.rotation_angle = 90;
	// addr.p = &p;
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