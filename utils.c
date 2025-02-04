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
		return (ft_strdup(""));
	while (ft_strchr(set, s1[len]) && len >= 0)
		len--;
	str = malloc((len - i + 2) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)&s1[i], len - i + 2);
	return (str);
}

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
	int i;
	int sign;
	int res;

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