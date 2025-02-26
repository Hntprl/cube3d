/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:39:02 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/24 14:45:39 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

void	ft_draw_block(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mlx->map->block_size * mlx->map->minimap_scale && i < WTH - x)
	{
		j = 0;
		while (j < mlx->map->block_size
			* mlx->map->minimap_scale && j < HTH - y)
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
	p->fov = 60;
	mlx->map = map;
	mlx->cube = cube;
	mlx->p = p;
	if (mlx->map->columns > 70 || mlx->map->rows > 70)
		mlx->map->minimap_scale = 0.15;
	else
		mlx->map->minimap_scale = 0.2;
}
