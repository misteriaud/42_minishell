/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:26:10 by artblin           #+#    #+#             */
/*   Updated: 2022/04/28 14:20:28 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	cmd_pwd(t_ctx *ctx, t_token *args)
{
	(void)args;
	t_str	value;

	if (!get_variable(ctx, "PWD", &value))
	{
		write(STDOUT_FILENO, value.str, value.len);
		write(STDOUT_FILENO, "\n", 1);
	}
	return (NO_ERROR);
	//exit(NO_ERROR);
}
