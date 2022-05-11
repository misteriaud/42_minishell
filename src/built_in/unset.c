/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:26:34 by artblin           #+#    #+#             */
/*   Updated: 2022/05/11 11:56:00 by mriaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <built_in.h>

static void	delete(t_ctx *ctx, t_token *args)
{
	t_env	*elm;
	t_env	*prv;

	prv = NULL;
	elm = ctx->env;
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
			return ;
		}
		prv = elm;
		elm = elm->next;
	}
}

t_err	cmd_unset(t_ctx *ctx, t_token *args)
{
	t_err	err;

	err = NO_ERROR;
	while (args)
	{
		if (!is_var_start(*args->value.str))
			err = print_err(UNSET_ERROR, args->value.str);
		else
			delete(ctx, args);
		args = args->next;
	}
	return (err);
}
