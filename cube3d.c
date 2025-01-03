/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 18:54:27 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/03 17:54:13 by bbenjrai         ###   ########.fr       */
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

t_map *read_map(char *av) {
    int i = 0;
    int fd;
    char *line;
    t_map *map;
	int inside_map=0;
    
    if (!av)
        return NULL;        
    map = malloc(sizeof(t_map));
    if (!map)
        return NULL;
        
    init_t_map(&map);
    if (!map)
        return NULL;
    map->block_size = 40;
	checkpath(av);
    map->rows = nbrs_lines(av,map);
    map->map = calloc(map->rows, sizeof(char *));
    if (!map->map) 
	{
        // free_map(map);
        return NULL;
    }
    
    fd = open(av, O_RDONLY,0777);
	// checkpath(fd,av);
    if (fd == -1) 
	{
        // free_map(map);
        return NULL;
    }
    while ((line = get_next_line(fd)) != NULL)
	{
        if (line[0] == 'N' || line[0] == 'S' || line[0] == 'W' || line[0] == 'E')
            fill_textures(map, line);
        else if (line[0] == 'F' || line[0] == 'C')
            fill_colors(map, line);
        else if (is_maplast(map))
            fill_map(map, line, &i,&inside_map);
            
        map->columns = ft_strlen(line);
        free(line); 
    }
    if(map)
    {
        // check_walls(map->map,map->rows,map->columns);
        check_walls(map->map,map->rows);
    }
    close(fd);
    return map;
}


int main(int ac, char **av) {
    t_cube cube;
    t_player p = {0}; 
    t_mlx mlx = {0};  
    t_addr addr = {0};
    t_map *map;
    
    if (ac != 2) 
	{
        printerr(1, "Error: u should enter just two arguments");
        return 1;
    }
    
    map = read_map(av[1]);
	// printf("line *%s*",map->map[0]);

    mlx.addr = &addr;
    mlx.p = &p;
	p.rotation_angle = 0;
    mlx.map = map;
    mlx.cube = &cube;  
    cube.height = map->rows * map->block_size;
    cube.width = map->columns * map->block_size;
    mlx.ptr = mlx_init();
    mlx.window = mlx_new_window(mlx.ptr, cube.width, cube.height, "Map");
    ft_cube(&mlx);
    event_handling(&mlx);  
}