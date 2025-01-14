/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:54:27 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/14 17:24:27 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	raycast_line(t_mlx *mlx, int x, int y, char flag, float pov)
{
	float	adj;
	float	opp;

	if (flag == '-')
	{
		adj = 100 * cos(convert_to_radian(mlx->p->rotation_angle - pov));
		opp = 100 * sin(convert_to_radian(mlx->p->rotation_angle - pov));
	}
	else
	{
		adj = 100 * cos(convert_to_radian(mlx->p->rotation_angle + pov));
		opp = 100 * sin(convert_to_radian(mlx->p->rotation_angle + pov));
	}
	bresenham(mlx, x, y, x + adj, y + opp);
}

void	raycaster(t_mlx *mlx, int x, int y)
{
	float	pov;
	float	gap;

	mlx->cube->wall_line = 3;
	pov = 90 / 2;
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
	t_mlx	*mlx;

	mlx = (t_mlx *)param;
	mlx->image = mlx_new_image(mlx->ptr, mlx->cube->width, mlx->cube->height);
	mlx->addr->pixels = mlx_get_data_addr(mlx->image,
			&mlx->addr->bits_per_pixel, &mlx->addr->size_line,
			&mlx->addr->endian);
	draw_map(mlx);
	draw_grid(mlx);
	draw_lines(mlx, mlx->p->x, mlx->p->y);
	ft_draw_block(mlx, mlx->p->x, mlx->p->y, 3093247);
	move_player(mlx, mlx->p->x, mlx->p->y);
	raycaster(mlx, mlx->p->x, mlx->p->y);
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->image, 0, 0);
	mlx_destroy_image(mlx->ptr, mlx->image);
	mlx->p->walk_direction = 0;
	mlx->p->side_walk = 0;
	mlx->p->turn_direction = 0;
	return (0);
}


// if (!myarr)
// {
//     // free_map(map);
//     free_arg(myarr);
//     return (NULL);
// }
// map ;
// if (!map)
//     return (NULL);
// int is_map(char *line)
// {
// 	char *trimed;
// 	trimed=line
// }
int	to_map(int fd, char **myarr, t_map *map)
{
	int		elmant;
	int		i;
	int		pl;
	int		inside_map;
	char	*line;
	char *nwline;
	int map_lines_read=0;

	elmant = 0;
	i = 0;
	pl = 0;
	inside_map = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		nwline=ft_strtrim(line," \t\n");
		if (((nwline[0] == 'N' && nwline[1] == 'O') || (nwline[0] == 'S'
					&& nwline[1] == 'O') || (nwline[0] == 'W' && nwline[1] == 'E')
				|| (nwline[0] == 'E' && nwline[1] == 'A')))
		{
			fill_textures(map, nwline);
			elmant++;
		}
		else if (nwline[0] == 'F' || nwline[0] == 'C')
		{
			fill_colors(map, nwline);
			elmant++;
		}
		else if ((map_lines_read != map->rows && inside_map) || (nwline[0]=='0' || nwline[0]=='1'))
		{
			if (nwline[0] == '\0')
            {
                free(nwline);
                free(line);
                printerr(1, "Error: Empty line inside map");
            }
             inside_map = 1;
            pl = fill_map(map, &myarr, line, &i, &inside_map);
            map_lines_read++;
		}
		else if(nwline[0]!='\0')
			printerr(1,"Error! : invalid content in the file");
		free(nwline);
		free(line);
	}
	if (elmant != 6)
		printerr(1, "Error: The textures and Colors must be in the first");
	return (pl);
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

int	main(int ac, char **av)
{
	t_cube cube;
	t_player p = {0};
	t_mlx mlx = {0};
	t_addr addr = {0};
	t_map *map;

	if (ac != 2)
	{
		printerr(1, "Error: u must enter the map file");
		return (1);
	}
	map = read_map(av[1]);
	mlx.addr = &addr;
	mlx.p = &p;
	p.rotation_angle = 0;
	mlx.map = map;
	mlx.cube = &cube;
	cube.height = map->rows * map->block_size ;
	cube.width = map->columns * map->block_size;
	mlx.ptr = mlx_init();
	mlx.window = mlx_new_window(mlx.ptr, cube.width, cube.height, "Map");
	ft_cube(&mlx);
	event_handling(&mlx);
}