/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 01:25:13 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/04 14:22:53 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "cube3d.h"

#include <stdlib.h>
#include <string.h> // For memset

void images_to_xpm(t_mlx *wind) {
    char *directs[5];
    int i = 0;
    
    directs[0] = wind->map->no_img;
    directs[1] = wind->map->su_img;
    directs[2] = wind->map->es_img;
    directs[3] = wind->map->we_img;
    
    i = 0;
    while(i < 4)
    {
        wind->texture[i].xpm = mlx_xpm_file_to_image(wind->ptr, directs[i], 
            &wind->texture[i].t_width,   
            &wind->texture[i].t_height);
            
        if(!wind->texture[i].xpm)
            printerr(1, "ERROR LOADING TEXTURE");
            
        wind->texture[i].addr = mlx_get_data_addr(wind->texture[i].xpm,
            &wind->texture[i].bpp,
            &wind->texture[i].line_len,
            &wind->texture[i].endian);
        i++;
    }
}


int	vertical_raycast(t_mlx *mlx, float rayangle, int index, t_cast *v_cast)
{
	double	xstep;
	double	ystep;

	ystep = v_cast->ystep;
	xstep = v_cast->xstep;
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

	index = -1;
	while (++ index < rays_count)
	{
		init_first_inter(&h, &v, mlx, index);
		while (h.ystep >= 0 && h.ystep < mlx->cube->height
			&& h.xstep >= 0 && h.xstep < mlx->cube->width)
		{
			if (horizontal_raycast(mlx, mlx->ray[index].ray_angle, index, &h))
				break ;
		}
		fix_intersection(&h.xstep, &h.ystep, mlx);
		h.distance = ft_distance(mlx->p->x, mlx->p->y, h.xstep, h.ystep);
		while (v.ystep >= 0 && v.ystep < mlx->cube->height
			&& v.xstep >= 0 && v.xstep < mlx->cube->width)
		{
			if (vertical_raycast(mlx, mlx->ray[index].ray_angle, index, &v))
				break ;
		}
		fix_intersection(&v.xstep, &v.ystep, mlx);
		v.distance = ft_distance(mlx->p->x, mlx->p->y, v.xstep, v.ystep);
		(check_distance(mlx, &h, &v, index), draw_wall(mlx, index));
	}
}

void	raycaster(t_mlx *mlx, int x, int y)
{
	t_ray *ray;
	int rays_count;
	(void)x;
	(void)y;

	rays_count = mlx->cube->width / mlx->cube->wall_line;

	ray = ft_malloc(sizeof(t_ray) * rays_count, 'a', false);
	mlx->ray = ray;
	build_rays(mlx, rays_count);
}
