/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:49:16 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/26 22:44:10 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

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
