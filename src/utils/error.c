/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 09:30:27 by mriaud            #+#    #+#             */
/*   Updated: 2022/05/10 15:22:21 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_putchar(char c)
{
	write(2, &c, 1);
}

void	print_nbr_err(const t_err err)
{
	if (err > 9)
		print_nbr_err(err / 10);
	ft_putchar(err % 10 + '0');
}

void	print_custom_err(const char *str)
{
	if (str && *str)
		write(2, str, get_len(str));
}

void	print_err_2(t_err err, char *str)
{
	if (err == EXPORT_ERROR)
	{
		print_custom_err("export: ");
		print_custom_err(str);
		print_custom_err(": not a valid identifier\n");
	}
	else if (err == UNSET_ERROR)
	{
		print_custom_err("unset: ");
		print_custom_err(str);
		print_custom_err(": not a valid identifier\n");
	}
}
	/*
	else
	{
		print_custom_err("unexpected error occurred (");
		print_nbr_err(err);
		write(2, ")\n", 2);
	}*/

t_err	print_err(t_err err, char *str)
{
	if (!err)
		return (err);
	write(2, "minishell: ", 11);
	print_err_2(err, str);
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
	return (err);
}
