#include "cube3d.h"

void is_newline(char *nwline,char *line)
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
	if ((line[0] == 'N' && line[1] == 'O') || 
		(line[0] == 'S' && line[1] == 'O') || 
		(line[0] == 'W' && line[1] == 'E') || 
		(line[0] == 'E' && line[1] == 'A'))
		return (1);
	return (0);
}
int	to_map(int fd, char **myarr, t_map *map)
{
	int		elmant;
	int		i;
	int		pl;
	int		inside_map;
	char	*line;
	char *nwline;
	int map_lines_read=0;

	elmant = 0;
	i = 0;
	pl = 0;
	inside_map = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		nwline=ft_strtrim(line," \t\n");
		if (is_texture_line(nwline))
		{
			fill_textures(map, nwline);
			elmant++;
		}
		else if (nwline[0] == 'F' || nwline[0] == 'C')
		{
			fill_colors(map, nwline);
			elmant++;
		}
		else if ((map_lines_read != map->rows && inside_map) || (nwline[0]=='0' || nwline[0]=='1'))
		{
			is_newline(nwline,line);
            pl = fill_map(map, &myarr, line, &i, &inside_map);
            map_lines_read++;
		}
		else if(nwline[0]!='\0')
			printerr(1,"Error! : invalid content in the file");
		free(nwline);
		free(line);
	}
	if (elmant != 6)
		printerr(1, "Error: The textures and Colors must be in the first");
	return (pl);
}