/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:16:53 by bbenjrai          #+#    #+#             */
/*   Updated: 2025/03/01 12:10:12 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	printerr(int status, char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	ft_malloc(sizeof(t_map), 'f', false);
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
