/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:35:31 by amarouf           #+#    #+#             */
/*   Updated: 2024/12/30 18:41:19 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_grid(t_mlx *mlx)
{
	int	i;
	int	x;
	int	y;
	int	x2;
	int	y2;

	i = 0;
	x = 0;
	y = 0;
	x2 = mlx->cube->width;
	y2 = mlx->cube->height;
	while (i < mlx->map->rows)
	{
		x = 0;
		y += mlx->map->block_size;
		while (x < x2)
		{
			put_pixel(mlx->addr, x, y, 16777215);
			x++;
		}
		i++;
	}
	i = 0;
	while (i < mlx->map->columns)
	{
		y = 0;
		x += mlx->map->block_size;
		while (y < y2)
		{
			put_pixel(mlx->addr, x, y, 16777215);
			y++;
		}
		i++;
	}
}

void	draw_lines(t_mlx *mlx, int x, int y)
{
	float	adj;
	float	opp;

	adj = 100 * cos(convert_to_radian(mlx->p->rotation_angle));
	opp = 100 * sin(convert_to_radian(mlx->p->rotation_angle));
	bresenham(mlx, x, y, x + adj, y + opp);
}
