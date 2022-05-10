/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:25:25 by artblin           #+#    #+#             */
/*   Updated: 2022/05/10 18:15:12 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	cmd_env(t_ctx *ctx, t_token *args)
{
	const t_env		*elm = ctx->env;

	(void)args;
	while (elm)
	{
		write(STDOUT_FILENO, elm->key.str, elm->key.len);
		write(STDOUT_FILENO, "=", 1);
		write(STDOUT_FILENO, elm->value.str, elm->value.len);
		write(STDOUT_FILENO, "\n", 1);
		elm = elm->next;
	}
	close(1);
	return (NO_ERROR);
}
