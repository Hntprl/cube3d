/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:37:22 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/27 14:53:21 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	set_player_direction(char c, t_mlx *mlx)
{
	if (c == 'S')
		mlx->p->rotation_angle = 0;
	if (c == 'W')
		mlx->p->rotation_angle = 180;
	if (c == 'N')
		mlx->p->rotation_angle = 90;
	if (c == 'E')
		mlx->p->rotation_angle = 270;
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

void	wall_slide_bonus(t_mlx *mlx, int *x, int *y, t_trn trn)
{
	if (!check_walls(mlx, *x + trn.adj, *y + trn.opp))
	{
		if (!check_walls(mlx, *x + trn.adj - 5, *y - 5)
			&& !check_walls(mlx, *x + trn.adj + 5, *y + 5))
			*x += trn.adj;
		if (!check_walls(mlx, *x - 5, *y + trn.opp - 5)
			&& !check_walls(mlx, *x + 5, *y + trn.opp + 5))
			*y += trn.opp;
	}
}

void	wall_slide(t_mlx *mlx, int *x, int *y, t_trn trn)
{
	if (!check_walls(mlx, *x + trn.adj, *y + trn.opp))
	{
		if (!check_walls(mlx, *x + trn.adj + 5, *y + trn.opp + 5)
			&& !check_walls(mlx, *x + trn.adj - 5, *y + trn.opp - 5))
		{
			*x += trn.adj;
			*y += trn.opp;
		}
	}
}

void	move_player(t_mlx *mlx, int x, int y)
{
	float	fov;
	t_trn	trn;

	rotate_player(mlx);
	fov = mlx->p->rotation_angle;
	if (mlx->p->side_walk)
		fov += 90;
	trn.adj = (mlx->p->move_speed * cos(convert_to_radian(fov)))
		* mlx->p->walk_direction;
	trn.opp = (mlx->p->move_speed * sin(convert_to_radian(fov)))
		* mlx->p->walk_direction;
	if (mlx->bonus)
		wall_slide_bonus(mlx, &x, &y, trn);
	else
		wall_slide(mlx, &x, &y, trn);
	mlx->p->x = x;
	mlx->p->y = y;
}
