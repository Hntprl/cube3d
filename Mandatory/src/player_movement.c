/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:37:22 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/26 17:31:16 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

void    set_player_direction(char c, t_mlx *mlx)
{
    if (c == 'N')
        mlx->p->rotation_angle = 270;
    if (c == 'S')
        mlx->p->rotation_angle = 90;
    if (c == 'E')
        mlx->p->rotation_angle = 0;
    if (c == 'W')
        mlx->p->rotation_angle = 180;
}

void	rotate_player(t_mlx *mlx)
{
	mlx->p->rotation_angle += mlx->p->turn_direction * mlx->p->rotation_speed;
	mlx->p->turn_direction = 0;
	if (mlx->p->rotation_angle > 360)
		mlx->p->rotation_angle = mlx->p->rotation_angle - 360;
	if (mlx->p->rotation_angle < 0)
		mlx->p->rotation_angle = 360 + mlx->p->rotation_angle;
}

void	move_player(t_mlx *mlx, int x, int y)
{
	float	fov;
	float	adj;
	float	opp;

	rotate_player(mlx);
	fov = mlx->p->rotation_angle;
	if (mlx->p->side_walk)
		fov += 90;
	adj = (mlx->p->move_speed * cos(convert_to_radian(fov)))
		* mlx->p->walk_direction;
	opp = (mlx->p->move_speed * sin(convert_to_radian(fov)))
		* mlx->p->walk_direction;
	if (!check_walls(mlx, x + adj, y + opp))
	{
		if (!check_walls(mlx, x + adj - 5, y + opp - 5)
			&& !check_walls(mlx, x + adj + 5, y + opp + 5))
		{
			x += adj;
			y += opp;
		}
	}
	mlx->p->x = x;
	mlx->p->y = y;
}
