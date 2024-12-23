/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:49:16 by amarouf           #+#    #+#             */
/*   Updated: 2024/12/23 17:19:09 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int get_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int put_pixel(t_addr *addr, int x, int y, int color)
{
	char	*dst;

	dst = addr->pixels + (y * addr->size_line + x * (addr->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
	return (0);
}

int destroy_win(void *param)
{
	t_mlx *mlx = (t_mlx *)param;
	
	mlx_destroy_window(mlx->ptr, mlx->window);
	exit(0);
}

void rotate_player(t_mlx *mlx)
{
	float rotate = convert_to_radian(mlx->addr->p->rotation_angle);
	mlx->addr->p->x += cos(rotate) * 10;
	mlx->addr->p->y += sin(rotate) * 10;
}

void handle_arrows(int keycode, t_mlx *mlx)
{
	float rotate = 90.0;
	
	if (keycode == 65361)
	{
		mlx->addr->p->rotation_angle -= 90;
		rotate_player(mlx);
	}
	else if (keycode == 65363)
	{
		mlx->addr->p->rotation_angle += 90;
		rotate_player(mlx);
	}
	if (mlx->addr->p->rotation_angle >= 360)
		mlx->addr->p->rotation_angle -= 360;
	if (mlx->addr->p->rotation_angle < 0)
		mlx->addr->p->rotation_angle += 360;
}

int key_hook(int keycode,void *param)
{
	t_mlx *mlx = (t_mlx *)param;

	if (keycode == 65307)
		destroy_win(param);
	if (keycode == 119)
    {
		if (mlx->map->map[mlx->addr->p->y / mlx->map->block_size][mlx->addr->p->x / mlx->map->block_size] != '1')
		{
			if (mlx->map->map[(mlx->addr->p->y - 10) / mlx->map->block_size][(mlx->addr->p->x) / mlx->map->block_size] != '1')
				mlx->addr->p->y -= 10;
		}
    }
	else if (keycode == 115)
	{
		if (mlx->map->map[mlx->addr->p->y / mlx->map->block_size][mlx->addr->p->x / mlx->map->block_size] != '1')
		{
			if (mlx->map->map[(mlx->addr->p->y + 10) / mlx->map->block_size][(mlx->addr->p->x) / mlx->map->block_size] != '1')
				mlx->addr->p->y += 10;
		}
	}
	else if (keycode == 100)
	{
		if (mlx->map->map[mlx->addr->p->y / mlx->map->block_size][mlx->addr->p->x / mlx->map->block_size] != '1')
		{
			if (mlx->map->map[(mlx->addr->p->y) / mlx->map->block_size][(mlx->addr->p->x + 10) / mlx->map->block_size] != '1')
				mlx->addr->p->x += 10;
		}
	}
	else if (keycode == 97)
	{
		if (mlx->map->map[mlx->addr->p->y / mlx->map->block_size][mlx->addr->p->x / mlx->map->block_size] != '1')
		{
			if (mlx->map->map[(mlx->addr->p->y) / mlx->map->block_size][(mlx->addr->p->x - 10) / mlx->map->block_size] != '1')
				mlx->addr->p->x -= 10;
		}
	}
	else
		handle_arrows(keycode, mlx);
	return (0);
}

void event_handling(t_mlx *mlx)
{
	mlx_hook(mlx->window, 2, 1L<<0, NULL, mlx);
    mlx_hook(mlx->window, 3, 1L<<1, NULL, mlx);
	mlx_key_hook(mlx->window, &key_hook, mlx);
	mlx_loop_hook(mlx->ptr, ft_cube, mlx);
	mlx_hook(mlx->window, 17, 0, destroy_win, mlx);
	mlx_loop(mlx->ptr);
}
