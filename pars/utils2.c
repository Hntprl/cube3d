/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:25:43 by bbenjrai          #+#    #+#             */
/*   Updated: 2025/02/22 12:11:44 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	isnot_alpha(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != ',' && *(str + 1) != ','
			&& !is_space(*str))
			return (0);
		str++;
	}
	return (1);
}

char	*ft_strdup2(const char *s1)
{
	size_t	i;
	char	*p;

	i = 0;
	p = ft_malloc(sizeof(char) * ft_strlen(s1) + 1, 'a', false);
	if (p == NULL)
	{
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	is_newline(char *line, t_map_fill *fill_info, int rows)
{
	char	*str;

	str = ft_strtrim(line, " \t\n");
	if (!str)
		printerr(1, "Error: Memory allocation failed");
	if (str[0] == '\0' && (*fill_info->inside_map) == 1
		&& fill_info->map_lines_read != rows)
	{
		printerr(1, "Error: Empty line inside map");
	}
}
