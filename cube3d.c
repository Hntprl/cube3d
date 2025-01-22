/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:54:27 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/22 10:12:33 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_cube(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx->image = mlx_new_image(mlx->ptr, WTH, HTH);
	mlx->addr->pixels = mlx_get_data_addr(mlx->image,
											&mlx->addr->bits_per_pixel,
											&mlx->addr->size_line,
											&mlx->addr->endian);
	raycaster(mlx, mlx->p->x, mlx->p->y);
	draw_map(mlx);
	move_player(mlx, mlx->p->x, mlx->p->y);
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
	map = ft_malloc(sizeof(t_map), 'a', false);
	map->rows = 12;
	map->block_size = 40;
	map->columns = 58;
	map->map = ft_malloc(sizeof(char *) * map->rows, 'a', false);
	while (i < map->rows)
	{
		map->map[i] = get_next_line(fd);
		i++;
	}
	close(fd);
	return (map);
}

void	find_player_pos(t_mlx *mlx)
{
	int	x;
	int	y;
	int	i;
	int	j;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	while (i < mlx->map->rows && mlx->map->map[i])
	{
		j = 0;
		x = 0;
		while (j < mlx->map->columns && mlx->map->map[i][j])
		{
			if (mlx->map->map[i][j] == 'N' || mlx->map->map[i][j] == 'S'
				|| mlx->map->map[i][j] == 'E' || mlx->map->map[i][j] == 'W')
			{
				mlx->p->x = x;
				mlx->p->y = y;
				set_player_direction(mlx->map->map[i][j], mlx);
				return ;
			}
			x += mlx->map->block_size;
			j++;
		}
		y += mlx->map->block_size;
		i++;
	}
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
	find_player_pos(&mlx);
	mlx.window = mlx_new_window(mlx.ptr, WTH, HTH, "Map");
	ft_cube(&mlx);
	event_handling(&mlx);
}