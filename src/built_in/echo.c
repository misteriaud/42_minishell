/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:23:15 by artblin           #+#    #+#             */
/*   Updated: 2022/05/18 15:44:29 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	skip_null(t_token *args)
{
	t_token *elm;

	elm = args;
	while (elm)
	{
		if (elm->next)
		{
			if (!elm->next->value.str)
			{
				elm->next = elm->next->next;
			}
			elm = elm->next;
		}
		else
			break;

	}

}

t_err	cmd_echo(t_ctx *ctx, t_token *args)
{
	int		state;

	skip_null(args);

	(void)ctx;
	state = 1;

	while ((args && args->value.str && args->value.str[0] == '-'
			&& args->value.str[1] == 'n'))
	{
		if (is_only_set(&args->value.str[2], "n"))
		{
			state = 0;
			args = args->next;
		}
		else
			break ;
	}
	//while (args && !args->value.str)
	//	args = args->next;
	//if (args && args->value.str)
	//{
	//	write(1, args->value.str, args->value.len);
	//	args = args->next;
	//}
	while (args)
	{
		if (writer(1, args->value.str, args->value.len))
			return (1);
		args = args->next;
		if (args)
			if (writer(STDOUT_FILENO, " ", 1))
				return (1);
	}
	if (state)
		if (writer(STDOUT_FILENO, "\n", 1))
			return (1);
	return (NO_ERROR);
}*/
		/*if (!args->value.str)
		{
			args = args->next;
			continue ;
		}
		write(1, args->value.str, args->value.len);
		args = args->next;
		if (args)
			write(STDOUT_FILENO, " ", 1);
			*/
