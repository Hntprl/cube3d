/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_fixes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:21:31 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/02 17:50:56 by bbenjrai         ###   ########.fr       */
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
void	bresenham(t_mlx *mlx, t_wall wall,int texture_index)
{
	t_bnham bnham;
	double	texture_step;
	double	texture_pos;
	int		color;
	int		texture_x, texture_y ,wall_hit_pos;
	
	if (mlx->ray->was_hit_vertical)
    wall_hit_pos = fmod(mlx->ray->y_hit, mlx->map->block_size) / mlx->map->block_size;
	else
    wall_hit_pos = fmod(mlx->ray->x_hit, mlx->map->block_size) / mlx->map->block_size;
	bnham.dx = abs(wall.x2 - mlx->p->x);
	bnham.dy = abs(wall.y2 - mlx->p->y);
	texture_x = (int)(wall_hit_pos * mlx->texture[texture_index].t_width);
	texture_step = (double)mlx->texture[texture_index].t_height / (wall.y2 - wall.y);
	texture_pos = 0;
	
	if (wall.x == wall.x2)
		bnham.sx = 0;
	else if (wall.x < wall.x2)
		bnham.sx = 1;
	else
		bnham.sx = -1;
	if (wall.y == wall.y2)
		bnham.sy = 0;
	else if (wall.y < wall.y2)
		bnham.sy = 1;
	else
		bnham.sy = -1;
	bnham.error = bnham.dx - bnham.dy;
	while (wall.x != wall.x2 || wall.y != wall.y2)
	{

		texture_y = (int)texture_pos % mlx->texture[texture_index].t_height;
		texture_pos += texture_step;

		// Fetch color from texture
		color = *(int *)(mlx->addr->addr_e + (texture_y * mlx->addr->e_size_line) +
			(texture_x * (mlx->addr->e_bits_per_pixel / 8)));
		put_pixel(mlx->addr, wall.x, wall.y, color);//  here i need to render the textures on the walls 
		bnham.e2 = bnham.error * 2;
		if (bnham.e2 > -bnham.dy)
		{
			bnham.error -= bnham.dy;
			wall.x += bnham.sx;
		}
		if (bnham.e2 < bnham.dx)
		{
			bnham.error += bnham.dx;
			wall.y += bnham.sy;
		}
	}
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
	bresenham(mlx, wall,index);
}
	// update_texture_pixel(mlx,index,wall_height);
