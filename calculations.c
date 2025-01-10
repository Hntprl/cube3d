/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:26:16 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/05 11:44:09 by amarouf          ###   ########.fr       */
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

bool check_walls(t_mlx *mlx, float x, float y)
{
	// if (x < 0 || x > mlx->cube->width || y < 0 || y > mlx->cube->height)
	// 	return (true);
	if (mlx->map->map[(int)(y / mlx->map->block_size)][(int)(x / mlx->map->block_size)] == '1')
		return (true);
	return (false);
}
