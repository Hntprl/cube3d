#include "cube3d.h"

int check_walls(char **map,int rows)
{
    int i=0;
    int j;
    while(map[i])
        {
            j=0;
            while (map[i][j])
            {
                if(map[0][j]!=1)
                    printerr(1,"Error : Top row not surrounded by walls");
                if(map[rows][j]!=1)
                    printerr(1,"Error : Bottom row not surrounded by walls");
                j++;        
            }
            i++;
            
        }
}
// int check_walls(char **map, int rows, int columns)
// {
//     int i;
//     // Check top row
//     i = 0;
//     while( i < columns )
//     {
//         if (map[0][i] != '1') {
//             fprintf(stderr, "Error: Top row is not surrounded by '1'.\n");
//             return 0;
//         }
//         i++;
//     }
//     i = 0;
//     // Check bottom row
//     while(i < columns) 
//     {
//         if (map[rows - 1][i] != '1') {
//             fprintf(stderr, "Error: Bottom row is not surrounded by '1'.\n");
//             return 0;
//         }
//         i++;
//     }
//     i = 1;
//     // Check left and right borders for middle rows
//     while( i < rows - 1)
//     {
//         if (map[i][0] != '1' || map[i][columns - 1] != '1') {
//             fprintf(stderr, "Error: Row %d is not surrounded by '1'.\n", i);
//             return 0;
//         }
//         i++;
//     }
//     // If all checks pass, the map is surrounded by '1'
//     return 1;
// }
int count_map_lines(char *line,int *inside_map,t_map map)
{
    int i = 0;
    // t_map *map;
    // printf("cloumns = %d\n",map.columns);
	if(*inside_map)
	{//here i can check others rules applied to a valid map
		
        if(map.rows==1 && map.columns==1)
            printf("line : %s- len : %d",line,map.columns);
        if (ft_strcmp(line, "\n") == 0) 
            printerr(1,"Error: The map contains a newline ");
		// if(check_walls(line))

	}
    	
	while (line[i]) 
	{
        if ((line[i] != '1' && line[i] != '0' && 
            line[i] != 'N' && line[i] != 'S' && 
            line[i] != 'E' && line[i] != 'W' && 
            line[i] != ' ' && line[i] != '\n'))
		{
			if(*inside_map)
            printerr(1,"Error: found a different symbol inside map ");
		}
        i++;
    }
	if(line[0] == '1' || line[0] == '0')
		*inside_map=1;
    return (line[0] == '1' || line[0] == '0');
}

int nbrs_lines(char *av,t_map *map) 
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
        if (count_map_lines(line,&inside,*map))
            nbr_line++;
        free(line);
    }
    close(fd); 
    if (nbr_line == 0)
        printerr(1, "Error: No valid map lines found");
    return nbr_line;
}

int is_maplast(t_map *map)
{
	if(map && map->ce_color && map->fl_color && map->no_img && map->es_img && map->we_img && map->su_img)
		return 1;
	return 0;
}

int valid_caracter(char *line, char *caracter) 
{
    int i = 0;
    int j;
    int flag;
    while (line[i]) 
	{        
        j = 0;
        flag = 0;

        while (caracter[j])
		 {
            if (line[i] == caracter[j]) 
			{
                flag = 1; 
                break;
            }
            j++;
        }
        if (flag == 0)
            return 0;
        i++;
    }

    return 1;
}

void fill_map(t_map *map, char *line, int *i,int *inside_map)
{
    if (!map || !line || !i || !inside_map)
        return;
    if (count_map_lines(line,inside_map,*map)) 
	{
        map->map[*i] = ft_strdup(line);
        // printf("Filling map row %d with line: [%s]\n",count_map_lines(line,inside_map,*map) , line);
        (*i)++;
    }
	// else if(!(count_map_lines(line,inside_map)))
	// {
	// 	printerr(1,"Error: found a different symbol inside map");
	// }
}

// void pars_map(t_map *map)
// {
// 	// if(found_space() || is_empty())
// 	// 	printerr(1,"Error: The map can not separated by  space or empty line");
//     // if((valid_caracter(map," 01NESW")))
// 	// 	printerr(1,"Error: The map must be composed of only 6 <1,0,N,W,E,S>");
// 	// if(closed_walls())
// 	// 	printerr(1,"Error: The map must be closed by walls");
// }


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
