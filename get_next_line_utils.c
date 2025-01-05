/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:45:39 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/05 22:46:48 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if(!s)
		return 0;
	while (s[i] != '\0')
	{
		i ++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*p;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	p = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1 * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i ++;
	}
	while (s2[j] != '\0')
	{
		p[i + j] = s2[j];
		j ++;
	}
	p[i + j] = '\0';
	return (p);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*k;
	char	ch;

	ch = c;
	i = 0;
	k = (char *)s;
	while (k[i] != '\0')
	{
		if (k[i] == ch)
			return (k + i);
		i++;
	}
	if (ch == '\0')
		return (k + i);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*p;

	i = 0;
	p = (char *) malloc(sizeof(char) * ft_strlen(s1) + 1);
	// p=calloc((ft_strlen(s1)+1),sizeof(char *));
	if (p == NULL)
	{
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		p[i] = s1[i];
		i ++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
