/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 01:25:13 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/27 15:27:08 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	vertical_raycast(t_mlx *mlx, float rayangle, int index, t_cast *v_cast)
{
	double	xstep;
	double	ystep;

	xstep = v_cast->xstep;
	ystep = v_cast->ystep;
	if (check_walls(mlx, xstep - mlx->ray[index].is_ray_facing_left, ystep))
		return (1);
	xstep = mlx->map->block_size;
	if (mlx->ray[index].is_ray_facing_left)
		xstep *= -1;
	ystep = mlx->map->block_size * tan(convert_to_radian(rayangle));
	if ((mlx->ray[index].is_ray_facing_up && ystep > 0)
		|| (mlx->ray[index].is_ray_facing_down && ystep < 0))
		ystep *= -1;
	v_cast->ystep += ystep;
	v_cast->xstep += xstep;
	return (0);
}

int	horizontal_raycast(t_mlx *mlx, float rayangle, int index, t_cast *h_cast)
{
	double	xstep;
	double	ystep;
	double	adj;

	xstep = h_cast->xstep;
	ystep = h_cast->ystep;
	if (check_walls(mlx, xstep, ystep - mlx->ray[index].is_ray_facing_up))
		return (1);
	ystep = mlx->map->block_size;
	if (mlx->ray[index].is_ray_facing_up)
		ystep *= -1;
	adj = mlx->map->block_size / tan(convert_to_radian(rayangle));
	xstep = adj;
	if ((mlx->ray[index].is_ray_facing_left && xstep > 0)
		|| (mlx->ray[index].is_ray_facing_right && xstep < 0))
		xstep *= -1;
	h_cast->ystep += ystep;
	h_cast->xstep += xstep;
	return (0);
}

void	check_distance(t_mlx *mlx, t_cast *h_cast, t_cast *v_cast, int index)
{
	if (h_cast->distance < v_cast->distance)
	{
		mlx->ray[index].distance = h_cast->distance;
		mlx->ray[index].x_hit = h_cast->xstep;
		mlx->ray[index].y_hit = h_cast->ystep;
		mlx->ray[index].was_hit_horizontal = 1;
	}
	else
	{
		mlx->ray[index].distance = v_cast->distance;
		mlx->ray[index].x_hit = v_cast->xstep;
		mlx->ray[index].y_hit = v_cast->ystep;
		mlx->ray[index].was_hit_vertical = 1;
	}
}

void	build_rays(t_mlx *mlx, int rays_count)
{
	t_cast	h;
	t_cast	v;
	int		index;
	int		flag;

	index = -1;
	while (++ index < rays_count)
	{
		flag = calculate_distance(mlx, index, &v, &h);
		if (flag == 1)
		{
			init_ray_hit(mlx->ray, index, v);
			mlx->ray[index].was_hit_vertical = 1;
		}
		else if (flag == 2)
		{
			init_ray_hit(mlx->ray, index, h);
			mlx->ray[index].was_hit_horizontal = 1;
		}
		else
			check_distance(mlx, &h, &v, index);
		draw_wall(mlx, index);
	}
}

void	raycaster(t_mlx *mlx)
{
	t_ray	*ray;
	int		rays_count;

	rays_count = WTH;
	ray = malloc(sizeof(t_ray) * rays_count);
	mlx->ray = ray;
	build_rays(mlx, rays_count);
	free(ray);
}
