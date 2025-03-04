/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:16:36 by bbenjrai          #+#    #+#             */
/*   Updated: 2025/02/28 21:40:17 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	check_zero(char **myarr, t_map *map, int i, int j)
{
	if (myarr[i][j] == '0')
	{
		if ((i == 0 || j == 0) || i == map->rows - 1
			|| j == (int)ft_strlen(myarr[i]) - 1)
			printerr(1, " Invalid map not surrounded by valid characters");
		if (!((i > 0 && (myarr[i - 1][j] == '0' || myarr[i - 1][j] == '1'
				|| ft_strchr("NEWS", myarr[i - 1][j])))
				&& (i < map->rows - 1 && (myarr[i + 1][j] == '0' || myarr[i
						+ 1][j] == '1' || ft_strchr("NEWS", myarr[i + 1][j])))
				&& (j > 0 && (myarr[i][j - 1] == '0' || myarr[i][j - 1] == '1'
						|| ft_strchr("NEWS", myarr[i][j - 1])))
				&& (j < (int)ft_strlen(myarr[i]) - 1 && (myarr[i][j + 1] == '0'
						|| myarr[i][j + 1] == '1' || ft_strchr("NEWS",
							myarr[i][j + 1])))))
		{
			printerr(1, " Invalid map not surrounded by valid characters");
		}
	}
}

void	check_player(char **myarr, t_map *map, int i, int j)
{
	if (ft_strchr("NEWS", myarr[i][j]))
	{
		if (i == 0 || j == 0 || i == map->rows - 1
			|| j == (int)ft_strlen(myarr[i]) - 1)
			printerr(1, " Invalid map not surrounded by valid characters");
		if (!((i > 0 && (myarr[i - 1][j] == '0' || myarr[i - 1][j] == '1'))
				&& (i < map->rows - 1 && (myarr[i + 1][j] == '0' || myarr[i
						+ 1][j] == '1')) && (j > 0 && (myarr[i][j - 1] == '0'
						|| myarr[i][j - 1] == '1'))
				&& (j < (int)ft_strlen(myarr[i]) - 1 && (myarr[i][j + 1] == '0'
						|| myarr[i][j + 1] == '1'))))
			printerr(1, " Invalid map not surrounded by valid characters");
	}
}

void	check_space(char **myarr, t_map *map, int i, int j)
{
	if (myarr[i][j] == ' ')
	{
		if (i > 0 && j > 0 && i < map->rows - 1 && j < (int)ft_strlen(myarr[i])
			- 1)
		{
			if (!((myarr[i - 1][j] == ' ' || myarr[i - 1][j] == '1') && (myarr[i
						+ 1][j] == ' ' || myarr[i + 1][j] == '1') && (myarr[i][j
						- 1] == ' ' || myarr[i][j - 1] == '1') && (myarr[i][j
						+ 1] == ' ' || myarr[i][j + 1] == '1')))
			{
				printerr(1, " Invalid map not surrounded by valid characters");
			}
		}
	}
}

int	isvalid_map(t_map *map, char **myarr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->rows && myarr[i])
	{
		j = 0;
		while (j < (int)ft_strlen(myarr[i]))
		{
			check_zero(myarr, map, i, j);
			check_player(myarr, map, i, j);
			check_space(myarr, map, i, j);
			j++;
		}
		i++;
	}
	return (1);
}
