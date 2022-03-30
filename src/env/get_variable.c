/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:14:33 by artblin           #+#    #+#             */
/*   Updated: 2022/03/30 22:32:26 by artblin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_err	get_variable(t_ctx *ctx, const char *key, t_str *value)
{
	t_env	*elm;

	elm = ctx->env;
	while (elm)
	{
		if (!compare(key, elm->key.str))
		{
			value->str = elm->value.str;
			value->len = elm->value.len;
			return (NO_ERROR);
		}
		elm = elm->next;
	}
	return (NO_VAR_ERROR);
}

t_err	get_address_variable(t_ctx *ctx, const char *key, t_str **address_value)
{
	t_env	*elm;

	elm = ctx->env;
	while (elm)
	{
		if (!compare(key, elm->key.str))
		{
			*address_value = &elm->value;
			return (NO_ERROR);
		}
		elm = elm->next;
	}
	return (NO_VAR_ERROR);
}
