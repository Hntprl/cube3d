/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:39:02 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/15 09:22:23 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	ft_draw_block(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mlx->map->block_size * mlx->map->minimap_scale)
	{
		j = 0;
		while (j < mlx->map->block_size * mlx->map->minimap_scale)
		{
			put_pixel(mlx->addr, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	minimap_player(t_mlx *mlx)
{
	ft_draw_block(mlx, mlx->p->x * mlx->map->minimap_scale, mlx->p->y
		* mlx->map->minimap_scale, 16711680);
}

void	draw_map(t_mlx *mlx)
{
	t_c	c;

	c.i = 0;
	c.y = 0;
	while (c.i < mlx->map->rows && mlx->map->map[c.i])
	{
		c.j = 0;
		c.x = 0;
		while (c.j < mlx->map->columns && mlx->map->map[c.i][c.j])
		{
			if (mlx->map->map[c.i][c.j] == '0' || mlx->map->map[c.i][c.j] == 'W'
				|| mlx->map->map[c.i][c.j] == 'N'
				|| mlx->map->map[c.i][c.j] == 'S'
				|| mlx->map->map[c.i][c.j] == 'E')
				ft_draw_block(mlx, c.x, c.y, get_color(0, 0, 255));
			if (mlx->map->map[c.i][c.j] == '1')
				ft_draw_block(mlx, c.x, c.y, get_color(255, 255, 255));
			c.x += mlx->map->block_size * mlx->map->minimap_scale;
			c.j++;
		}
		c.y += mlx->map->block_size * mlx->map->minimap_scale;
		c.i++;
	}
	minimap_player(mlx);
}

void	bresenham(t_mlx *mlx, t_wall wall)
{
	t_bnham	bnham;

	bnham.dx = abs((int)(wall.x2 - wall.x));
	bnham.dy = abs((int)(wall.y2 - wall.y));
	init_br(wall, &bnham);
	bnham.error = bnham.dx - bnham.dy;
	while (wall.x != wall.x2 || wall.y != wall.y2)
	{
		put_pixel(mlx->addr, wall.x, wall.y, 14666399);
		bnham.e2 = bnham.error * 2;
		if (bnham.e2 > -bnham.dy)
		{
			bnham.error -= bnham.dy;
			wall.x += bnham.sx;
		}
		if (bnham.e2 < bnham.dx)
		{
			bnham.error += bnham.dx;
			wall.y += bnham.sy;
		}
	}
}

void	init_data(t_mlx *mlx, t_cube *cube, t_player *p, t_map *map)
{
	mlx->ptr = mlx_init();
	cube->height = map->rows * map->block_size;
	cube->width = map->columns * map->block_size;
	cube->wall_line = 1;
	p->turn_direction = 0;
	p->walk_direction = 0;
	p->rotation_angle = 0;
	p->move_speed = 5;
	p->rotation_speed = 2.5;
	p->side_walk = 0;
	p->fov = 90;
	mlx->map = map;
	mlx->cube = cube;
	mlx->p = p;
	if (mlx->map->columns > 70 || mlx->map->rows > 70)
		mlx->map->minimap_scale = 0.15;
	else
		mlx->map->minimap_scale = 0.2;
}
