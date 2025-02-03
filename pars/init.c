#include "../cube3d.h"

void	printerr(int status, char *str)
{
	printf("Error\n");
	printf("%s\n", str);
	exit(status);
}

void	init_t_map(t_map **map)
{
	if (!map || !*map)
		return ;
	(*map)->map = NULL;
	(*map)->no_img = ft_calloc(1, sizeof(char *));
	(*map)->su_img = ft_calloc(1, sizeof(char *));
	(*map)->es_img = ft_calloc(1, sizeof(char *));
	(*map)->we_img = ft_calloc(1, sizeof(char *));
	(*map)->es_img = NULL;
	(*map)->we_img = NULL;
	(*map)->no_img = NULL;
	(*map)->su_img = NULL;
	(*map)->fl_color = ft_calloc(3, sizeof(int));
	(*map)->ce_color = ft_calloc(3, sizeof(int));
	if (!(*map)->fl_color || !(*map)->ce_color)
	{
		free((*map)->fl_color);
		free((*map)->ce_color);
		free(*map);
		*map = NULL;
		return ;
	}
	(*map)->rows = 0;
	(*map)->columns = 0;
	(*map)->text[0] = 0;
	(*map)->text[1] = 0;
	(*map)->text[2] = 0;
	(*map)->text[3] = 0;
	(*map)->colors[1] = 0;
	(*map)->colors[0] = 0;
	(*map)->block_size = 0;
}

void	free_arg(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i++]);
	}
	free(str);
}
void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_arg(map->map);
	free(map->es_img);
	free(map->we_img);
	free(map->no_img);
	free(map->su_img);
	free(map->fl_color);
	free(map->ce_color);
	init_t_map(&map);
}
// void	add_allocation(MemoryManager *manager, void *ptr)
// {
// 	if (manager->count < 100)
// 	{
// 		manager->allocations[manager->count++] = ptr;
// 	}
// 	else
// 	{
// 		fprintf(stderr, "Memory Manager: Exceeded allocation limit!\n");
// 	}
// }

// void	free_all_allocations(MemoryManager *manager)
// {
// 	int i;

// 	i = 0;
// 	while (i < manager->count)
// 	{
// 		free(manager->allocations[i]);
// 		i++;
// 	}
// 	manager->count = 0;
// }