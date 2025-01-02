#include "cube3d.h"

int nbrs_lines(char *av)
{
	int fd;
	char *line;
	int nbr_line;
	nbr_line=0;
	fd= open(av, O_RDONLY, 0777);
	if (fd == -1 || !av)
        return -1;
	checkpath(fd,av);
	while((line = get_next_line(fd)) != NULL)
	{
		if(line[0]=='1' || line[0]=='0')
				nbr_line++;
		free(line);
	}
	close(fd);
	return nbr_line;
	
}
int is_maplast(t_map *map)
{
	if(map && map->ce_color && map->fl_color && map->no_img && map->es_img && map->we_img && map->su_img)
		return 1;
	return 0;
}

int valid_caracter(char *line, char *caracter) {
    int i = 0;
    int j;
    int flag;
    while (line[i]) {        
        j = 0;
        flag = 0;

        while (caracter[j]) {
            if (line[i] == caracter[j]) {
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

// void fill_map(t_map *map, char *line, int i) {
//     if (!map || !line || i < 0 || i >= map->rows)
//         return;
        
//     if (line[0] == '1' || line[0] == '0') {
//         map->map[i] = ft_strdup(line);  // Make a copy of the line
//         if (!map->map[i]) {
//             return;
//         }
//     }
// }
int count_map_lines(char *line)
{
    int i = 0;
    while (line[i]) {
        if (line[i] != '1' && line[i] != '0' && 
            line[i] != 'N' && line[i] != 'S' && 
            line[i] != 'E' && line[i] != 'W' && 
            line[i] != ' ' && line[i] != '\n')
            return 0;
        i++;
    }
    return (line[0] == '1' || line[0] == '0');
}

void fill_map(t_map *map, char *line, int *i)
{
    if (!map || !line || !i)
        return;
        
    if (count_map_lines(line)) {
        map->map[*i] = ft_strdup(line);
        // printf("Filling map row %d with line: [%s]\n", *i, map->map[*i]);
        (*i)++;
    }
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