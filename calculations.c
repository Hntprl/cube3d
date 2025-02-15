/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:26:16 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/05 18:31:30 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

  #include "cube3d.h"

float	convert_to_radian(float angle)
{
	return (angle * (PI / 180));
}

float	convert_to_degree(float radian)
{
	return (radian * (180 / PI));
}

// bool check_walls(t_mlx *mlx, float x, float y)
// {
//     // Debug prints to see values when crash occurs
//     // printf("x: %f, y: %f\n", x, y);
//     // printf("block_size: %d\n", mlx->map->block_size);
//     // printf("rows: %d, columns: %d\n", mlx->map->rows, mlx->map->columns);

//     // Calculate map coordinates
//     int map_y = (int)y / mlx->map->block_size;
//     int map_x = (int)x / mlx->map->block_size;
    
//     // printf("map_x: %d, map_y: %d\n", map_x, map_y);

//     // Boundary checks
//     if (map_y < 0 || map_x < 0)
//         return true;
//     if (map_y >= mlx->map->rows)
//         return true;
    
//     // Check string length before accessing
//     size_t line_len = ft_strlen(mlx->map->map[map_y]);
//     if (map_x >= (int)line_len)
//         return true;

//     return (mlx->map->map[map_y][map_x] == '1');
// }

bool	check_walls(t_mlx *mlx, float x, float y)
{
	if (x < 0 || x >= mlx->cube->width || y < 0 || y >= mlx->cube->height)
		return (true);
	if (mlx->map->map[(int)((y / mlx->map->block_size))][(int)(x
			/ mlx->map->block_size)] == '1')
		return (true);
	return (false);
}

double	ft_distance(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
