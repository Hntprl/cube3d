/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:19:08 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/26 22:44:10 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	checkpath(char *av)
{
	if (ft_strcmp(av + ft_strlen(av) - 4, ".cub"))
		printerr(1, "Error: The file must end with .cub");
}

void	spliit(char *str, t_map *map)
{
	int	i;
	int	start;

	i = 1;
	start = 0;
	is_validcolor(str + 1);
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		start = i;
		while (str[i] && ft_isdigit(str[i]))
			i++;
		if (start < i)
			min_fill(map, str, i, start);
		else if (str[i] == ',')
			i++;
		i++;
	}
}

void	fill_colors(t_map *map, char *str)
{
	if ((str[0] == 'C' || str[0] == 'F') && str[1] == ' ' || str[1] == '	')
		spliit(str, map);
	else
		printerr(1, "error the format of color invalid");
}
