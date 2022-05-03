/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secure_atoi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:58:27 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/03 13:42:03 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	by_ten_overflow(int *result)
{
	int	i;
	int	temp;

	i = -1;
	temp = *result;
	while (*result && ++i < 9)
	{
		*result += temp;
		if (((*result >> 31) & 1) == 0)
			return (1);
	}
	return (0);
}

int	secure_atoi(char *str, int *result)
{
	int	sign;

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
		if (*result && ((*result >> 31) & 1) == 0)
			return (1);
		str++;
	}
	*result *= sign;
	if (((*result >> 31) & 1) != (sign == 1))
		return (1);
	return (0);
}
