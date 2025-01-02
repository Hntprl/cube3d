#include "cube3d.h"

void init_t_map(t_map **map) {
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

void free_map(t_map *map)
{
    if (!map)
        return;
    int i = 0;
    if (map->map) {
        while ( map->map[i])
        {
            free(map->map[i]);
            i++;
        }
        free(map->map);
    }

    free(map->es_img);
    free(map->we_img);
    free(map->no_img);
    free(map->su_img);
    free(map->fl_color);
    free(map->ce_color);

    init_t_map(&map);
}

