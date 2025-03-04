/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:49:16 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/27 14:52:46 by amarouf          ###   ########.fr       */
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
	int		i;

	i = 0;
	mlx = (t_mlx *)param;
	while (i < 4)
	{
		if (mlx->texture[i].xpm)
			mlx_destroy_image(mlx->ptr, mlx->texture[i].xpm);
		i++;
	}
	ft_malloc(0, 'f', false);
	mlx_destroy_window(mlx->ptr, mlx->window);
	mlx_destroy_display(mlx->ptr);
	free(mlx->ptr);
	exit(0);
}
