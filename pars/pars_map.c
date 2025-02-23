/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:23:48 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/23 11:31:43 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	diff_symbol(char line, int *inside_map)
{
	if ((*inside_map) && (line != '1' && line != '0' && line != 'N'
			&& line != 'S' && line != 'E' && line != 'W' && line != '\n'
			&& line != ' '))
	{
		printerr(1, " found a different symbol inside map ");
	}
}

int	count_map_lines(char *line, int *inside_map)
{
	int		i;
	char	*trimedline;

	trimedline = ft_strtrim(line, " \t\n");
	i = 0;
	if (*inside_map)
	{
		while (trimedline[i])
		{
			diff_symbol(trimedline[i], inside_map);
			i++;
		}
	}
	if (trimedline[0] == '1' || trimedline[0] == '0')
	{
		*inside_map = 1;
		return (1);
	}
	if (*inside_map)
		*inside_map = 0;
	return (0);
}

int	process_map_lines(int fd, int *columns)
{
	char	*line;
	char	*trimline;
	int		nbr_line;
	int		inside;

	nbr_line = 0;
	inside = 0;
	line = get_next_line(fd);
	while ((line) != NULL)
	{
		trimline = ft_strtrim(line, " \t\n");
		if (trimline[0] == '0' || trimline[0] == '1')
			inside = 1;
		if (inside && trimline[0] != '\0')
		{
			if ((int)ft_strlen(line) > *columns)
				*columns = ft_strlen(line);
			nbr_line++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (nbr_line);
}

int	nbrs_lines(char *av, int *columns)
{
	int	nbr_line;
	int	fd;

	nbr_line = 0;
	*columns = 0;
	fd = open(av, O_RDONLY, 0777);
	if (fd == -1)
		printerr(1, " Cannot open file");
	nbr_line = process_map_lines(fd, columns);
	if (nbr_line == 0)
		printerr(1, " No valid map lines found");
	return (nbr_line);
}

int	fill_map(t_map *map, char ***myarr, char *line, t_map_fill *fill_info)
{
	int	j;

	if (!map || !line || !fill_info)
		return (-1);
	if (count_map_lines(line, &fill_info->inside_map))
	{
		map->map[(fill_info->map_index)] = ft_strdup2(line);
		(*myarr)[(fill_info->map_index)] = ft_strdup2(line);
		j = 0;
		while (map->map[(fill_info->map_index)][j])
		{
			if (map->map[(fill_info->map_index)][j] == 'N'
				|| map->map[(fill_info->map_index)][j] == 'E'
				|| map->map[(fill_info->map_index)][j] == 'W'
				|| map->map[(fill_info->map_index)][j] == 'S')
				map->nb_player++;
			j++;
		}
		((fill_info->map_index))++;
	}
	return (map->nb_player);
}
