/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:16:26 by bbenjrai          #+#    #+#             */
/*   Updated: 2025/02/24 14:50:59 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	is_valid_start(char **str)
{
	while (is_space(**str))
		(*str)++;
	if (!(*str) || **str == '\0' || **str == ',')
		return (0);
	return (1);
}

int	is_valid_format(char *str)
{
	int		last_was_comma;
	char	*last_non_space;

	if (!is_valid_start(&str))
		return (0);
	last_was_comma = 0;
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

void	is_validcolor(char *str)
{
	char	**split;

	if (!(is_valid_format(str)) || !(isnot_alpha(str)))
		printerr(1, "Error : invalid color the correct format (R, G, B)");
	split = ft_split(str, ',');
	if (split[3])
		printerr(1, "Error: Colors have 3 elements (R, G, B)");
}

void	check_cei_flo(char *str, t_map *map, int valid_range)
{
	if (str[0] == 'C' && map->colors[0] == 0)
	{
		if (map->ce_index < 3)
		{
			map->ce_color[map->ce_index++] = valid_range;
			if (map->ce_index == 3)
				map->colors[0] = 1;
		}
	}
	else if (str[0] == 'F' && map->colors[1] == 0)
	{
		if (map->fl_index < 3)
		{
			map->fl_color[map->fl_index++] = valid_range;
			if (map->fl_index == 3)
				map->colors[1] = 1;
		}
	}
	else
		printerr(1, "Error : color already set");
}

int	*min_fill(t_map *map, char *str, int i, int start)
{
	int		valid_range;
	char	*substr;

	if (map->ce_index == 0 && map->fl_index == 0)
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
	check_cei_flo(str, map, valid_range);
	return (NULL);
}
