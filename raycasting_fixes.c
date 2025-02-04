/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_fixes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:21:31 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/04 14:20:47 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "cube3d.h"


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
        *x = mlx->cube->width;
    if (*y < 0)
        *y = 0;
    if (*y > mlx->cube->height)
        *y = mlx->cube->height;
}

void fix(int *x, int *y, t_mlx *mlx)
{
    (void)mlx;
    if (*x < 0)
        *x = 0;
    if (*x > WTH)
        *x = WTH;
    if (*y < 0)
        *y = 0;
    if (*y > HTH)
        *y = HTH;
}

int get_wall_orientation(t_mlx *mlx,int index)
{
    if (mlx->ray[index].was_hit_horizontal)
    {
        if(mlx->ray[index].is_ray_facing_up)
            return 0;
        else    
            return 1;
    }
    else if(mlx->ray[index].was_hit_vertical)
    {
        if(mlx->ray[index].is_ray_facing_right)
            return 2;
        else
            return 3;
    }
    return 0;
}

void rendering_texture(t_mlx *mlx, int index, t_wall wall)
{
    double wall_height = wall.y2 - wall.y;
    double step;
    int texture_x;
    double texture_pos = 0.0;
    int d = get_wall_orientation(mlx,index);
    // int original_y = wall.y;

    if (mlx->ray[wall.x].was_hit_vertical)
        texture_x = (int)(fmod(mlx->ray[wall.x].y_hit, mlx->map->block_size) / mlx->map->block_size * mlx->texture[d].t_width);
    else
        texture_x = (int)(fmod(mlx->ray[wall.x].x_hit, mlx->map->block_size) / mlx->map->block_size * mlx->texture[d].t_width);
    step = 1.0 * mlx->texture[d].t_height / wall_height;
    while (wall.y < wall.y2)
    {
        int texture_y = (int)texture_pos & (mlx->texture[d].t_height - 1); // calculate the current position in the texture
        int offset = (texture_y * mlx->texture[d].line_len) +
                     (texture_x * (mlx->texture[d].bpp / 8));
        if (wall.y >= 0 && wall.y < HTH &&
            texture_x >= 0 && texture_x < mlx->texture[d].t_width &&
            texture_y >= 0 && texture_y < mlx->texture[d].t_height)
        {
            int color = *(int *)(mlx->texture[d].addr + offset);
            put_pixel(mlx->addr, wall.x, wall.y, color);
        }
        wall.y++;
        texture_pos += step;
    }
}

void draw_wall(t_mlx *mlx, int index)
{
    double plane_distance;
    double wall_height;
    t_wall wall;

    mlx->ray[index].distance = mlx->ray[index].distance * cos(convert_to_radian(mlx->ray[index].ray_angle - mlx->p->rotation_angle));
    plane_distance = (WTH / 2) / tan(mlx->p->pov / 2);
    wall_height = (mlx->map->block_size / mlx->ray[index].distance) * plane_distance;
    wall.y = HTH / 2 - wall_height / 2;
    wall.x = index;
    fix(&wall.x, &wall.y, mlx);
    wall.y2 = wall.y + wall_height;
    fix(&wall.x, &wall.y2, mlx);
    wall.x2 = wall.x;

    rendering_texture(mlx, index, wall);
    // bresenham(mlx, wall,index);
}
