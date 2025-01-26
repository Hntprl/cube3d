/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:39:02 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/26 14:47:56 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

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
	// t_wall wall;
	// float line_size;

	// line_size = 5;
	// wall.x = mlx->p->x * mlx->map->minimap_scale;
	// wall.y = mlx->p->y * mlx->map->minimap_scale;
	// wall.x2 = wall.x + cos(convert_to_radian(mlx->p->pov)) * line_size;
	// wall.y2 = wall.y + sin(convert_to_radian(mlx->p->pov)) * line_size;
	ft_draw_block(mlx, mlx->p->x * mlx->map->minimap_scale, mlx->p->y
			* mlx->map->minimap_scale, 16711680);
	// bresenham(mlx, wall);
}

void	draw_map(t_mlx *mlx)
{
	int flag;
	int			i;
	int			j;
	int			x;
	int			y;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	flag = 0;
	while (i < mlx->map->rows && mlx->map->map[i])
	{
		j = 0;
		x = 0;
		while (j < mlx->map->columns && mlx->map->map[i][j])
		{
			if (mlx->map->map[i][j] == '0' || mlx->map->map[i][j] == 'W' || mlx->map->map[i][j] == 'N'
				|| mlx->map->map[i][j] == 'S' || mlx->map->map[i][j] == 'E')
				ft_draw_block(mlx, x, y, get_color(0 ,0 ,255));
			if (mlx->map->map[i][j] == '1')
				ft_draw_block(mlx, x, y, 16777215);
			minimap_player(mlx);
			x += mlx->map->block_size * mlx->map->minimap_scale;
			j++;
		}
		y += mlx->map->block_size * mlx->map->minimap_scale;
		i++;
	}
}

void	bresenham(t_mlx *mlx, t_wall wall)
{
	t_bnham bnham;

	bnham.dx = abs(wall.x2 - mlx->p->x);
	bnham.dy = abs(wall.y2 - mlx->p->y);
	if (wall.x == wall.x2)
		bnham.sx = 0;
	else if (wall.x < wall.x2)
		bnham.sx = 1;
	else
		bnham.sx = -1;
	if (wall.y == wall.y2)
		bnham.sy = 0;
	else if (wall.y < wall.y2)
		bnham.sy = 1;
	else
		bnham.sy = -1;
	bnham.error = bnham.dx - bnham.dy;
	while (wall.x != wall.x2 || wall.y != wall.y2)
	{
		put_pixel(mlx->addr, wall.x, wall.y, 16711680);
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
	map = read_map();
	cube->height = map->rows * map->block_size;
	cube->width = map->columns * map->block_size;
	cube->wall_line = 1;
	p->turn_direction = 0;
	p->walk_direction = 0;
	p->rotation_angle = 0;
	p->move_speed = 5;
	p->rotation_speed = 3;
	p->side_walk = 0;
	p->pov = 90;
	mlx->map = map;
	mlx->cube = cube;
	mlx->p = p;
	mlx->map->minimap_scale = 0.2;
}
