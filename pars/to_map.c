/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:30:03 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/21 00:11:12 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	is_newline(char *nwline, char *line)
{
	if (nwline[0] == '\0')
	{
		free(nwline);
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

void	my_init(int *map_lines_read, int *inside_map, int *integer)
{
	integer[0] = 0;
	integer[1] = 0;
	(*map_lines_read) = 0;
	(*inside_map) = 0;
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

void	to_map(int fd, char **myarr, t_map *map, int *pl)
{
	int			map_lines_read;
	int			integer[2];
	int			inside_map;
	char		*line;
	char		*nwline;
	t_map_fill	fill_info;

	my_init(&map_lines_read, &inside_map, integer);
	fill_info.map_index = &(integer[0]);
	fill_info.inside_map = &inside_map;
	line = get_next_line(fd);
	while (line)
	{
		nwline = ft_strtrim(line, " \t\n");
		if (nwline[0] != '0' && nwline[0] != '1')
			fill_texture_color(nwline, map, &integer[1]);
		else if ((map_lines_read != map->rows && inside_map)
			|| (nwline[0] == '0' || nwline[0] == '1'))
		{
			is_newline(nwline, line);
			(*pl) = fill_map(map, &myarr, line, &fill_info);
			map_lines_read++;
		}
		(free(nwline), free(line));
		line = get_next_line(fd);
	}
	if ((integer[1]) != 6)
		printerr(1, "Error: The textures and Colors must be in the first");
}
