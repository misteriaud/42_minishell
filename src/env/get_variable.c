/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mriaud <mriaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:14:33 by artblin           #+#    #+#             */
/*   Updated: 2022/03/29 22:34:43 by artblin          ###   ########.fr       */
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
