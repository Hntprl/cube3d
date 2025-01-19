/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:54:27 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/02 01:25:27 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_cube(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx->image = mlx_new_image(mlx->ptr, mlx->cube->width, mlx->cube->height);
	mlx->addr->pixels = mlx_get_data_addr(mlx->image,
			&mlx->addr->bits_per_pixel, &mlx->addr->size_line,
			&mlx->addr->endian);
	// draw_grid(mlx);
	// draw_lines(mlx, mlx->p->x, mlx->p->y);
	// ft_draw_block(mlx, mlx->p->x, mlx->p->y, 3093247);
	move_player(mlx, mlx->p->x, mlx->p->y);
	raycaster(mlx, mlx->p->x, mlx->p->y);
	draw_map(mlx);
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image, 0, 0);
	mlx_destroy_image(mlx->ptr, mlx->image);
	mlx->p->walk_direction = 0;
	mlx->p->side_walk = 0;
	mlx->p->turn_direction = 0;
	return (0);
}

t_map	*read_map(void)
{
	int		fd;
	int		i;
	t_map	*map;

	fd = open("maps/mapp.cub", O_RDONLY, 0777);
	i = 0;
	map = malloc(sizeof(t_map));
	map->rows = 12;
	map->block_size = 40;
	map->columns = 58;
	map->map = malloc(sizeof(char *) * map->rows);
	while (i < map->rows)
	{
		map->map[i] = get_next_line(fd);
		i++;
	}
	return (map);
}

int	main(void)
{
	t_cube cube;
	t_player p;
	t_mlx mlx;
	t_addr addr;
	t_map *map;

	mlx.addr = &addr;
	init_data(&mlx, &cube, &p, map);
	mlx.window = mlx_new_window(mlx.ptr, cube.width, cube.height, "Map");
	ft_cube(&mlx);
	event_handling(&mlx);
}