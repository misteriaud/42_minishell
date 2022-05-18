/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:07:38 by artblin           #+#    #+#             */
/*   Updated: 2022/05/17 16:38:01 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_num(const char c)
{
	return ((c >= '0') & (c <= '9'));
}

int	is_lower(const char c)
{
	return ((c >= 'a') & (c <= 'z'));
}

int	is_upper(const char c)
{
	return ((c >= 'A') & (c <= 'Z'));
}

int	is_under(const char c)
{
	return (c == '_');
}

int	is_variable(const char c)
{
	return (is_var_start(c) | is_num(c));
}

int is_white(const char c)
{
	return ((c >= 9 && c <= 13) || (c == 32));

}
