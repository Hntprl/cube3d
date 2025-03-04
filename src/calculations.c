/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:26:16 by amarouf           #+#    #+#             */
/*   Updated: 2025/03/01 10:16:33 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

float	convert_to_radian(float angle)
{
	return (angle * (PI / 180));
}

bool	check_walls(t_mlx *mlx, float x, float y)
{
	if (x < 0 || x >= mlx->cube->width || y < 0 || y >= mlx->cube->height)
		return (true);
	if (mlx->map->map[(int)((y / mlx->map->block_size))][(int)(x
			/ mlx->map->block_size)] == '1')
		return (true);
	return (false);
}

double	ft_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	init_structs(t_cube *cube, t_player *p, t_addr *addr)
{
	ft_bzero(cube, sizeof(t_cube));
	ft_bzero(p, sizeof(t_player));
	ft_bzero(addr, sizeof(t_addr));
}

bool	is_position_clear(t_mlx *mlx, int x, int y)
{
	return (!check_walls(mlx, x - 5, y - 5)
		&& !check_walls(mlx, x + 5, y - 5)
		&& !check_walls(mlx, x - 5, y + 5)
		&& !check_walls(mlx, x + 5, y + 5));
}
