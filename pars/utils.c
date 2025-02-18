/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbenjrai <bbenjrai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:21:03 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/18 11:05:38 by bbenjrai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (-1);
	else if (!s2)
		return (1);
	else
		while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
			i++;
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

int	ft_isdigit(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

size_t	ft_strlcpy(char *dst, char *src, size_t n)
{
	size_t	i;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (n != 0)
	{
		while (src[i] && i < n - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (srclen);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		i;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = ft_strlen((char *)s1) - 1;
	while (ft_strchr(set, s1[i]) && i <= len)
		i++;
	if (i >= len)
		return (ft_strdup2(""));
	while (ft_strchr(set, s1[len]) && len >= 0)
		len--;
	// str = malloc((len - i + 2) * sizeof(char));
	str= ft_malloc(sizeof(char) *(len-i+2), 'a', false);
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)&s1[i], len - i + 2);
	return (str);
}
char	*ft_strdup2(const char *s1)
{
	size_t	i;
	char	*p;

	i = 0;
	p = ft_malloc(sizeof(char) * ft_strlen(s1) + 1,'a',false);
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