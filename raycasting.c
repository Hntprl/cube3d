/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 01:25:13 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/13 09:30:05 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int vertical_raycast(t_mlx *mlx, float rayangle, int index, t_cast *v_cast)
{
	double xstep;
	double ystep;

	ystep = v_cast->ystep;
	xstep = v_cast->xstep;
	if (mlx->ray[index].is_ray_facing_left)
		xstep--;
	if (check_walls(mlx, xstep, ystep))
	{
		return (1);
	}
	xstep = mlx->map->block_size;
	if (mlx->ray[index].is_ray_facing_left)
		xstep *= -1;
	ystep = mlx->map->block_size * tan(convert_to_radian(rayangle));
	if ((mlx->ray[index].is_ray_facing_up && ystep > 0) || (mlx->ray[index].is_ray_facing_down && ystep < 0))
		ystep *= -1;
	v_cast->ystep += ystep;
	v_cast->xstep += xstep;
	return (0);
}

int horizontal_raycast(t_mlx *mlx, float rayangle, int index, t_cast *h_cast)
{
	double xstep = h_cast->xstep;
	double ystep = h_cast->ystep;

	if (mlx->ray[index].is_ray_facing_up)
		ystep--;
	
	if (check_walls(mlx, xstep, ystep))
	{
		return 1;
	}
	ystep = mlx->map->block_size;
	if (mlx->ray[index].is_ray_facing_up)
		ystep *= -1;
	xstep = mlx->map->block_size / tan(convert_to_radian(rayangle));
	if ((mlx->ray[index].is_ray_facing_left && xstep > 0) || (mlx->ray[index].is_ray_facing_right && xstep < 0))
		xstep *= -1;
	h_cast->ystep += ystep;
	h_cast->xstep += xstep;

	return 0;
}

void find_ray_direction(float angle, t_ray *ray)
{
	ray->is_ray_facing_down = (angle > 0 && angle < 180);
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	ray->is_ray_facing_right = (angle < 90 || angle > 270);
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
}

float fix_rayangle(float angle)
{
	if (angle > 360)
		angle = angle - 360;
	if (angle < 0)
		angle = 360 + angle;
	return (angle);
}

void fix_intersection(double *x, double *y, t_mlx *mlx)
{
	if (*x < 0)
		*x = 0;
	if (*x > mlx->cube->width)
		*x =  mlx->cube->width;
	if (*y < 0)
		*y = 0;
	if (*y > mlx->cube->height)
		*y =  mlx->cube->height;
}

void fix(int *x, int *y, t_mlx *mlx)
{
	
	if (*x < 0)
		*x = 0;
	if (*x > mlx->cube->width)
		*x =  mlx->cube->width;
	if (*y < 0)
		*y = 0;
	if (*y > mlx->cube->height)
		*y =  mlx->cube->height;
}

void draw_wall(t_mlx *mlx, int index)
{
	double plane_distance = ( mlx->cube->width / 2) / tan(mlx->p->pov / 2);
	double wall_height = (mlx->map->block_size / mlx->ray[index].distance) * plane_distance;

	int y = mlx->cube->height / 2 - wall_height / 2;
	int x = index;
	fix(&x, &y, mlx);
	int endy = y + wall_height;
	fix(&x, &endy, mlx);

	bresenham(mlx, x, y, x, endy);
}

void build_rays(t_mlx *mlx, int rays_count)
{
	t_cast h_cast;
	t_cast v_cast;
	int index;
	float pov;
	float gap_angle;
	
	index = 0;
	gap_angle = mlx->p->pov / (rays_count);
	pov = mlx->p->pov / 2;
	while (index < rays_count)
	{
		mlx->ray[index].was_hit_horizontal = 0;
		mlx->ray[index].was_hit_vertical = 0;
		mlx->ray[index].ray_angle = fix_rayangle(mlx->p->rotation_angle - pov + (index * gap_angle));
		find_ray_direction(mlx->ray[index].ray_angle, &mlx->ray[index]);
		// Initialize horizontal intersection
		h_cast.ystep = floor(mlx->p->y / mlx->map->block_size) * mlx->map->block_size;
		if (mlx->ray[index].is_ray_facing_down)
			h_cast.ystep += mlx->map->block_size;
		h_cast.xstep = mlx->p->x + (h_cast.ystep - mlx->p->y) / tan(convert_to_radian(mlx->ray[index].ray_angle));

		// Initialize vertical intersection
		v_cast.xstep = floor(mlx->p->x / mlx->map->block_size) * mlx->map->block_size;
		if (mlx->ray[index].is_ray_facing_right)
			v_cast.xstep += mlx->map->block_size;
		v_cast.ystep = mlx->p->y + (v_cast.xstep - mlx->p->x) * tan(convert_to_radian(mlx->ray[index].ray_angle));

		while (h_cast.ystep >= 0 && h_cast.ystep < mlx->cube->height && h_cast.xstep >= 0 && h_cast.xstep < mlx->cube->width)
		{
			if (horizontal_raycast(mlx, mlx->ray[index].ray_angle, index, &h_cast))
				break;
		}
		fix_intersection(&h_cast.xstep, &h_cast.ystep, mlx);
		h_cast.distance = calculate_distance(mlx->p->x, mlx->p->y, h_cast.xstep, h_cast.ystep);
		// Cast rays
		while (v_cast.ystep >= 0 && v_cast.ystep < mlx->cube->height && v_cast.xstep >= 0 && v_cast.xstep < mlx->cube->width)
		{
			if (vertical_raycast(mlx, mlx->ray[index].ray_angle, index, &v_cast))
				break;
		}
		fix_intersection(&v_cast.xstep, &v_cast.ystep, mlx);
		v_cast.distance = calculate_distance(mlx->p->x, mlx->p->y, v_cast.xstep, v_cast.ystep);
		if (h_cast.distance <= v_cast.distance)
		{
			mlx->ray[index].x_hit = h_cast.xstep;
			mlx->ray[index].y_hit = h_cast.ystep;
			mlx->ray[index].was_hit_horizontal = 1;
			mlx->ray[index].distance = h_cast.distance;
		}
		else
		{
			mlx->ray[index].x_hit = v_cast.xstep;
			mlx->ray[index].y_hit = v_cast.ystep;
			mlx->ray[index].was_hit_vertical = 1;
			mlx->ray[index].distance = v_cast.distance;
		}
		draw_wall(mlx, index);
		index++;
	}
}

void	raycaster(t_mlx *mlx, int x, int y)
{
	t_ray	*ray; 
	int rays_count;
	
	rays_count = mlx->cube->width / mlx->cube->wall_line;

	ray = malloc(sizeof(t_ray) * rays_count);
	mlx->ray = ray;
	build_rays(mlx, rays_count);
}