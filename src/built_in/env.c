/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:25:25 by artblin           #+#    #+#             */
/*   Updated: 2022/04/28 14:19:58 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	cmd_env(t_ctx *ctx, t_token *args)
{
	(void)args;
	const t_env		*elm = ctx->env;

	while (elm)
	{
		write(STDOUT_FILENO, elm->key.str, elm->key.len);
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, elm->value.str, elm->value.len);
		write(STDOUT_FILENO, "\n", 1);
		elm = elm->next;
	}
	return (NO_ERROR);
}
