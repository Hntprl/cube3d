 #include "cube3d.h"
#include <string.h>
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
    char    *trimline;
    int  line_len;

    nbr_line = 0;
    *columns = 0;
    inside = 0;

    fd = open(av, O_RDONLY, 0777);
    if (fd == -1)
        printerr(1, "Error: cannot open file");

    while ((line = get_next_line(fd)) != NULL)
    {
        trimline = ft_strtrim(line, " \t\n");
        if (trimline[0] == '0' || trimline[0] == '1')
            inside = 1;

        if (inside && trimline[0] != '\0')
        {
            line_len = ft_strlen(line);
            if(*columns < line_len) 
                *columns=line_len;
            nbr_line++;
        }
        free(trimline);
        free(line);
    }
    close(fd);

    if (nbr_line == 0)
        printerr(1, "Error: No valid map lines found");
    return nbr_line;
}


int fill_map(t_map *map, char ***myarr, char *line, int *i, int *inside_map)
{
    char *myline=NULL;
    int line_len=0;
    int j=0;
    if (!map || !line || !i || !inside_map)
        return (-1);

    if (count_map_lines(line, inside_map))
    {
        line_len = ft_strlen(line);
        if (line_len > 0 && line[line_len - 1] == '\n')
            line_len--;
        myline = malloc(map->columns + 1);
        if (!myline)
            return (-1);
        ft_strcpy(myline,line);
        j = line_len;
        while (j < map->columns)
        {
            myline[j] = ' ';
            j++;
        }
        myline[map->columns] = '\0';
        map->map[*i] = myline;
        (*myarr)[*i] = ft_strdup(myline);

        j = 0; 
        while (j < map->columns)
        {
            if (myline[j] == 'N' || myline[j] == 'E' 
                || myline[j] == 'W' || myline[j] == 'S')
                map->nb_player++;
            j++;
        }
        (*i)++;
    }
    return (map->nb_player);
}
