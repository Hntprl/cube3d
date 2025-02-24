/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:16:36 by bbenjrai          #+#    #+#             */
/*   Updated: 2025/02/24 14:51:08 by amarouf          ###   ########.fr       */
=======
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:16:36 by bbenjrai          #+#    #+#             */
/*   Updated: 2025/02/23 11:38:22 by bbenjrai         ###   ########.fr       */
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	check_zero(char **myarr, t_map *map, int i, int j)
{
	if (myarr[i][j] == '0')
	{
		if ((i == 0 || j == 0) || i == map->rows - 1
			|| j == (int)ft_strlen(myarr[i]) - 1)
<<<<<<< HEAD
			printerr(1,
				"Error : Invalid map not surrounded by valid characters");
=======
			printerr(1, " Invalid map not surrounded by valid characters");
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3
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
<<<<<<< HEAD
			printerr(1,
				"Error : Invalid map not surrounded by valid characters");
=======
			printerr(1, " Invalid map not surrounded by valid characters");
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3
		}
	}
}

void	check_player(char **myarr, t_map *map, int i, int j)
{
	if (ft_strchr("NEWS", myarr[i][j]))
	{
		if (i == 0 || j == 0 || i == map->rows - 1
			|| j == (int)ft_strlen(myarr[i]) - 1)
<<<<<<< HEAD
			printerr(1,
				"Error : Invalid map not surrounded by valid characters");
=======
			printerr(1, " Invalid map not surrounded by valid characters");
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3
		if (!((i > 0 && (myarr[i - 1][j] == '0' || myarr[i - 1][j] == '1'))
				&& (i < map->rows - 1 && (myarr[i + 1][j] == '0' || myarr[i
						+ 1][j] == '1')) && (j > 0 && (myarr[i][j - 1] == '0'
						|| myarr[i][j - 1] == '1'))
				&& (j < (int)ft_strlen(myarr[i]) - 1 && (myarr[i][j + 1] == '0'
						|| myarr[i][j + 1] == '1'))))
<<<<<<< HEAD
			printerr(1,
				"Error : Invalid map not surrounded by valid characters");
=======
			printerr(1, " Invalid map not surrounded by valid characters");
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3
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
<<<<<<< HEAD
				printerr(1,
					"Error: Invalid map not surrounded by valid characters");
=======
				printerr(1, " Invalid map not surrounded by valid characters");
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3
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
