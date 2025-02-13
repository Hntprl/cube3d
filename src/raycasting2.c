/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 08:59:22 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/10 18:06:38 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	init_first_inter(t_cast *h_cast, t_cast *v_cast, t_mlx *mlx, int index)
{
	float	pov;
	float	gap_angle;

	gap_angle = mlx->p->pov / (WTH / mlx->cube->wall_line);
	pov = mlx->p->pov / 2;
	mlx->ray[index].ray_angle = fix_rayangle(mlx->p->rotation_angle - pov
			+ (index * gap_angle));
	find_ray_direction(mlx->ray[index].ray_angle, &mlx->ray[index]);
	h_cast->ystep = floor(mlx->p->y / mlx->map->block_size)
		* mlx->map->block_size;
	if (mlx->ray[index].is_ray_facing_down)
		h_cast->ystep += mlx->map->block_size;
	h_cast->xstep = mlx->p->x + (h_cast->ystep - mlx->p->y)
		/ tan(convert_to_radian(mlx->ray[index].ray_angle));
	if (mlx->ray[index].ray_angle == 0 || mlx->ray[index].ray_angle == 360)
		return (1);
	v_cast->xstep = floor(mlx->p->x / mlx->map->block_size)
		* mlx->map->block_size;
	if (mlx->ray[index].is_ray_facing_right)
		v_cast->xstep += mlx->map->block_size;
	v_cast->ystep = mlx->p->y + (v_cast->xstep - mlx->p->x)
		* tan(convert_to_radian(mlx->ray[index].ray_angle));
	if (mlx->ray[index].ray_angle == 90 || mlx->ray[index].ray_angle == 270)
		return (2);
	return (0);
}

int	calculate_distance(t_mlx *mlx, int index, t_cast *v, t_cast *h)
{
	int	flag;

	flag = init_first_inter(h, v, mlx, index);
	while (h->ystep >= 0 && h->ystep <= mlx->cube->height
		&& h->xstep >= 0 && h->xstep <= mlx->cube->width)
		if (horizontal_raycast(mlx, mlx->ray[index].ray_angle, index, h))
			break ;
	fix_intersection(&h->xstep, &h->ystep, mlx);
	h->distance = ft_distance(mlx->p->x, mlx->p->y, h->xstep, h->ystep);
	while (v->ystep >= 0 && v->ystep <= mlx->cube->height
		&& v->xstep >= 0 && v->xstep <= mlx->cube->width)
		if (vertical_raycast(mlx, mlx->ray[index].ray_angle, index, v))
			break ;
	fix_intersection(&v->xstep, &v->ystep, mlx);
	v->distance = ft_distance(mlx->p->x, mlx->p->y, v->xstep, v->ystep);
	return (flag);
}

void	init_br(t_wall wall, t_bnham *bnham)
{
	if (wall.x == wall.x2)
		bnham->sx = 0;
	else if (wall.x < wall.x2)
		bnham->sx = 1;
	else
		bnham->sx = -1;
	if (wall.y == wall.y2)
		bnham->sy = 0;
	else if (wall.y < wall.y2)
		bnham->sy = 1;
	else
		bnham->sy = -1;
}
