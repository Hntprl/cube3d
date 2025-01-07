#include "cube3d.h"

void init_t_map(t_map **map) 
{
    if (!map || !*map)
        return;
    
    (*map)->map = NULL;
    (*map)->es_img = NULL;
    (*map)->we_img = NULL;
    (*map)->no_img = NULL;
    (*map)->su_img = NULL;
    
    (*map)->fl_color = calloc(3, sizeof(int));
    (*map)->ce_color = calloc(3, sizeof(int));
    if (!(*map)->fl_color || !(*map)->ce_color) 
    {
        free((*map)->fl_color);
        free((*map)->ce_color);
        free(*map);
        *map = NULL;
        return;
    }
    
    (*map)->rows = 0;
    (*map)->columns = 0;
    (*map)->block_size = 0;
}

void	free_arg(char **str)
{
	int		i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i++]);
	}
	free(str);
}
void free_map(t_map *map)
{
    if (!map)
        return;
    free_arg(map->map);
    free(map->es_img);
    free(map->we_img);
    free(map->no_img);
    free(map->su_img);
    free(map->fl_color);
    free(map->ce_color);

    init_t_map(&map);
}

// int validate_map(char **map, int rows, int columns) {
//     int player_found = 0;
//     int player_x = -1, player_y = -1;

//     // Step 1: Validate symbols and find the player
//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < columns; j++) {
//             char c = map[i][j];
//             if (c == 'p') {
//                 if (player_found) {
//                     printerr(1, "Error: Multiple players found.\n");
//                     return 0;
//                 }
//                 player_found = 1;
//                 player_x = i;
//                 player_y = j;
//             } else if (c != '1' && c != '0') {
//                 printerr(1, "Error: Invalid character in map.\n");
//                 return 0;
//             }
//         }
//     }

//     if (!player_found) {
//         printerr(1, "Error: No player found in map.\n");
//         return 0;
//     }

//     // Step 2: Check outer walls
//     for (int j = 0; j < columns; j++) {
//         if (map[0][j] != '1' || map[rows - 1][j] != '1') 
//             printerr(1, "Error: Map is not surrounded by walls (top or bottom).\n");
            
//     }

//     for (int i = 0; i < rows; i++) {
//         if (map[i][0] != '1' || map[i][columns - 1] != '1') {
//             printerr(1, "Error: Map is not surrounded by walls (sides).\n");
//             return 0;
//         }
//     }

//     // Step 3: Flood fill for connectivity
//     // if (!flood_fill(map, rows, columns, player_x, player_y)) {
//     //     printerr(1, "Error: Map has inaccessible spaces or leaks.\n");
//     //     return 0;
//     // }

//     // Step 4: Rectangular shape check
//     for (int i = 1; i < rows; i++) {
//         if (ft_strlen(map[i]) != columns) {
//             printerr(1, "Error: Map rows are not rectangular.\n");
//             return 0;
//         }
//     }

//     // All checks passed
//     return 1;
// }