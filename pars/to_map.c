/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:30:03 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/21 11:49:11 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	is_newline(char *nwline, char *line)
{
	if (nwline[0] == '\0')
	{
		free(line);
		printerr(1, "Error: Empty line inside map");
	}
}

int	is_texture_line(const char *line)
{
	if (!line)
		return (0);
	if ((line[0] == 'N' && line[1] == 'O') || (line[0] == 'S' && line[1] == 'O')
		|| (line[0] == 'W' && line[1] == 'E') || (line[0] == 'E'
			&& line[1] == 'A'))
		return (1);
	return (0);
}

void	my_init(int *map_lines_read, int *element, int integer[2])
{
	integer[0] = 0;
	integer[1] = 0;
	(*element) = 0;
	(*map_lines_read) = 0;
}

void	fill_texture_color(char *nwline, t_map *map, int *element)
{
	if (is_texture_line(nwline))
	{
		fill_textures(map, nwline);
		(*element)++;
	}
	else if (nwline[0] == 'F' || nwline[0] == 'C')
	{
		fill_colors(map, nwline);
		(*element)++;
	}
	else if (nwline[0] != '\0' && nwline[0] != '0' && nwline[0] != '1')
	{
		printerr(1, "Error! : invalid content in the file");
	}
}

void	process_map_line(char *line, t_map *map, t_map_fill *fill_info,
		char **myarr)
{
	char	*nwline;

	nwline = ft_strtrim(line, " \t\n");
	if (nwline[0] != '0' && nwline[0] != '1')
		fill_texture_color(nwline, map, &fill_info->element);
	else if ((fill_info->map_lines_read != map->rows
			&& *(fill_info->inside_map)) || (nwline[0] == '0'
			|| nwline[0] == '1'))
	{
		is_newline(nwline, line);
		(fill_info->player_count) = fill_map(map, &myarr, line, fill_info);
		(fill_info->map_lines_read)++;
	}
}

void	to_map(int fd, char **myarr, t_map *map, int *pl)
{
	int			map_lines_read;
	int			integer[2];
	int			element;
	char		*line;
	t_map_fill	fill_info;

	my_init(&map_lines_read, &element, integer);
	fill_info.map_index = &(integer[0]);
	fill_info.inside_map = &(integer[1]);
	fill_info.element = element;
	fill_info.map_lines_read = map_lines_read;
	line = get_next_line(fd);
	while ((line))
	{
		process_map_line(line, map, &fill_info, myarr);
		free(line);
		line = get_next_line(fd);
	}
	(*pl) = fill_info.player_count;
	if (fill_info.element != 6)
		printerr(1, "Error: The textures and Colors must be set in the first");
}
