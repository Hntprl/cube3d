#include "cube3d.h"

void	checkpath(char *av)
{
	if (ft_strcmp(av + ft_strlen(av) - 4, ".cub"))
		printerr(1, "Error: The file must end with .cub");
}

// void	spliit(char *str, t_map *map)
// {
// 	int	i;
// 	int	start;

// 	i = 1;
// 	start = 0;
// 	is_validcolor(str + 1);
// 	while (str[i])
// 	{
// 		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
// 			i++;
// 		start = i;
// 		while (str[i] && ft_isdigit(str[i]))
// 			i++;
// 		if (start < i)
// 			min_fill(map, str, i, start);
// 		else if (str[i] == ',')
// 			i++;
// 		i++;
// 	}
// }
void spliit(char *str, t_map *map)
{
    int i;
    int start;

    if (!str || !map)
        return;
    i = 1;
    while (str[i])
    {
        while (str[i] && (str[i] == ' ' || str[i] == '\t'))
            i++;
        if (!str[i])
            break;
        is_validcolor(str + 1);
        start = i;
        while (str[i] && ft_isdigit(str[i]))
            i++;
        if (start < i && i - start <= 3)  // max 3 digits for RGB
        {
            min_fill(map, str, i, start);
        }
        else if (str[i] == ',')
        {
            i++;
            continue;
        }
        if (!str[i] || (!ft_isdigit(str[i]) && str[i] != ','))
            break;
    }
}

void	fill_colors(t_map *map, char *str)
{
	if ((str[0] == 'C' || str[0] == 'F') && (str[1] == ' ' || str[1] == '	'))
		spliit(str, map);
	else
		printerr(1, "error the format of color invalid");
}