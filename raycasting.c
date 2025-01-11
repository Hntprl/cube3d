/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 01:25:13 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/11 14:52:55 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int vertical_raycast(t_mlx *mlx, float gap, int index, t_cast *v_cast)
{
	long xstep;
	long ystep;

	xstep = v_cast->firstx;
	ystep = v_cast->firsty;
	bresenham(mlx, mlx->p->x, mlx->p->y, xstep, ystep);
	if (check_walls(mlx, xstep, ystep))
	{
		mlx->ray[index].was_hit_vertical = 1;
		mlx->ray[index].wall_hit_x = xstep;
		mlx->ray[index].wall_hit_y = ystep;
		return  (1);
	}
	xstep = mlx->map->block_size;
	if (mlx->ray[index].is_ray_facing_left)
		xstep *= -1;
	ystep = xstep * tan(convert_to_radian(gap));
	if (mlx->ray[index].is_ray_facing_up && xstep > 0 || mlx->ray[index].is_ray_facing_down && xstep < 0)
		xstep *= -1;
	v_cast->ystep += ystep;
	v_cast->xstep += xstep;
	return (0);
}

int	horizontal_raycast(t_mlx *mlx, float rayangle, int index, t_cast *h_cast)
{
	long	xstep;
	long	ystep;

	ystep = h_cast->ystep;
	xstep = h_cast->xstep;
	if (mlx->ray[index].is_ray_facing_up)
		ystep --;
	bresenham(mlx, mlx->p->x, mlx->p->y, xstep, ystep);
	if (check_walls(mlx, xstep, ystep))
	{
		mlx->ray[index].was_hit_horizontal = 1;
		mlx->ray[index].wall_hit_x = xstep;
		mlx->ray[index].wall_hit_y = ystep;
		return  (1);
	}
	ystep = mlx->map->block_size;
	if (mlx->ray[index].is_ray_facing_up)
		ystep *= -1;
	xstep = mlx->map->block_size / tan(convert_to_radian(rayangle));
	if (mlx->ray[index].is_ray_facing_left && xstep > 0 || mlx->ray[index].is_ray_facing_right && xstep < 0)
		xstep *= -1;
    h_cast->ystep += ystep;
    h_cast->xstep += xstep;
    return (0);
}

void find_ray_direction(float angle, t_ray *ray)
{
	if (angle > 0 && angle < 180)
	{
		ray->is_ray_facing_down = 1;
		ray->is_ray_facing_up = 0;
	}
	else
	{
		ray->is_ray_facing_down = 0;
		ray->is_ray_facing_up = 1;
	}
	if (angle > 90 && angle < 270)
	{
		ray->is_ray_facing_right = 0;
		ray->is_ray_facing_left = 1;
	}
	else
	{
		ray->is_ray_facing_right = 1;
		ray->is_ray_facing_left = 0;
	}
}

float fix_rayangle(float angle)
{
	if (angle > 360)
		angle = angle - 360;
	if (angle < 0)
		angle = 360 + angle;
	return (angle);
}

void build_rays(t_mlx *mlx, int rays_count)
{
    t_cast h_cast;
    t_cast v_cast;
	int index = 0;
	float pov = mlx->p->pov / 2;
	float gap_angle = pov * -1;
	float gap = mlx->p->pov / (rays_count);

	while (index < rays_count)
	{
		mlx->ray[index].ray_angle = fix_rayangle(mlx->p->rotation_angle + gap_angle);
		find_ray_direction(mlx->ray[index].ray_angle, &mlx->ray[index]);
        h_cast.firsty = floor(mlx->p->y / mlx->map->block_size) * mlx->map->block_size;
		if (mlx->ray->is_ray_facing_down)
			h_cast.firsty += mlx->map->block_size;
		h_cast.firstx = mlx->p->x + (h_cast.firsty - mlx->p->y) / tan(convert_to_radian(mlx->ray[index].ray_angle));
        h_cast.ystep = h_cast.firsty;
        h_cast.xstep = h_cast.firstx;

		v_cast.firstx = floor(mlx->p->x / mlx->map->block_size) * mlx->map->block_size;
		if (mlx->ray->is_ray_facing_right)
			v_cast.firstx += mlx->map->block_size;
		v_cast.firsty = mlx->p->y + tan(mlx->ray[index].ray_angle) * (v_cast.firstx - mlx->p->x);
		v_cast.xstep = v_cast.firstx;
		v_cast.ystep = v_cast.firsty;
		while ( h_cast.ystep > 0 && h_cast.ystep < mlx->cube->height && h_cast.xstep > 0 && h_cast.xstep < mlx->cube->width
		&& v_cast.ystep > 0 && v_cast.ystep < mlx->cube->height && v_cast.xstep > 0 && v_cast.xstep < mlx->cube->width)
        {
			if (horizontal_raycast(mlx, mlx->ray[index].ray_angle, index, &h_cast))
				break ;
			if (vertical_raycast(mlx,  mlx->ray[index].ray_angle, index, &v_cast))
				break ;
		}
		gap_angle += gap;
		index++;
	}
}

void	raycaster(t_mlx *mlx, int x, int y)
{
	t_ray	*ray; 
	int rays_count = mlx->cube->width / mlx->cube->wall_line;

	ray = malloc(sizeof(t_ray) * rays_count);
	mlx->ray = ray;
	build_rays(mlx, rays_count);
}