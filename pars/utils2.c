/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:25:43 by bbenjrai          #+#    #+#             */
/*   Updated: 2025/02/24 14:51:39 by amarouf          ###   ########.fr       */
=======
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 22:25:43 by bbenjrai          #+#    #+#             */
/*   Updated: 2025/02/23 11:32:01 by bbenjrai         ###   ########.fr       */
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3
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
<<<<<<< HEAD
		printerr(1, "Error: Memory allocation failed");
	if (str[0] == '\0' && (*fill_info->inside_map) == 1
		&& fill_info->map_lines_read != rows)
	{
		printerr(1, "Error: Empty line inside map");
=======
		printerr(1, " Memory allocation failed");
	if (str[0] == '\0' && (fill_info->inside_map) == 1
		&& fill_info->map_lines_read != rows)
	{
		printerr(1, " Empty line inside map Or the map not the last");
>>>>>>> e6670a3f8cb5374debb8a80e1fdf8e92fe2e58f3
	}
}
