/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:49:16 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/04 13:39:06 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "cube3d.h"

int	get_color(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int	put_pixel(t_addr *addr, int x, int y, int color)
{
	char	*dst;

	dst = addr->pixels + (y * addr->size_line + x * (addr->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (0);
}

int	destroy_win(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx_destroy_window(mlx->ptr, mlx->window);
	exit(0);
}

void	handle_arrows(int keycode, t_mlx *mlx)
{
	float	rotate;

	rotate = 5.0;
	if (keycode == 65361)
	{
		mlx->p->turn_direction = -1;
	}
	else if (keycode == 65363)
	{
		mlx->p->turn_direction = +1;
	}
}

int	key_hook(int keycode, void *param)
{
	float	new_x;
	float	new_y;
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (keycode == 65307)
		destroy_win(param);
	if (keycode == 'w')
	{
		mlx->p->walk_direction = 1;
	}
	else if (keycode == 's')
	{
		mlx->p->walk_direction = -1;
	}
	else if (keycode == 'a')
	{
		mlx->p->side_walk = 1;
		mlx->p->walk_direction = -1;
	}
	else if (keycode == 'd')
	{
		mlx->p->side_walk = 1;
		mlx->p->walk_direction = 1;
	}
	else
		handle_arrows(keycode, mlx);
	return (0);
}

void	event_handling(t_mlx *mlx)
{
	mlx_hook(mlx->window, 2, 1L << 0, NULL, mlx);
	mlx_hook(mlx->window, 3, 1L << 1, NULL, mlx);
	mlx_key_hook(mlx->window, &key_hook, mlx);
	mlx_loop_hook(mlx->ptr, ft_cube, mlx);
	mlx_hook(mlx->window, 17, 0, destroy_win, mlx);
	mlx_loop(mlx->ptr);
}
