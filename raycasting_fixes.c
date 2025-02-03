/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_fixes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:21:31 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/03 15:22:01 by bbenjrai         ###   ########.fr       */
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
void bresenham(t_mlx *mlx, t_wall wall, int texture_index)
{
    t_bnham bnham;
    int color;
    int texture_x, texture_y;

    // check texture_index is valid
    if (texture_index < 0 || texture_index >= 4) {
        // printf("Invalid texture index: %d\n", texture_index);
        return;
    }

    //  wall hit position
    double wall_hit_pos;
    if (mlx->ray[texture_index].was_hit_vertical)
        wall_hit_pos = fmod(mlx->ray[texture_index].y_hit, mlx->map->block_size) / mlx->map->block_size;
    else
        wall_hit_pos = fmod(mlx->ray[texture_index].x_hit, mlx->map->block_size) / mlx->map->block_size;

    //  wall_hit_pos is between 0 and 1
    wall_hit_pos = fmax(0.0, fmin(1.0, wall_hit_pos));

    //  texture x coordinate
    texture_x = (int)(wall_hit_pos * (mlx->texture[texture_index].t_width - 1));

    //  wall height
    double wall_height = wall.y2 - wall.y;
    if (wall_height <= 0) wall_height = 1;

    // starting y position for texture mapping
    int start_y = wall.y;

    // bresenham setup
    bnham.dx = abs(wall.x2 - wall.x);
    bnham.dy = abs(wall.y2 - wall.y);
    bnham.sx = (wall.x < wall.x2) ? 1 : -1;
    bnham.sy = (wall.y < wall.y2) ? 1 : -1;
    bnham.error = bnham.dx - bnham.dy;
    double y = 0;
    // double step = mlx->texture[texture_index].t_height/ wall_height;
    while ((wall.x != wall.x2 || wall.y != wall.y2 ) && wall.y<wall.y2)
    {
        // calculer y progress (between 0 and 1)
        double y_progress = (double)(wall.y - start_y) / wall_height;
        y_progress = fmax(0.0, fmin(1.0, y_progress));
        // printf("progress %d\n",y_progress);
        // // calculer texture y coordinate
        texture_y = (int)(y_progress * (mlx->texture[texture_index].t_height - 1));

        //  checking bounds 
        if (wall.x >= 0 && wall.x < WTH && 
            wall.y >= 0 && wall.y < HTH && 
            texture_x >= 0 && texture_x < mlx->texture[texture_index].t_width && 
            texture_y >= 0 && texture_y < mlx->texture[texture_index].t_height)
        {
            int offset = (texture_y * mlx->texture[texture_index].line_len) +
                        (texture_x * (mlx->texture[texture_index].bpp / 8));
            // Additional bounds check for offset
            if (offset >= 0 && offset < (mlx->texture[texture_index].line_len * mlx->texture[texture_index].t_height))
            {
                color = *(int *)(mlx->texture[texture_index].addr + offset);
                put_pixel(mlx->addr, wall.x, wall.y, color);
            }
            wall.y+=y_progress;
        }
        // Bresenham step
        bnham.e2 = 2 * bnham.error;
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



void rendering(t_mlx *mlx,int index,t_wall wall)
{
    
    double wall_height = wall.y2 - wall.y;
    double step=mlx->texture[0].t_height/(wall_height);
    int texture_x,texture_y;
    if (mlx->ray[wall.x].was_hit_vertical)
        texture_x = (fmod(mlx->ray[wall.x].y_hit, mlx->map->block_size) )/ mlx->map->block_size *mlx->texture[0].t_width;
    else
        texture_x = (fmod(mlx->ray[wall.x].x_hit, mlx->map->block_size) / mlx->map->block_size )*mlx->texture[0].t_height;
    texture_y = 0;
    int  color ;
    while(wall.y<wall.y2)
    {
        int offset = (texture_y * mlx->texture[0].line_len) +
                        (texture_x * (mlx->texture[0].bpp / 8));
        if(texture_x >= 0 && texture_x <= mlx->texture[0].t_width && texture_y >= 0 && texture_y <= mlx->texture[0].t_height)
            color = *(int *)(mlx->texture[0].addr +  offset);
        put_pixel(mlx->addr, wall.x, wall.y, color);
        wall.y++;
        texture_y+=step;
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

	//    wall.y = HTH / 2 - wall_height / 2;
    // wall.y2 = wall.y + wall_height;
    
    // // Set x coordinates - this is crucial!
    // wall.x = index;        // Current strip x position
    // wall.x2 = index; 
    rendering(mlx,index,wall);
	// bresenham(mlx, wall,index);
}
    // Debug print
    // printf("Drawing wall: x=%d->%d, y=%f->%f\n", wall.x, wall.x2, wall.y, wall.y2);