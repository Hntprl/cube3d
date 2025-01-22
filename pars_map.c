#include "cube3d.h"

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
	char *trimedline;
	trimedline=ft_strtrim(line," \t\n");

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
		free(trimedline);
		return (1);
	}
	 if (*inside_map)
        *inside_map = 0;
	free(trimedline);
	return (0);
}

int nbrs_lines(char *av, int *columns)
{
    int     fd;
    char    *line;
    int     nbr_line;
    int     inside;
	char *trimline;

    nbr_line = 0;
    inside = 0;
    if (!av)
        return (-1);
    fd = open(av, O_RDONLY, 0777);
    if (fd == -1)
        printerr(1, "Error: Cannot open file");
    while ((line = get_next_line(fd)) != NULL)
    {
		trimline=ft_strtrim(line," \t\n");
        if (trimline[0]=='0' || trimline[0]=='1')
			inside=1;
		if(inside && trimline[0]!='\0')
		{
            if (ft_strlen(line) > *columns)
                *columns = ft_strlen(line);
            nbr_line++;
		}
        free(line);
    }
    close(fd);
    if (nbr_line == 0)
        printerr(1, "Error: No valid map lines found");
    return (nbr_line);
}

int	fill_map(t_map *map, char ***myarr, char *line, int *i, int *inside_map)
{
	static int	number_p = 0;
	int			j;

	if (!map || !line || !i || !inside_map)
		return (-1);
	if (count_map_lines(line, inside_map))
	{
		map->map[*i] = ft_strdup(line);
		(*myarr)[*i] = ft_strdup(line);
		j = 0;
		while (map->map[*i][j])
		{
			if (map->map[*i][j] == 'N' || map->map[*i][j] == 'E'
				|| map->map[*i][j] == 'W' || map->map[*i][j] == 'S')
				number_p++;
			j++;
		}
		(*i)++;
	}
	return (number_p);
}
