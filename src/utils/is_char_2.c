/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_char_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artblin <artblin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 15:18:06 by artblin           #+#    #+#             */
/*   Updated: 2022/05/18 16:06:35 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_var_start(const char c)
{
	return (is_lower(c) | is_upper(c) | is_under(c));
}

int	is_variable(const char c)
{
	return (is_var_start(c) | is_num(c));
}
