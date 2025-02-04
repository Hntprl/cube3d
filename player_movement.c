/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:37:22 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/04 13:39:23 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "cube3d.h"

void	set_player_direction(char c, t_mlx *mlx)
{
	if (c == 'N')
		mlx->p->rotation_angle = 0;
	if (c == 'S')
		mlx->p->rotation_angle = 180;
	if (c == 'E')
		mlx->p->rotation_angle = 90;
	if (c == 'W')
		mlx->p->rotation_angle = 270;
}

void	rotate_player(t_mlx *mlx)
{
	mlx->p->rotation_speed = 5;
	mlx->p->rotation_angle += mlx->p->turn_direction * mlx->p->rotation_speed;
	if (mlx->p->rotation_angle > 360)
		mlx->p->rotation_angle = mlx->p->rotation_angle - 360;
	if (mlx->p->rotation_angle < 0)
		mlx->p->rotation_angle = 360 + mlx->p->rotation_angle;
}

void	move_player(t_mlx *mlx, int x, int y)
{
	float	pov;
	float	adj;
	float	opp;

	rotate_player(mlx);
	pov = mlx->p->rotation_angle;
	if (mlx->p->side_walk)
		pov += 90;
	adj = 10 * cos(convert_to_radian(pov));
	opp = 10 * sin(convert_to_radian(pov));
	if (check_walls(mlx, x + adj * mlx->p->walk_direction, y + opp * mlx->p->walk_direction) == false)
	{
		x += adj * mlx->p->walk_direction;
		y += opp * mlx->p->walk_direction;
	}
	mlx->p->x = x;
	mlx->p->y = y;
}
