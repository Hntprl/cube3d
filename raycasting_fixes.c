/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_fixes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:21:31 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/24 19:57:15 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	find_ray_direction(float angle, t_ray *ray)
{
	ray->is_ray_facing_down = (angle > 0 && angle < 180);
	ray->is_ray_facing_up = !ray->is_ray_facing_down;
	ray->is_ray_facing_right = (angle < 90 || angle > 270);
	ray->is_ray_facing_left = !ray->is_ray_facing_right;
}

float	fix_rayangle(float angle)
{
	if (angle > 360)
		angle = angle - 360;
	if (angle < 0)
		angle = 360 + angle;
	return (angle);
}

void	fix_intersection(double *x, double *y, t_mlx *mlx)
{
	if (*x < 0)
		*x = 0;
	if (*x > mlx->cube->width)
		*x = mlx->cube->width;
	if (*y < 0)
		*y = 0;
	if (*y > mlx->cube->height)
		*y = mlx->cube->height;
}

void	fix(int *x, int *y, t_mlx *mlx)
{
	if (*x < 0)
		*x = 0;
	if (*x > WTH)
		*x = WTH;
	if (*y < 0)
		*y = 0;
	if (*y > HTH)
		*y = HTH;
}

void	draw_wall(t_mlx *mlx, int index)
{
	double	plane_distance;
	double	wall_height;
	t_wall	wall;
	
	mlx->ray[index].distance = mlx->ray[index].distance * cos(convert_to_radian(mlx->ray[index].ray_angle - mlx->p->rotation_angle));
	plane_distance = (WTH / 2) / tan(mlx->p->pov / 2);
	wall_height = (mlx->map->block_size / mlx->ray[index].distance)
		* plane_distance;
	wall.y = HTH / 2 - wall_height / 2;
	wall.x = index;
	fix(&wall.x, &wall.y, mlx);
	wall.y2 = wall.y + wall_height;
	fix(&wall.x, &wall.y2, mlx);
	wall.x2 = wall.x;
	bresenham(mlx, wall);
}
