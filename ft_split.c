#include "cube3d.h"

int	countword(char *str, char sep)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		while (str[i] && str[i] == sep)
			i++;
		if (str[i])
			len++;
		while (str[i] && str[i] != sep)
			i++;
	}
	return (len);
}

static int	len_word(char *s, char c)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static char	*alloc(char *s, char c)
{
	char	*string;
	int		lenght;
	int		i;

	i = 0;
	lenght = len_word((char *)s, c);
	string = malloc(sizeof(char) * (lenght + 1));
	if (!string)
		return (NULL);
	while (i < lenght && s[i])
	{
		string[i] = s[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

static char	**free_split(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char **string;
	int index_string;

	index_string = 0;
	if (!s)
		return (NULL);
	string = (char **)malloc(sizeof(char *) * (countword((char *)s, c) + 1));
	if (!string)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			string[index_string] = alloc((char *)s, c);
			if (!string[index_string])
				return (free_split(string, index_string));
			index_string++;
		}
		while (*s && *s != c)
			s++;
	}
	string[index_string] = NULL;
	return (string);
}