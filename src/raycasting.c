/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 01:25:13 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/06 17:04:26 by amarouf          ###   ########.fr       */
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

	xstep = h_cast->xstep;
	ystep = h_cast->ystep;
	if (check_walls(mlx, xstep, ystep - mlx->ray[index].is_ray_facing_up))
		return (1);
	ystep = mlx->map->block_size;
	if (mlx->ray[index].is_ray_facing_up)
		ystep *= -1;
	xstep = mlx->map->block_size / tan(convert_to_radian(rayangle));
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
	}
	else
	{
		mlx->ray[index].distance = v_cast->distance;
		mlx->ray[index].x_hit = v_cast->xstep;
		mlx->ray[index].y_hit = v_cast->ystep;
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
		flag = 0;
		if (init_first_inter(&h, &v, mlx, index))
			flag = 1;
		while (h.ystep >= 0 && h.ystep <= mlx->cube->height
			&& h.xstep >= 0 && h.xstep <= mlx->cube->width)
			if (horizontal_raycast(mlx, mlx->ray[index].ray_angle, index, &h))
				break ;
		fix_intersection(&h.xstep, &h.ystep, mlx);
		h.distance = ft_distance(mlx->p->x, mlx->p->y, h.xstep, h.ystep);
		while (v.ystep >= 0 && v.ystep <= mlx->cube->height
			&& v.xstep >= 0 && v.xstep <= mlx->cube->width)
			if (vertical_raycast(mlx, mlx->ray[index].ray_angle, index, &v))
				break ;
		fix_intersection(&v.xstep, &v.ystep, mlx);
		v.distance = ft_distance(mlx->p->x, mlx->p->y, v.xstep, v.ystep);
		if (flag)
		{
			mlx->ray[index].distance = v.distance;
			mlx->ray[index].x_hit = v.xstep;
			mlx->ray[index].y_hit = v.ystep;
		}
		else
			check_distance(mlx, &h, &v, index);
		draw_wall(mlx, index);
	}
}

void	raycaster(t_mlx *mlx, int x, int y)
{
	t_ray	*ray;
	int		rays_count;

	rays_count = WTH / mlx->cube->wall_line;
	ray = ft_malloc(sizeof(t_ray) * rays_count, 'a', false);
	mlx->ray = ray;
	build_rays(mlx, rays_count);
	free(ray);
}
