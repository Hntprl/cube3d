/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:51:52 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/02 17:46:34 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_3D_H
# define CUBE_3D_H
# include <X11/X.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# define BUFFER_SIZE 1
# define WTH 2000
# define HTH 1000
# define W
# define PI 3.14159265358979323846

// typedef	struct 
// {
//     void	*allocations[100];
//     int		count;
// }			MemoryManager;

typedef struct s_bnham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	e2;
}				t_bnham;

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
	float		wall_line;
}				t_cube;

typedef struct s_ray
{
	double	distance;
	float	ray_angle;
	float	x_hit;
	float	y_hit;
	int		was_hit_vertical;
	int		was_hit_horizontal;
	int		is_ray_facing_down;
	int		is_ray_facing_up;
	int		is_ray_facing_right;
	int		is_ray_facing_left;
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
	float	pov;
}				t_player;

typedef struct s_map
{
	char	**map;
	char	*es_img;
	char	*we_img;
	char	*no_img;
	char	*su_img;
	int		*fl_color;
	int		*ce_color;
	int		colors[2];
	int		text[4];
	int		rows;
	float	minimap_scale;
	int		columns;
	int		block_size;
	int nb_player;
}			t_map;

typedef struct s_addr
{
	char		*pixels;
	int			bits_per_pixel;
	int			size_line;
	int			endian;

	char		*addr_w;
	int			w_bits_per_pixel;
	int			w_size_line;
	int			w_endian;

	char		*addr_e;
	int			e_bits_per_pixel;
	int			e_size_line;
	int			e_endian;

	char		*addr_n;
	int			n_bits_per_pixel;
	int			n_size_line;
	int			n_endian;

	char		*addr_s;
	int			s_bits_per_pixel;
	int			s_size_line;
	int			s_endian;

}				t_addr;

typedef struct s_texture
{
	int t_height;
	int t_width;
	char		*n_xpm;
	char		*s_xpm;
	char		*e_xpm;
	char		*w_xpm;
	t_addr	address;
	int x;
	int y;
	
}			t_texture;
typedef struct s_mlx
{
	void		*ptr;
	void		*window;
	void		*image;
	t_addr		*addr;
	t_map		*map;
	t_cube		*cube;
	t_texture	texture[5];
	t_player	*p;
	t_ray		*ray;
}					t_mlx;

void	init_first_inter(t_cast *h_cast, t_cast *v_cast, t_mlx *mlx, int index);
void	draw_wall(t_mlx *mlx, int index);
void	fix_intersection(double *x, double *y, t_mlx *mlx);
void	fix(int *x, int *y, t_mlx *mlx);
void	find_ray_direction(float angle, t_ray *ray);
float	fix_rayangle(float angle);
void	*ft_malloc(size_t size, char alloc, bool is_free);
double	ft_distance(float x1, float y1, float x2, float y2);
int		vertical_raycast(t_mlx *mlx, float gap, int index, t_cast *v_cast);
int		horizontal_raycast(t_mlx *mlx, float gap, int index, t_cast *h_cast);
void	build_rays(t_mlx *mlx, int rays_count);
void	raycaster(t_mlx *mlx, int x, int y);
bool	check_walls(t_mlx *mlx, float x, float y);
void	init_data(t_mlx *mlx, t_cube *cube, t_player *p, t_map *map, char *av);
t_map	*read_map(char *av);
void	move_player(t_mlx *mlx, int x, int y);
void	trurn_player(t_mlx *mlx);
void	bresenham(t_mlx *mlx, t_wall wall,int texture_index);
void	draw_map(t_mlx *mlx);
void	ft_draw_block(t_mlx *mlx, int x, int y, int color);
void	set_player_direction(char c, t_mlx *mlx);
void	draw_lines(t_mlx *mlx, int x, int y);
void	draw_grid(t_mlx *mlx);
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



void	images_to_xpm(t_mlx *wind);
// parsing functions
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *s, char c);
int		countword(char *str, char sep);
void	printerr(int status, char *str);
void	checkpath(char *av);
int		is_validtexture(char **str);
void	fill_textures(t_map *map, char *str);
void	spliit(char *str, t_map *map);
void	fill_colors(t_map *map, char *str);
int		ft_isdigit(int c);
char	*ft_strtrim(char const *s1, char const *set);
int		ft_isalpha(int c);
int		nbrs_lines(char *av, int *columns);
int		fill_map(t_map *map, char ***myarr, char *line, int *i, int *inside_map);
void	init_t_map(t_map **map);
void	free_map(t_map *map);
void	free_arg(char **str);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
int		isvalid_map(t_map *map, char **myarr);
void	is_validcolor(char *str);
int		is_space(char str);
int		*min_fill(t_map *map, char *str, int i, int start);
int		to_map(int fd, char **myarr, t_map *map);



#endif
