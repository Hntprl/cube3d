/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:34:06 by bbenjrai          #+#    #+#             */
/*   Updated: 2025/02/22 10:26:52 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void images_to_xpm(t_mlx *wind)
{
    char *directs[5];
    int i = 0;
    
    directs[0] = wind->map->no_img;
    directs[1] = wind->map->su_img;
    directs[2] = wind->map->es_img;
    directs[3] = wind->map->we_img;
    
    i = 0;
    while(i < 4)
    {
        wind->texture[i].xpm = mlx_xpm_file_to_image(wind->ptr, directs[i],
            &wind->texture[i].t_width,   
            &wind->texture[i].t_height); 
        if(!wind->texture[i].xpm)
            printerr(1, "ERROR LOADING TEXTURE");
        wind->texture[i].addr = mlx_get_data_addr(wind->texture[i].xpm,
            &wind->texture[i].bpp,
            &wind->texture[i].line_len,
            &wind->texture[i].endian);
        i++;
    }
}

int get_wall_orientation(t_mlx *mlx,int index)
{
    if (mlx->ray[index].was_hit_horizontal)
    {
        if(mlx->ray[index].is_ray_facing_up)
            return 0;
        else    
            return 1;
    }
    else if(mlx->ray[index].was_hit_vertical)
    {
        if(mlx->ray[index].is_ray_facing_right)
            return 2;
        else
            return 3;
    }
    return 0;
}

int get_text_x(int index,t_mlx *mlx,int d)
{
    double wallX;
    int texture_x;
    
      if (mlx->ray[index].was_hit_vertical) {
        wallX = mlx->ray[index].y_hit;
    } else {
        wallX = mlx->ray[index].x_hit;
    }
    wallX = fmod(wallX, mlx->map->block_size);// normaliser à la taille du bloc (scaling)
    texture_x = (int)((wallX * mlx->texture[d].t_width) / mlx->map->block_size);
    return texture_x;
}

void rendering_texture(t_mlx *mlx, int index, t_wall wall)
{
    double wall_height = wall.y2 - wall.y;
    int d = get_wall_orientation(mlx, index);
    int texture_x;
    int texture_y;
    double texture_pos;

    texture_x=get_text_x(index,mlx,d);
    while (wall.y < wall.y2)
    {
        // simple modulo operation to keep texture_y within bounds
        texture_pos=wall.y + (wall_height/2)- (HTH/2);
         texture_y = ((int)texture_pos) * (mlx->texture[d].t_height/wall_height);  
        int offset = (texture_y * mlx->texture[d].line_len) + 
                    (texture_x * (mlx->texture[d].bpp / 8));
        if (wall.y >= 0 && wall.y < HTH 
        && texture_x >= 0 && texture_x < mlx->texture[d].t_width &&
            texture_y >= 0 && texture_y < mlx->texture[d].t_height)
        {
            int color = *(int *)(mlx->texture[d].addr + offset);
            put_pixel(mlx->addr, wall.x, wall.y, color);
        }
        wall.y++;
    }
}
