/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:19:18 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/27 14:55:47 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	mouse_move(int x, int y, t_mlx *mlx)
{
	static int	last_x;

	mlx_mouse_get_pos(mlx->ptr, mlx->window, &x, &y);
	(void)y;
	if (x > last_x)
		mlx->p->turn_direction += 1;
	else if (x < last_x)
		mlx->p->turn_direction -= 1;
	last_x = x;
	return (0);
}
