/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:58:27 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/18 16:06:23 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <memory.h>
#include <struct.h>

static char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((unsigned char)(s[i]) == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	if ((unsigned char)(s[i]) == (unsigned char)c)
		return ((char *)s + i);
	return (0);
}

static int	by_ten_overflow(long *result)
{
	int		i;
	long	temp;

	i = -1;
	temp = *result;
	while (*result && ++i < 9)
	{
		*result += temp;
		if (((*result >> 63) & 1) == 0)
			return (1);
	}
	return (0);
}

int	secure_atoi(char *str, long *result)
{
	long	sign;

	*result = 0;
	sign = -1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = 1;
		str++;
	}
	while (*str)
	{
		if (!ft_strchr("0123456789", *str) || by_ten_overflow(result))
			return (1);
		*result -= *str - '0';
		if (*result && ((*result >> 63) & 1) == 0)
			return (1);
		str++;
	}
	*result *= sign;
	if (((*result >> 63) & 1) != (sign == 1))
		return (1);
	return (0);
}

size_t	ft_digitnbr(long n)
{
	size_t		d;

	d = (!n);
	while (n && ++d)
		n /= 10;
	return (d);
}

char	*ft_itoa(int i)
{
	char	*a;
	long	n;
	long	x;
	char	m;

	n = (long)i;
	m = 0;
	x = ft_digitnbr(n);
	if (n < 0 && ++x && ++m)
		n = -(n);
	if (xmalloc(&a, (x + 1) * sizeof(char), ENV_ALLOC))
		return (NULL);
	if (a)
	{
		a[x] = '\0';
		while (--x >= 0)
		{
			a[x] = (n % 10) + '0';
			n /= 10;
			if (!x && m)
				a[x] = '-';
		}
		return (a);
	}
	return (NULL);
}
