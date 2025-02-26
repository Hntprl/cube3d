/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:51:52 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/26 16:56:45 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <X11/X.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdint.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "parsing.h"

# define TRANSPARENT 0xFF000000
# define TR -16777216
# define SP 180
# define BUFFER_SIZE 1
# define WTH 2000
# define HTH 800
# define PI 3.14159265358979323846

typedef struct s_wall
{
	int	x;
	int	y;
	int	x2;
	int	y2;
}		t_wall;

typedef struct s_garbage
{
	void				*data;
	bool				is_free;
	struct s_garbage	*next;
}						t_garbage;

typedef struct s_cast
{
	double	distance;
	double	xstep;
	double	ystep;
}				t_cast;

typedef struct s_cube
{
	float		height;
	float		width;
}				t_cube;

typedef struct s_ray
{
	double	distance;
	float	ray_angle;
	double	x_hit;
	double	y_hit;
	int		is_ray_facing_down;
	int		is_ray_facing_up;
	int		is_ray_facing_right;
	int		is_ray_facing_left;
	int		was_hit_vertical;
	int		was_hit_horizontal;
}				t_ray;

typedef struct s_player
{
	float	x;
	float	y;
	int		turn_direction;
	int		walk_direction;
	float	rotation_angle;
	float	move_speed;
	float	rotation_speed;
	int		side_walk;
	float	fov;
}				t_player;

typedef struct s_addr
{
	char		*pixels;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_addr;

typedef struct s_texture
{
	char	*xpm;
	int		t_height;
	int		t_width;
	char	*addr;
	int		line_len;
	int		endian;
	int		bpp;
	int		x;
	int		y;
}			t_texture;

typedef struct s_mlx
{
	void		*ptr;
	void		*window;
	void		*image;
	t_addr		*addr;
	t_map		*map;
	t_cube		*cube;
	t_player	*p;
	t_ray		*ray;
	t_texture	texture[5];
}				t_mlx;

typedef struct s_c
{
	int	i;
	int	j;
	int	x;
	int	y;
}				t_c;

void	render_animation(t_mlx *mlx);
void	init_ray_hit(t_ray *ray, int index, t_cast hit);
int		calculate_distance(t_mlx *mlx, int index, t_cast *v, t_cast *h);
void	release_arrows(int keycode, t_mlx *mlx);
int		init_first_inter(t_cast *h_cast, t_cast *v_cast, t_mlx *mlx, int index);
void	draw_wall(t_mlx *mlx, int index);
void	fix_intersection(double *x, double *y, t_mlx *mlx);
void	fix(int *x, int *y);
void	find_ray_direction(float angle, t_ray *ray);
float	fix_rayangle(float angle);
void	*ft_malloc(size_t size, char alloc, bool is_free);
double	ft_distance(double x1, double y1, double x2, double y2);
int		vertical_raycast(t_mlx *mlx, float gap, int index, t_cast *v_cast);
int		horizontal_raycast(t_mlx *mlx, float gap, int index, t_cast *h_cast);
void	build_rays(t_mlx *mlx, int rays_count);
void	raycaster(t_mlx *mlx);
bool	check_walls(t_mlx *mlx, float x, float y);
void	init_data(t_mlx *mlx, t_cube *cube, t_player *p, t_map *map);
t_map	*read_map(char *av);
void	move_player(t_mlx *mlx, int x, int y);
void	draw_map(t_mlx *mlx);
void	ft_draw_block(t_mlx *mlx, int x, int y, int color);
void	set_player_direction(char c, t_mlx *mlx);
float	convert_to_degree(float radian);
void	rotate_player(t_mlx *mlx);
float	convert_to_radian(float angle);
int		ft_cube(void *param);
void	event_handling(t_mlx *mlx);
int		key_hook(int keycode, void *param);
char	*get_next_line(int fd);
char	*ft_editbackup(char *line);
char	*ft_readline(int fd, char *backup, char *rd);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
int		get_color(int r, int g, int b);
int		put_pixel(t_addr *addr, int x, int y, int color);
int		destroy_win(void *param);
char	*ft_itoa(int n);
void	images_to_xpm(t_mlx *wind);
void	rendering_texture(t_mlx *mlx, int index, t_wall wall);
int		mouse_move(int x, int y, t_mlx *mlx);
#endif
