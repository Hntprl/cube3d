/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarouf <amarouf@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 22:21:39 by amarouf           #+#    #+#             */
/*   Updated: 2025/02/27 13:59:56 by amarouf          ###   ########.fr       */
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
		return (NULL);
	str = ft_malloc(size * count, 'a', false);
	if (str == 0)
		return (0);
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

int	ft_number_size(int number)
{
	int	len;

	len = 0;
	if (number == 0)
	{
		return (1);
	}
	if (number < 0)
	{
		len += 1;
	}
	while (number != 0)
	{
		number /= 10;
		len ++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		len;
	long	num;

	num = n;
	len = ft_number_size(n);
	p = ft_malloc(sizeof(char) * (len + 1), 'a', false);
	if (p == NULL)
		return (NULL);
	p[len] = '\0';
	len --;
	if (n == 0)
		p[0] = '0';
	if (num < 0)
	{
		p[0] = '-';
		num *= -1;
	}
	while (num != 0)
	{
		p[len] = (num % 10) + 48;
		len --;
		num /= 10;
	}
	return (p);
}
