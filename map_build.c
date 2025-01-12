/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:39:02 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/06 13:17:59 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_draw_block(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mlx->map->block_size)
	{
		j = 0;
		while (j < mlx->map->block_size)
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
			x += mlx->map->block_size;
			j++;
		}
		y += mlx->map->block_size;
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
