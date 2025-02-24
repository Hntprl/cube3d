/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:16:03 by amarouf           #+#    #+#             */
<<<<<<< HEAD:Bonus/src/key_hook.c
/*   Updated: 2025/02/24 14:38:43 by amarouf          ###   ########.fr       */
=======
/*   Updated: 2025/02/23 13:07:11 by bbenjrai         ###   ########.fr       */
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3:src/key_hook.c
/*                                                                            */
/* ************************************************************************** */

#include "../../cube3d.h"

void	release_arrows(int keycode, t_mlx *mlx)
{
	if (keycode == 65361)
		mlx->p->turn_direction = 0;
	else if (keycode == 65363)
		mlx->p->turn_direction = 0;
}

void	handle_arrows(int keycode, t_mlx *mlx)
{
	if (keycode == 65361)
		mlx->p->turn_direction = -1;
	else if (keycode == 65363)
		mlx->p->turn_direction = +1;
}

int	key_release(int keycode, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (keycode == 'w')
	{
		mlx->p->walk_direction = 0;
	}
	else if (keycode == 's')
	{
		mlx->p->walk_direction = 0;
	}
	else if (keycode == 'a')
	{
		mlx->p->side_walk = 0;
		mlx->p->walk_direction = 0;
	}
	else if (keycode == 'd')
	{
		mlx->p->side_walk = 0;
		mlx->p->walk_direction = 0;
	}
	else
		release_arrows(keycode, mlx);
	return (0);
}

int	key_hook(int keycode, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	if (keycode == 65307)
		destroy_win(param);
	if (keycode == 'w')
		mlx->p->walk_direction = 1;
	if (keycode == 's')
		mlx->p->walk_direction = -1;
	if (keycode == 'a')
	{
		mlx->p->side_walk = 1;
		mlx->p->walk_direction = -1;
	}
	if (keycode == 'd')
	{
		mlx->p->side_walk = 1;
		mlx->p->walk_direction = 1;
	}
	else
		handle_arrows(keycode, mlx);
	return (0);
}
<<<<<<< HEAD:Bonus/src/key_hook.c
=======

int mouse_move( int x, int y, t_mlx *mlx)
{
	static int	last_x ;
	
	mlx_mouse_get_pos(mlx->ptr,mlx->window, &x, &y);
	(void)y;
	if(x > last_x)
		mlx->p->turn_direction = (x - last_x) / 2 ;
	else if(x < last_x )
		mlx->p->turn_direction = (x - last_x) / 2 ;
	last_x = x;
	return(0);
}
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3:src/key_hook.c

void	event_handling(t_mlx *mlx)
{
	mlx_hook(mlx->window, 2, 1L << 0, key_hook, mlx);
	mlx_hook(mlx->window, 3, 1L << 1, key_release, mlx);
<<<<<<< HEAD:Bonus/src/key_hook.c
	mlx_hook(mlx->window, 6, 1L << 6, mouse_move, mlx);
=======
	mlx_hook(mlx->window,6,1L << 6,mouse_move,mlx);//bonus mouses  
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3:src/key_hook.c
	mlx_loop_hook(mlx->ptr, ft_cube, mlx);
	mlx_hook(mlx->window, 17, 0, destroy_win, mlx);
	mlx_loop(mlx->ptr);
}
