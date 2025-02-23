/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:54:27 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/23 10:47:32 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	sky_floor(t_mlx *mlx)
{
	int	i;
	int	j;
	int hth;

	hth = HTH / 2;
	i = -1;
	while (++i < hth)
	{
		j = -1;
		while (++j < WTH)
			put_pixel(mlx->addr, j, i, get_color(mlx->map->fl_color[0]
				, mlx->map->fl_color[1], mlx->map->fl_color[2]));
	}
	while (++i < HTH)
	{
		j = -1;
		while (++j < WTH)
			put_pixel(mlx->addr, j, i, get_color(mlx->map->ce_color[0]
				, mlx->map->ce_color[1], mlx->map->ce_color[2]));
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
	raycaster(mlx);
	draw_map(mlx);
	move_player(mlx, mlx->p->x, mlx->p->y);
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image, 0, 0);
	mlx_destroy_image(mlx->ptr, mlx->image);
	return (0);
}

t_map	*read_map(char *av)
{
	int		fd;
	t_map	*map;
	char	**myarr;
	int pl;

	if (!av)
		return (NULL);
	map = ft_calloc(1, sizeof(t_map));
	init_t_map(&map);
	map->block_size = 40;
	checkpath(av);
	map->rows = nbrs_lines(av, &map->columns);
	myarr = ft_calloc(map->rows, sizeof(char *));
	map->map = ft_calloc(map->rows, sizeof(char *));
	if (!map->map)
		return NULL;
	fd = open(av, O_RDONLY, 0777);
	if (fd == -1)
		return NULL;
	to_map(fd, myarr, map,&pl);
	if (pl != 1)
		printerr(1, " the game must have one player ");
	(isvalid_map(map, myarr), close(fd));	
	return (map);
}

void	find_player_pos(t_mlx *mlx)
{
	t_c	c;

	c.i = 0;
	c.y = 0;
	while (c.i < mlx->map->rows && mlx->map->map[c.i])
	{
		c.j = 0;
		c.x = 0;
		while (c.j < mlx->map->columns && mlx->map->map[c.i][c.j])
		{
			if (mlx->map->map[c.i][c.j] == 'N' || mlx->map->map[c.i][c.j] == 'S'
				|| mlx->map->map[c.i][c.j] == 'E'
				|| mlx->map->map[c.i][c.j] == 'W')
			{
				mlx->p->x = c.x + mlx->map->block_size / 2;
				mlx->p->y = c.y + mlx->map->block_size / 2;
				return (set_player_direction(mlx->map->map[c.i][c.j], mlx));
			}
			c.x += mlx->map->block_size;
			c.j++;
		}
		c.y += mlx->map->block_size;
		c.i++;
	}
}

int	main(int ac, char **av)
{
	t_cube		cube;
	t_player	p;
	t_mlx		mlx;
	t_addr		addr;
	t_map		*map;

	if (ac != 2)
		printerr(1, " invalid number of arguments");
	map = read_map(av[1]);
	map->columns -= 1;
	mlx.addr = &addr;
	init_data(&mlx, &cube, &p, map);
	find_player_pos(&mlx);
	mlx.window = mlx_new_window(mlx.ptr, WTH, HTH, "Map");
	images_to_xpm(&mlx);
	event_handling(&mlx);
}
