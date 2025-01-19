/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:39:02 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/07 17:08:54 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_draw_block(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mlx->map->block_size / 4)
	{
		j = 0;
		while (j < mlx->map->block_size / 4)
		{
			put_pixel(mlx->addr, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_mlx *mlx)
{
	static int	flag;
	int			i;
	int			j;
	int			x;
	int			y;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
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
			if (mlx->map->map[i][j] == 'N' || mlx->map->map[i][j] == 'S'
				|| mlx->map->map[i][j] == 'E' || mlx->map->map[i][j] == 'W')
			{
				if (flag == 0)
				{
					mlx->p->x = x;
					mlx->p->y = y;
					flag = 1;
					set_player_direction(mlx->map->map[i][j], mlx);
				}
				ft_draw_block(mlx, mlx->p->x, mlx->p->y, 3093247);
			}
			x += mlx->map->block_size / 4;
			j++;
		}
		y += mlx->map->block_size / 4;
		i++;
	}
}

void	bresenham(t_mlx *mlx, int x, int y, int x2, int y2)
{
	int	e2;
	int	dx;
	int	dy;
	int	error;
	int	sx;
	int	sy;

	dx = abs(x2 - mlx->p->x);
	dy = abs(y2 - mlx->p->y);
	if (x == x)
		sx = 0;
	else if (x < x2)
		sx = 1;
	else
		sx = -1;
	if (y == y2)
		sy = 0;
	else if (y < y2)
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

void	init_data(t_mlx *mlx, t_cube *cube, t_player *p, t_map *map)
{
	mlx->ptr = mlx_init();
	map = read_map();
	cube->height = map->rows * map->block_size;
	cube->width = map->columns * map->block_size;
	cube->wall_line = 1;
	p->turn_direction = 0;
	p->walk_direction = 0;
	p->rotation_angle = 0;
	p->move_speed = 10;
	p->rotation_speed = 5;
	p->side_walk = 0;
	p->pov = 90;
	mlx->map = map;
	mlx->cube = cube;
	mlx->p = p;
}
