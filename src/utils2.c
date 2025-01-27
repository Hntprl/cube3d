/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:21:39 by amarouf           #+#    #+#             */
/*   Updated: 2025/01/26 22:44:10 by amarouf          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube3d.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	char	*pt;
	int		i;
	int		n;

	if (size != 0 && count >= SIZE_MAX / size)
	{
		return (NULL);
	}
	str = malloc(size * count);
	if (str == 0)
	{
		return (0);
	}
	i = 0;
	pt = (char *)str;
	n = count * size;
	while (n-- > 0)
	{
		pt[i] = '\0';
		i++;
	}
	return (str);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		i++;
		sign = -sign;
	}
	while (str[i] <= '9' && str[i] >= '0')
		res = res * 10 + str[i++] - '0';
	return (sign * res);
}
