/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:23:48 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/21 12:00:53 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	diff_symbol(char line, int *inside_map)
{
	if ((*inside_map) && (line != '1' && line != '0' && line != 'N'
			&& line != 'S' && line != 'E' && line != 'W' && line != '\n'
			&& line != ' '))
	{
		printerr(1, "Error: found a different symbol inside map ");
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

int	process(char *line, int *inside,int *column, int *nbr_line)
{
	char	*trimline;

	trimline = ft_strtrim(line, " \t\n");
	if (trimline[0] == '0' || trimline[0] == '1')
		(*inside) = 1;
	if ((*inside) && trimline[0] != '\0')
	{
		if ((int)ft_strlen(line) > *column)
			*column = ft_strlen(line);
		(*nbr_line)++;
	}
	return (*nbr_line);
}

int	nbrs_lines(char *av, int *columns)
{
	int		fd;
	char	*line;
	int		nbr_line;
	int		inside;

	nbr_line = 0;
	inside = 0;
	if (!av)
		return (-1);
	fd = open(av, O_RDONLY, 0777);
	if (fd == -1)
		printerr(1, "Error: Cannot open file");
	line = get_next_line(fd);
	while (line)
	{
		 process(line, &inside,columns, &nbr_line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (nbr_line == 0)
		printerr(1, "Error: No valid map lines found");
	printf(" nbr lines %d\n",*columns);
	return (*columns);
}

int	fill_map(t_map *map, char ***myarr, char *line, t_map_fill *fill_info)
{
	int	j;

	if (!map || !line || !fill_info)
		return (-1);
	if (count_map_lines(line, fill_info->inside_map))
	{
		map->map[*(fill_info->map_index)] = ft_strdup2(line);
		(*myarr)[*(fill_info->map_index)] = ft_strdup2(line);
		j = 0;
		while (map->map[*(fill_info->map_index)][j])
		{
			if (map->map[*(fill_info->map_index)][j] == 'N'
				|| map->map[*(fill_info->map_index)][j] == 'E'
				|| map->map[*(fill_info->map_index)][j] == 'W'
				|| map->map[*(fill_info->map_index)][j] == 'S')
				map->nb_player++;
			j++;
		}
		(*(fill_info->map_index))++;
	}
	return (map->nb_player);
}
