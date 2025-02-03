/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:54:27 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/26 22:44:10 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	sky_floor(t_mlx *mlx)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < HTH / 2)
	{
		j = 0;
		while (j < WTH)
		{
			put_pixel(mlx->addr, j, i, get_color(0 ,250 ,250));
			j ++;
		}
		i ++;
	}
	while (i < HTH)
	{
		j = 0;
		while (j < WTH)
		{
			put_pixel(mlx->addr, j, i, get_color(70, 44, 44));
			j ++;
		}
		i ++;
	}
}

int	ft_cube(void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx->image = mlx_new_image(mlx->ptr, WTH, HTH);
	mlx->addr->pixels = mlx_get_data_addr(mlx->image,
			&mlx->addr->bits_per_pixel,
			&mlx->addr->size_line,
			&mlx->addr->endian);
	sky_floor(mlx);
	raycaster(mlx, mlx->p->x, mlx->p->y);
	draw_map(mlx);
	move_player(mlx, mlx->p->x, mlx->p->y);
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image, 0, 0);
	mlx_destroy_image(mlx->ptr, mlx->image);
	return (0);
}

t_map	*read_map(char *av)
{
	int		i;
	int		fd;
	char	*line;
	t_map	*map;
	char	**myarr;

	i = 0;
	if (!av)
		return (NULL);
	map = ft_calloc(1, sizeof(t_map));
	init_t_map(&map);
	map->block_size = 40;
	checkpath(av);
	map->rows = nbrs_lines(av, &map->columns);
	myarr = ft_calloc(map->columns, sizeof(char *));
	map->map = ft_calloc(map->rows, sizeof(char *));
	if (!map->map)
	{
		free_map(map);
		free_arg(myarr);
		return (NULL);
	}
	fd = open(av, O_RDONLY, 0777);
	if (fd == -1)
	{
		free_map(map);
		free_arg(myarr);
		return (NULL);
	}
	if (to_map(fd, myarr, map) != 1)
		printerr(1, "Error: the game must have one player ");
	isvalid_map(map, myarr);
	free_arg(myarr);
	close(fd);
	return (map);
}

void	find_player_pos(t_mlx *mlx)
{
	int (x), (y), (i), (j);
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
				return (set_player_direction(mlx->map->map[i][j], mlx));
			}
			x += mlx->map->block_size;
			j++;
		}
		y += mlx->map->block_size;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_cube		cube;
	t_player	p;
	t_mlx		mlx;
	t_addr		addr;
	t_map		*map;

	map = read_map(ft_strdup(av[1]));
	map->columns -= 1;
	mlx.addr = &addr;
	init_data(&mlx, &cube, &p, map);
	find_player_pos(&mlx);
	mlx.window = mlx_new_window(mlx.ptr, WTH, HTH, "Map");
	event_handling(&mlx);
	ft_cube(&mlx);
}
