#include "cube3d.h"

int nbrs_lines(char *av)
{
	int fd;
	char *line;
	int nbr_line;
	nbr_line=0;
	fd= open(av, O_RDONLY, 0777);
	checkpath(fd,av);
	while((line = get_next_line(fd)) != NULL)
	{
		// printf("1 line *%s*",line);
		if(line[0]=='1' || line[0]=='0')
				nbr_line++;
	}
	close(fd);
	return nbr_line;
	
}
int is_maplast(t_map *map)
{
	if(map->ce_color && map->fl_color && map->no_img && map->es_img && map->we_img && map->su_img)
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
	// new_line=ft_strdup(line);
		// new_line[ft_strlen(line)]='\0';
		// if(!(valid_caracter(new_line,"10NEWS")))
		// 	printerr(1,"Error: The map must be composed of only 6 <1,0,N,W,E,S>");
		// printf("is valid =1 if not 0 ---> %d == ",(valid_caracter(line,"01NESW")));
void fill_map(t_map *map,char *line,int i)
{
	if(line[0]=='1' || line[0]=='0')
		map->map[i] = line;
	
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