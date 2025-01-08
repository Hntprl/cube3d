#include "cube3d.h"

int count_map_lines(char *line,int *inside_map)
{
    int i = 0;
    t_map *mp;
    
	if(*inside_map && (ft_strcmp(line, "\n") == 0))//mp->rows!=12
        printerr(1,"Error: The map contains a newline ");
	while (line[i]) 
	{
        if ((*inside_map) && (line[i] != '1' && line[i] != '0' && 
            line[i] != 'N' && line[i] != 'S' && 
            line[i] != 'E' && line[i] != 'W' && 
            line[i] != '\n' && line[i] != ' '))
		{
            printerr(1,"Error: found a different symbol inside map ");
		}  
        i++;
    }
	if((line[0] == '1' || line[0] == '0') )
		*inside_map=1;
    return (line[0] == '1' || line[0] == '0');
}

int nbrs_lines(char *av,int *columns) 
{
    int fd;
    char *line;
    int nbr_line = 0;
	int inside=0;
    
    if (!av)
        return -1;
    fd = open(av, O_RDONLY,0777);
    if (fd == -1) 
        printerr(1, "Error: Cannot open file");
    while ((line = get_next_line(fd)) != NULL) 
	{
        if (count_map_lines(line,&inside))
        {
            if(ft_strlen(line)>*columns)
                *columns=ft_strlen(line);
            nbr_line++;
        }
        free(line);
    }
    close(fd); 
    if (nbr_line == 0)
        printerr(1, "Error: No valid map lines found");
    return nbr_line;
}

int is_maplast(t_map *map)
{
	if(map && map->ce_color==NULL && map->fl_color==NULL && map->no_img==NULL && map->es_img==NULL && map->we_img==0 && map->su_img==0)
		return 0;
	return 1;
}

int fill_map(t_map *map,char ***myarr, char *line, int *i,int *inside_map)
{
   static int number_p=0;
    if (!map || !line || !i || !inside_map)
        return -1;
    if (count_map_lines(line,inside_map)) 
	{
        map->map[*i] = ft_strdup(line);
        (*myarr)[*i]=ft_strdup(line);
        int j=0;
        while(map->map[*i][j])
        {
            if(map->map[*i][j]== 'N' || map->map[*i][j]== 'E' || map->map[*i][j]== 'W' || map->map[*i][j]== 'S')
                number_p++;           
            j++;
        }
        (*i)++;
    }
    return (number_p);
}

// Parse and Identify Sections:

// Locate the map as the last section of the file.
// Handle and ignore empty lines where applicable.
// Verify Map Characters:

// Check that the map contains only the valid characters (0, 1, N, S, E, W).
// Validate Surrounding Walls:

// Ensure all rows at the edges (top and bottom) are filled with 1.
// Ensure all columns at the edges (leftmost and rightmost) are filled with 1.
// Check Player Start Position:

// Confirm there is exactly one player start position (N, S, E, W).
// More or fewer starting positions would make the map invalid.
// Handle Empty Spaces:

// Ensure no 0 appears outside of the map bounds or leads to an unclosed area.
