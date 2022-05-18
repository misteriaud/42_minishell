/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:23:15 by artblin           #+#    #+#             */
/*   Updated: 2022/05/18 16:05:42 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	skip_null(t_token *args)
{
	t_token		*elm;

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
			break ;
	}
}

void	get_arg(t_token **args, int *state)
{
	while ((*args && (*args)->value.str
			&& (*args)->value.str[0] == '-'
			&& (*args)->value.str[1] == 'n'))
	{
		if (is_only_set(&(*args)->value.str[2], "n"))
		{
			*state = 0;
			*args = (*args)->next;
		}
		else
			break ;
	}
}

t_err	cmd_echo(t_ctx *ctx, t_token *args)
{
	int		state;

	(void)ctx;
	skip_null(args);
	state = 1;
	get_arg(&args, &state);
	while (args)
	{
		if (args->value.str)
		{
			write(1, args->value.str, args->value.len);
			if (args->next)
				write(STDOUT_FILENO, " ", 1);
		}
		args = args->next;
	}
	if (state)
		write(STDOUT_FILENO, "\n", 1);
	return (NO_ERROR);
}
