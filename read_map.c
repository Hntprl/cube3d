 #include "cube3d.h"

t_map	*read_map(char *av)
{
	int		i;
	int		fd;
	char	*line;
	t_map	*map;
	char	**myarr;

	i = 0;
	if (!av)
		return (NULL);
	map = ft_calloc(1, sizeof(t_map));
	init_t_map(&map);
	map->block_size = 40;
	checkpath(av);
	map->rows = nbrs_lines(av, &map->columns);
	myarr = ft_calloc(map->columns, sizeof(char *));
	map->map = ft_calloc(map->rows, sizeof(char *));
	if (!map->map)
	{
		free_map(map);
		free_arg(myarr);
		return (NULL);
	}
	fd = open(av, O_RDONLY, 0777);
	if (fd == -1)
	{
		free_map(map);
		free_arg(myarr);
		return (NULL);
	}
	if (to_map(fd, myarr, map) != 1)
		printerr(1, "Error: the game must have one player ");
	isvalid_map(map, myarr);
	free_arg(myarr);
	close(fd);
	return (map);
}