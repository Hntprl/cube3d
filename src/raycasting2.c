/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:59:22 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/06 17:00:32 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	init_first_inter(t_cast *h_cast, t_cast *v_cast, t_mlx *mlx, int index)
{
	float	pov;
	float	gap_angle;
	int		rays_count;

	rays_count = WTH / mlx->cube->wall_line;
	gap_angle = mlx->p->pov / (rays_count);
	pov = mlx->p->pov / 2;
	mlx->ray[index].ray_angle = fix_rayangle(mlx->p->rotation_angle - pov
			+ (index * gap_angle));
	find_ray_direction(mlx->ray[index].ray_angle, &mlx->ray[index]);
	h_cast->ystep = floor(mlx->p->y / mlx->map->block_size)
		* mlx->map->block_size;
	if (mlx->ray[index].is_ray_facing_down)
		h_cast->ystep += mlx->map->block_size;
	h_cast->xstep = mlx->p->x + (h_cast->ystep - mlx->p->y) / tan(convert_to_radian(mlx->ray[index].ray_angle));
	if (mlx->ray[index].ray_angle == 0 || mlx->ray[index].ray_angle == 360)
	{	
		return (1);
	}
	v_cast->xstep = floor(mlx->p->x / mlx->map->block_size)
		* mlx->map->block_size;
	if (mlx->ray[index].is_ray_facing_right)
		v_cast->xstep += mlx->map->block_size;
	v_cast->ystep = mlx->p->y + (v_cast->xstep - mlx->p->x) * tan(convert_to_radian(mlx->ray[index].ray_angle));
	return (0);
}
