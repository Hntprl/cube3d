/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:39:02 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/04 14:22:25 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "cube3d.h"


void	ft_draw_block(t_mlx *mlx, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mlx->map->block_size * mlx->map->minimap_scale)
	{
		j = 0;
		while (j < mlx->map->block_size * mlx->map->minimap_scale)
		{
			put_pixel(mlx->addr, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	minimap_player(t_mlx *mlx)
{
	// t_wall wall;
	// float line_size;

	// line_size = 5;
	// wall.x = mlx->p->x * mlx->map->minimap_scale;
	// wall.y = mlx->p->y * mlx->map->minimap_scale;
	// wall.x2 = wall.x + cos(convert_to_radian(mlx->p->pov)) * line_size;
	// wall.y2 = wall.y + sin(convert_to_radian(mlx->p->pov)) * line_size;
	ft_draw_block(mlx, mlx->p->x * mlx->map->minimap_scale, mlx->p->y
			* mlx->map->minimap_scale, 16711680);
	// bresenham(mlx, wall);
}

void	draw_map(t_mlx *mlx)
{
	// int flag;
	int			i;
	int			j;
	int			x;
	int			y;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	// flag = 0;
	while (i < mlx->map->rows && mlx->map->map[i])
	{
		j = 0;
		x = 0;
		while (j < mlx->map->columns && mlx->map->map[i][j])
		{
			if (mlx->map->map[i][j] == '0' || mlx->map->map[i][j] == 'W' || mlx->map->map[i][j] == 'N'
				|| mlx->map->map[i][j] == 'S' || mlx->map->map[i][j] == 'E')
				ft_draw_block(mlx, x, y, get_color(0 ,0 ,255));
			if (mlx->map->map[i][j] == '1')
				ft_draw_block(mlx, x, y, 16777215);
			minimap_player(mlx);
			x += mlx->map->block_size * mlx->map->minimap_scale;
			j++;
		}
		y += mlx->map->block_size * mlx->map->minimap_scale;
		i++;
	}
}
// void update_texture_pixel(t_mlx *mlx,int index,double wall_height)
// {
// double wall_x = (mlx->ray->was_hit_vertical) ? mlx->ray->y_hit : mlx->ray->x_hit;
// wall_x -= floor(wall_x);


// int tex_x = (int)(wall_x * (double)mlx->texture->t_width);
// if ((mlx->ray->was_hit_vertical && mlx->ray->is_ray_facing_left) || 
//     (!mlx->ray->was_hit_vertical && mlx->ray->is_ray_facing_up))
//     tex_x = mlx->texture->t_width - tex_x - 1;

// int draw_start=0;
// double step = 1.0 * mlx->texture->t_height / wall_height;
// double tex_pos = (draw_start - WTH / 2 + wall_height / 2) * step;
// int x=0;
// for (int y = draw_start; y < wall_height; y++) {
//     int tex_y = (int)tex_pos & (mlx->texture->t_height - 1);
//     tex_pos += step;
//     int color = *(int *)(mlx->addr->addr_e + (tex_y * mlx->addr->e_size_line) + (tex_x * mlx->addr->e_bits_per_pixel / 8));
    
//     put_pixel(mlx->addr, x, y, color);
// }

// }


void	init_data(t_mlx *mlx, t_cube *cube, t_player *p, t_map *map, char *av)
{
	mlx->ptr = mlx_init();
	map = read_map(av);
	cube->height = map->rows * map->block_size;
	cube->width = map->columns * map->block_size;
	cube->wall_line = 1;
	p->turn_direction = 0;
	p->walk_direction = 0;
	p->rotation_angle = 0;
	p->move_speed = 10;
	p->rotation_speed = 5;
	p->side_walk = 0;
	p->pov = 90;
	mlx->map = map;
	mlx->cube = cube;
	mlx->p = p;
	mlx->map->minimap_scale = 0.2;
}
