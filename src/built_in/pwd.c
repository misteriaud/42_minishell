/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:26:10 by artblin           #+#    #+#             */
/*   Updated: 2022/05/10 16:39:29 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	cmd_pwd(t_ctx *ctx, t_token *args)
{
	t_str	value;
	char	*pwd;

	(void)args;
	if (!get_variable(ctx, "PWD", &value))
	{
		write(STDOUT_FILENO, value.str, value.len);
	}
	else
	{
		pwd = getcwd(NULL, 0);
		write(STDOUT_FILENO, pwd, get_len(pwd));
		free(pwd);
	}
	write(STDOUT_FILENO, "\n", 1);
	return (NO_ERROR);
}
