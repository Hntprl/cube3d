#include "../cube3d.h"

int	is_valid_format(char *str)
{
	int		last_was_comma;
	char	*last_non_space;

	while (is_space(*str))
		str++;
	if (!str || *str == '\0')
		return (0);
	last_was_comma = 0;
	if (*str == ',')
		return (0);
	last_non_space = NULL;
	while (*str)
	{
		if (!is_space(*str))
			last_non_space = str;
		if (*str == ',')
		{
			if (last_was_comma)
				return (0);
			last_was_comma = 1;
		}
		else
			last_was_comma = 0;
		str++;
	}
	if (last_non_space && *last_non_space == ',')
		return (0);
	return (1);
}

int	isnot_alpha(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ',' && !is_space(*str))
			return (0);
		str++;
	}
	return (1);
}

void	is_validcolor(char *str)
{
	char	**split;

	if (!(is_valid_format(str)) || !(isnot_alpha(str)))
		printerr(1, "Error : invalid color the correct format (R, G, B)");
	split = ft_split(str, ',');
	if (split[3])
		printerr(1, "Error: Colors have 3 elements (R, G, B)");
	free(split);
}

int	*min_fill(t_map *map, char *str, int i, int start)
{
	int			valid_range;
	char		*substr;
	static int	ce_index;
	static int	fl_index;

	ce_index = 0;
	fl_index = 0;
	valid_range = 0;
	if (ce_index == 0 && fl_index == 0)
	{
		map->ce_color = ft_calloc(3, sizeof(int));
		map->fl_color = ft_calloc(3, sizeof(int));
	}
	substr = ft_substr(str, start, i);
	valid_range = ft_atoi(substr);
	free(substr);
	if (valid_range < 0 || valid_range > 255)
	{
		printerr(1, "Error: The color range should be between 0 & 255");
		return (NULL);
	}
	if (str[0] == 'C' && map->colors[0] == 0)
	{
		if (ce_index < 3)
		{
			map->ce_color[ce_index++] = valid_range;
			if (ce_index == 3)
				map->colors[0] = 1;
		}
	}
	else if (str[0] == 'F' && map->colors[1] == 0)
	{
		if (fl_index < 3)
		{
			map->fl_color[fl_index++] = valid_range;
			if (fl_index == 3)
				map->colors[1] = 1;
		}
	}
	else
		printerr(1, "Error :  color already set");
	return (NULL);
}
