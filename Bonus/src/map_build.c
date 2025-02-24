/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:39:02 by amarouf           #+#    #+#             */
<<<<<<< HEAD:Bonus/src/map_build.c
/*   Updated: 2025/02/24 14:38:43 by amarouf          ###   ########.fr       */
=======
/*   Updated: 2025/02/22 11:56:58 by bbenjrai         ###   ########.fr       */
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3:src/map_build.c
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

void	ft_draw_block(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
<<<<<<< HEAD:Bonus/src/map_build.c
	while (i < mlx->map->block_size * mlx->map->minimap_scale && i < WTH - x)
	{
		j = 0;
		while (j < mlx->map->block_size
			* mlx->map->minimap_scale && j < HTH - y)
=======
	while (i < mlx->map->block_size * mlx->map->minimap_scale && i<WTH-x)
	{
		j = 0;
		while (j < mlx->map->block_size * mlx->map->minimap_scale && j< HTH-y )
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3:src/map_build.c
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

void	init_data(t_mlx *mlx, t_cube *cube, t_player *p, t_map *map)
{
	mlx->ptr = mlx_init();
	cube->height = map->rows * map->block_size;
	cube->width = map->columns * map->block_size;
	p->turn_direction = 0;
	p->walk_direction = 0;
	p->rotation_angle = 0;
	p->move_speed = 5;
	p->rotation_speed = 2.5;
	p->side_walk = 0;
<<<<<<< HEAD:Bonus/src/map_build.c
	p->fov = 60;
=======
	p->fov = 90;
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3:src/map_build.c
	mlx->map = map;
	mlx->cube = cube;
	mlx->p = p;
	if (mlx->map->columns > 70 || mlx->map->rows > 70)
		mlx->map->minimap_scale = 0.15;
	else
		mlx->map->minimap_scale = 0.2;
}
