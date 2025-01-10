/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:51:52 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/08 19:17:48 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_3D_H
# define CUBE_3D_H
# include <X11/X.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define W
# define PI 3.14159265358979323846

typedef struct s_cast
{
	long 	firstx;
	long 	firsty;
	long	xstep;
	long	ystep;
}				t_cast;

typedef struct s_cube
{
	float		height;
	float		width;
	float		wall_line;
}				t_cube;

typedef struct s_ray
{
	float 		ray_angle;
	float		distance;
	float		wall_hit_x;
	float		wall_hit_y;
	int			was_hit_vertical;
	int			was_hit_horizontal;
	int			is_ray_facing_down;
	int			is_ray_facing_up;
	int			is_ray_facing_right;
	int			is_ray_facing_left;
}				t_ray;

typedef struct s_player
{
	float		x;
	float		y;
	int			turn_direction;
	int			walk_direction;
	float		rotation_angle;
	float		move_speed;
	float		rotation_speed;
	int			side_walk;
	float		pov;
}				t_player;

typedef struct s_map
{
	char		**map;
	int			rows;
	int			columns;
	int			block_size;
}				t_map;

typedef struct s_addr
{
	char		*pixels;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_addr;

typedef struct s_mlx
{
	void		*ptr;
	void		*window;
	void		*image;
	t_addr		*addr;
	t_map		*map;
	t_cube		*cube;
	t_player	*p;
	t_ray 		*ray;
}				t_mlx;

int				vertical_raycast(t_mlx *mlx, float gap, int index, t_cast *v_cast);
int				horizontal_raycast(t_mlx *mlx, float gap, int index, t_cast *h_cast);
void			build_rays(t_mlx *mlx, int rays_count);
void			raycaster(t_mlx *mlx, int x, int y);
bool			check_walls(t_mlx *mlx, float x, float y);
void			init_data(t_mlx *mlx, t_cube *cube, t_player *p, t_map *map);
t_map			*read_map(void);
void			move_player(t_mlx *mlx, int x, int y);
void			trurn_player(t_mlx *mlx);
void			bresenham(t_mlx *mlx, int x, int y, int x2, int y2);
void			draw_map(t_mlx *mlx);
void			ft_draw_block(t_mlx *mlx, int x, int y, int color);
void			set_player_direction(char c, t_mlx *mlx);
void			draw_lines(t_mlx *mlx, int x, int y);
void			draw_grid(t_mlx *mlx);
float			convert_to_degree(float radian);
void			rotate_player(t_mlx *mlx);
float			convert_to_radian(float angle);
int				ft_cube(void *param);
void			event_handling(t_mlx *mlx);
int				key_hook(int keycode, void *param);
char			*get_next_line(int fd);
char			*ft_editbackup(char *line);
char			*ft_readline(int fd, char *backup, char *rd);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s1);
size_t			ft_strlen(const char *s);
char			*ft_substr(const char *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
int				get_color(int r, int g, int b);
int				put_pixel(t_addr *addr, int x, int y, int color);
int				destroy_win(void *param);
#endif
