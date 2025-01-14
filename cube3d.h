/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:51:52 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/14 17:39:10 by bbenjrai         ###   ########.fr       */
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
#include <stdint.h>
#include <math.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE  1
# endif

#define W   
#define PI  3.14159265358979323846


typedef struct {
    void *allocations[100];
    int count;
} MemoryManager;

typedef struct s_cube
{
    float height;
    float width;
    float wall_line;
}   t_cube;

typedef struct s_ray
{
    float angle;
    float distance;
    float wall_hit_x;
    float wall_hit_y;
    char wall_hit_content;
    int was_hit_vertical;
}   t_ray;

typedef struct s_player
{
    float x;
    float y;
    int turn_direction;
    int walk_direction;
    float rotation_angle;
    float move_speed;
    float rotation_speed;
    int side_walk;
}   t_player;

typedef struct s_map
{
    char **map;
    char *es_img;
    char *we_img;
    char *no_img;
    char *su_img;
    int *fl_color;
    int *ce_color;
    int colors[2];
    int text[4];
    int rows;
    int columns;
    int block_size;
}   t_map;


typedef struct s_addr
{
    char *pixels;
    int bits_per_pixel;
    int size_line;
    int endian;
}   t_addr;

typedef struct s_mlx
{
    void *ptr;
    void *window;
    void *image;
    t_addr *addr;
    t_map *map;
    t_cube *cube;
    t_player *p;
}   t_mlx;

t_map *read_map(char *av);
void move_player(t_mlx *mlx, int x, int y);
void trurn_player(t_mlx *mlx);
void bresenham(t_mlx *mlx, int x, int y, int x2, int y2);
void draw_map(t_mlx *mlx);
void ft_draw_block(t_mlx *mlx, int x, int y, int color);
void set_player_direction(char c, t_mlx *mlx);
void	draw_lines(t_mlx *mlx, int x, int y);
void draw_grid(t_mlx *mlx);
float convert_to_degree(float radian);
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


//parsing 
int	ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
int	countword(char *str, char sep);
void printerr(int status,char *str);
void checkpath(char *av);
int is_validtexture(char **str);
void fill_textures(t_map *map,char *str);
void	spliit(char *str,t_map *map);
void fill_colors(t_map *map,char *str);
int	ft_isdigit(int c);
char	*ft_strtrim(char const *s1, char const *set);
int	ft_isalpha(int c);
int nbrs_lines(char *av,int *columns);
int fill_map(t_map *map,char ***myarr,char *line,int *i,int *inside_map);
void init_t_map(t_map **map);
void free_map(t_map *map);
void	free_arg(char **str);
void	*ft_calloc(size_t count, size_t size);
int	ft_atoi(const char *str);
int	isvalid_map(t_map *map, char **myarr);
void	is_validcolor(char *str);
int	is_space(char str);
int	*min_fill(t_map *map, char *str, int i, int start);
int	to_map(int fd, char **myarr, t_map *map);
#endif
