/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 18:09:44 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/23 11:30:05 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_map
{
	char	**map;
	char	*es_img;
	char	*we_img;
	char	*no_img;
	char	*su_img;
	int		*fl_color;
	int		*ce_color;
	int		ce_index;   
    int		fl_index; 
	int		colors[2];
	int		text[4];
	int		rows;
	float	minimap_scale;
	int		columns;
	int		block_size;
	int		nb_player;
}			t_map;

typedef struct s_map_fill {
    int map_index;        
    int inside_map;      
    int player_count;      
	int			element;
	int			map_lines_read;
} t_map_fill;

int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char *s, char c);
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
int fill_map(t_map *map, char ***myarr, char *line, t_map_fill *fill_info);
void	init_t_map(t_map **map);
void	free_map(t_map *map);
void	free_arg(char **str);
void	*ft_calloc(size_t count, size_t size);
int		ft_atoi(const char *str);
int		isvalid_map(t_map *map, char **myarr);
void	is_validcolor(char *str);
int		is_space(char str);
int		*min_fill(t_map *map, char *str, int i, int start);
void		to_map(int fd, char **myarr, t_map *map,int *pl);
char	*ft_strdup2(const char *s1);
int	isnot_alpha(char *str);
void	is_newline(char *line,t_map_fill *fill_info,int rows);




#endif