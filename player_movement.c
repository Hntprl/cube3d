/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:37:22 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/02 09:53:16 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void set_player_direction(char c, t_mlx *mlx)
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

void trurn_player(t_mlx *mlx)
{
	mlx->p->rotation_speed = 5;
	mlx->p->rotation_angle += mlx->p->turn_direction * mlx->p->rotation_speed;
}

void move_player(t_mlx *mlx, int x, int y)
{
	  if (!mlx || !mlx->p || !mlx->map || !mlx->map->map)
        return ;
	trurn_player(mlx);
	float pov = mlx->p->rotation_angle;
	if (mlx->p->side_walk == 1)
		pov-= 90;
	float adj = 10 * cos(convert_to_radian(pov));
	float opp = 10 * sin(convert_to_radian(pov));
	
    if (mlx->map->map[(int)(y + opp * mlx->p->walk_direction) / mlx->map->block_size][(int)(x + adj * mlx->p->walk_direction) / mlx->map->block_size] != '1')
    {
        x += adj * mlx->p->walk_direction;
        y += opp * mlx->p->walk_direction;
    }
	mlx->p->x = x;
	mlx->p->y = y;
}
