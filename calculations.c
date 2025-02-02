/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:26:16 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/01 17:48:14 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

float	convert_to_radian(float angle)
{
	return (angle * (PI / 180));
}

float	convert_to_degree(float radian)
{
	return (radian * (180 / PI));
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

double	ft_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
