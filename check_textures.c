#include "cube3d.h"

int	is_validtexture(char **str)
{
	if ((!ft_strcmp(str[0], "NO") || !ft_strcmp(str[0], "SO")
			|| !ft_strcmp(str[0], "WE") || !ft_strcmp(str[0], "EA"))
		&& (ft_strlen(str[1]) > 4))
		return (0);
	else
		return (1);
}

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

void	fill_textures(t_map *map, char *str)
{
	char	**string;
	int		j;

	string = ft_split(str, ' ');
	if (count_words(str) > 2)
		printerr(1, "Error : the args of textures must be 2");
	j = 0;
	while (string[j])
	{
		string[j] = ft_strtrim(string[j], " \t\n");
		j++;
	}
	if ((ft_strcmp(string[1] + ft_strlen(string[1]) - 4, ".xpm")))
		printerr(1, "the texture should end with .xpm");
	if (!(is_validtexture(string)))
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
			printerr(1, "Error: duplicate or invalid texture already set");
	}
	else
		printerr(1, "the textures should have one of the directions < NO, SO,WE, EA > ");
}