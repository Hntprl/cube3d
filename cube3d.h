/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:51:52 by amarouf           #+#    #+#             */
/*   Updated: 2024/12/23 18:35:31 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_3D
#define CUBE_3D

#include <mlx.h>
#include <X11/X.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
# include <limits.h>
#include <math.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE  1
# endif

#define PI  3.14159265358979323846

typedef struct s_cube
{
    int height;
    int width;
}   t_cube;

typedef struct s_map
{
    char **map;
    int rows;
    int columns;
    int block_size;
}   t_map;

typedef struct s_p
{
    int x;
    int y;
    float rotation_angle;
}   t_p;

typedef struct s_addr
{
    char *pixels;
    int bits_per_pixel;
    int size_line;
    int endian;
    t_p *p;
}   t_addr;

typedef struct s_mlx
{
    void *ptr;
    void *window;
    void *image;
    t_addr *addr;
    t_map *map;
    t_cube *cube;
}   t_mlx;

void rotate_player(t_mlx *mlx);
float convert_to_radian(float angle);
int ft_cube(void *param);
void event_handling(t_mlx *mlx);
int key_hook(int keycode,void *param);
char	*get_next_line(int fd);
char	*ft_editbackup(char *line);
char	*ft_readline(int fd, char *backup, char *rd);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int get_color(int r, int g, int b);
int put_pixel(t_addr *addr, int x, int y, int color);
int destroy_win(void *param);
#endif
