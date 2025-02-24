/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:16:41 by bbenjrai          #+#    #+#             */
/*   Updated: 2025/02/24 14:51:12 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"
=======
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 21:16:41 by bbenjrai          #+#    #+#             */
/*   Updated: 2025/02/23 11:58:31 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3

#include "../cube3d.h"

int	is_space(char str)
{
	if (str == ' ' || str == '\n' || str == '\t' || str == '\v' || str == '\f'
		|| str == '\r')
		return (1);
	return (0);
}

int	count_words(const char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (!is_space(*str))
		{
			if (!in_word)
			{
				in_word = 1;
				count++;
			}
		}
		else
		{
			in_word = 0;
		}
		str++;
	}
	return (count);
}

void	norm_texture(char *str, char **string, t_map *map)
{
	if (str[0] == 'N' && map->text[0] == 0)
	{
		map->no_img = string[1];
		map->text[0] = 1;
	}
	else if (str[0] == 'S' && map->text[1] == 0)
	{
		map->su_img = string[1];
		map->text[1] = 1;
	}
	else if (str[0] == 'W' && map->text[2] == 0)
	{
		map->we_img = string[1];
		map->text[2] = 1;
	}
	else if (str[0] == 'E' && map->text[3] == 0)
	{
		map->es_img = string[1];
		map->text[3] = 1;
	}
	else
<<<<<<< HEAD
		printerr(1, "Error: duplicate or invalid texture already set");
=======
		printerr(1, " duplicate or invalid texture already set");
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3
}

void	fill_textures(t_map *map, char *str)
{
	char	**string;
	int		j;

	string = ft_split(str, ' ');
	if (count_words(str) > 2)
		printerr(1, " the args of textures must be 2");
	j = 0;
	while (string[j])
	{
		string[j] = ft_strtrim(string[j], " \t\n");
		j++;
	}
	if ((ft_strcmp(string[1] + ft_strlen(string[1]) - 4, ".xpm")))
<<<<<<< HEAD
		printerr(1, "the texture should end with .xpm");
	if (open(string[1], O_RDONLY, 0777) == -1)
		printerr(1, "Cannot open texture file");
	if (!(is_validtexture(string)))
	{
		norm_texture(str, string, map);
	}
	else
		printerr(1, "textures should have one of the directions <NO,SO,WE,EA>");
=======
		printerr(1, " the texture should end with .xpm");
	if (open(string[1], O_RDONLY, 0777) == -1)
		printerr(1, " Cannot open texture file");
	norm_texture(str, string, map);
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3
}
