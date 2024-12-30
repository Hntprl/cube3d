/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:54:27 by amarouf           #+#    #+#             */
/*   Updated: 2024/12/30 18:46:26 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void raycast_line(t_mlx *mlx, int x, int y, char flag, float pov)
{
	float adj;
	float opp;
	
	if (flag == '-')
	{
		adj	= 100 * cos(convert_to_radian(mlx->p->rotation_angle - pov));
	 	opp	= 100 * sin(convert_to_radian(mlx->p->rotation_angle - pov));
	}
	else
	{
		adj = 100 * cos(convert_to_radian(mlx->p->rotation_angle + pov));
		opp = 100 * sin(convert_to_radian(mlx->p->rotation_angle + pov));
	}
	bresenham(mlx, x, y, x + adj, y + opp);
}

void raycaster(t_mlx *mlx, int x, int y)
{
	mlx->cube->wall_line = 3;
	float pov = 90 / 2;
	float gap;

	gap = 0;
	while (gap < pov)
	{
		raycast_line(mlx, x, y, '+', gap);
		raycast_line(mlx, x, y, '-', gap);
		gap += pov / (mlx->cube->width / mlx->cube->wall_line);
	}	
}

int	ft_cube(void *param)
{
	t_mlx *mlx = (t_mlx *)param;
	
	mlx->image =  mlx_new_image(mlx->ptr, mlx->cube->width, mlx->cube->height);
	mlx->addr->pixels = mlx_get_data_addr(mlx->image, &mlx->addr->bits_per_pixel
	, &mlx->addr->size_line, &mlx->addr->endian); 
	draw_map(mlx);
	draw_grid(mlx);
	draw_lines(mlx, mlx->p->x, mlx->p->y);
	ft_draw_block(mlx, mlx->p->x, mlx->p->y, 3093247);
	move_player(mlx, mlx->p->x, mlx->p->y);
	raycaster(mlx, mlx->p->x, mlx->p->y);
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image, 0, 0);
	mlx_destroy_image ( mlx->ptr, mlx->image );
	mlx->p->walk_direction = 0;
	mlx->p->side_walk = 0;
	mlx->p->turn_direction = 0;
	return (0);
}

t_map *read_map(void)
{
	int fd = open("maps/mapp.cub", O_RDONLY, 0777);
	int i = 0;
	t_map *map = malloc(sizeof(t_map));
	map->rows = 12;
	map->block_size = 40;
	map->columns = 58;
	map->map = malloc(sizeof(char *) * map->rows);
	while (i < map->rows)
	{
		map->map[i] = get_next_line(fd);
		i ++;
	}
	return (map);
}

int main ()
{
	t_cube cube;
	t_player p;
	t_mlx mlx;
	t_addr addr;
	t_map *map;
	
	mlx.addr = &addr;
	mlx.p = &p;
	p.walk_direction = 0;
	p.turn_direction = 0;
	p.side_walk = 0;
	map = read_map();
	cube.height = map->rows * map->block_size;
	cube.width = map->columns * map->block_size;
	mlx.map = map;
	mlx.cube = &cube;
	mlx.ptr = mlx_init();
	mlx.window =  mlx_new_window(mlx.ptr, cube.width, cube.height, "Map");
	ft_cube(&mlx);
	event_handling(&mlx);
}