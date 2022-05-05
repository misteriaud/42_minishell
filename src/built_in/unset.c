/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:26:34 by artblin           #+#    #+#             */
/*   Updated: 2022/05/05 17:55:39 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	cmd_unset(t_ctx *ctx, t_token *args)
{
	t_env	*elm;
	t_env	*prv;

	elm = ctx->env;
	prv = NULL;
	while (elm)
	{
		if (!compare(args->value.str, elm->key.str))
		{
			xfree(elm->key.str, ENV_ALLOC);
			xfree(elm->value.str, ENV_ALLOC);
			if (!prv)
				ctx->env = elm->next;
			else
				prv->next = elm->next;
			xfree(elm, ENV_ALLOC);
			return (NO_ERROR);
		}
		prv = elm;
		elm = elm->next;
	}
	return (NO_ERROR);
}
