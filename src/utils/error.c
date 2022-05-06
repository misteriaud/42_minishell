/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 09:30:27 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/06 17:44:41 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_putchar(char c)
{
	write(2, &c, 1);
}

void print_nbr_err(const t_err err)
{
	if (err > 9)
		print_nbr_err(err / 10);
	ft_putchar(err % 10 + '0');
}

void print_custom_err(const char *str)
{
	if (str && *str)
		write(2, str, get_len(str));
}

t_err print_err(t_err err, char *str)
{
	if (!err || err == 1 || err == CTRL_C_ERROR || err == PARSING_ERROR || err == LEXING_ERROR)
		return (err);
	write(2, "minishell: ", 11);
	if (err == UNKNOWN_EXEC_ERROR)
	{
		print_custom_err(str);
		print_custom_err(": command not found\n");
	}
	else if (err == UNKNOWN_PATH_ERROR)
		perror(str);
	else if (err == EXIT_ERROR)
	{
		print_custom_err("exit: ");
		print_custom_err(str);
		print_custom_err(": numeric argument required\n");
	}
	else
	{
		print_custom_err("unexpected error occurred (");
		print_nbr_err(err);
		write(2, ")\n", 2);
	}
	return (err);
}
